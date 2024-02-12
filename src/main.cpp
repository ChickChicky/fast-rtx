#define DO_IMPL

#include "shapes.hpp"
#include "scene.hpp"
#include "threadlib.hpp"

#include <cinttypes>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define N_THREADS 12

using namespace std;

Scene scene;

vec3 trace(Scene scene, vec3 source, vec3 direction, int bounces) {
    (void) bounces;
    vec3 ray = source.clone();
    const vec3 offset = direction/scene.precision;
    float i = 0.f;
    while (true) {
        if (i > scene.precision * scene.range) break;
        ray = ray + offset;
        for (Renderable* ren : scene.renderables) {
            if (
                ren == nullptr ||
                !ren->intersects(ray)
            ) continue;
            switch (ren->type()) {
                case RenderableType::Invalid: break; // Maybe issue a warning/error ?
                case RenderableType::Shape: {
                    Shape* shape = (Shape*)ren;
                    bool hit = false;
                    vec3 color = shape->getColor();
                    if (scene.shadows) {
                        vec3 ld = (scene.lightpos-ray).unit();
                        vec3 rr = ray.clone() - offset;
                        float dist = scene.lightpos.distance(rr);
                        float j = 0;
                        rr = rr + ld / scene.precision;
                        while (true) {
                            if (j > scene.precision * dist) break;
                            rr = rr + ld / scene.precision;
                            bool dd = false;
                            for (Renderable* ren2 : scene.renderables) {
                                if (ren2->intersects(rr)) {
                                    hit = true;
                                    dd = true;
                                    break;
                                }
                            }
                            if (dd) break;
                            j++;
                        }
                    }
                    const float reflective = shape->getReflective();
                    if (scene.reflections && reflective > 0.f && bounces > 0) {
                        vec3  n  = (ray-shape->getPosition()).unit();
                        float p  = direction.dot(n)*2.f;
                        vec3  m  = n*p;
                        vec3  rd = direction-m;
                        color = color.blend(trace(scene,ray,rd,bounces-1),reflective);
                    }
                    if (hit) {
                        color = color / 4.f;
                    }
                    return color;
                } break;
                case RenderableType::Object: {
                    // TODO
                }; break;
            }
        }
        i++;
    }
    return scene.voidcolor.clone();
}

struct RenderThreadData {
    Thread* thread;
    Scene*  scene;
    vec3*   image;
    float   pxa;
    float   pxb;
    float   py;
    int     processed;
    bool    started;
};

void render_part(void* arg) {
    RenderThreadData* data = (RenderThreadData*)arg;
    data->started = true;
    for (float px = data->pxa; px < data->pxb && px < data->scene->vieww; px++) {
        for (data->py = 0.f; data->py < data->scene->viewh; data->py++) {
            vec3 direction = vec3(
                scene.camsize/2.f-px/scene.vieww*scene.camsize,
                scene.camsize/2.f-data->py/scene.viewh*scene.camsize,
                scene.camlength
            ).unit();
            // Other ray projection method
            /*vec3 direction = vec3(
                -(px*2.f/scene.vieww-1.f)*scene.camsize,
                -(py*2.f/scene.viewh-1.f)*scene.camsize,
                scene.camlength
            ).unit();*/
            vec3 ray = scene.campos.clone();
            data->image[(int)(data->py*scene.vieww+px)] = trace(scene,ray,direction,scene.reflections);
            data->processed++;
        }   
    }
}

static const char  loading_bar_chars[]        = " :#";   // The characters used for rendering the bar
static       char  loading_bar_buff[4096]     = { 0 };   // Stores the formatted loading bar string as it is created
static       float loading_bar_segments[4096] = { 0.f }; // Stores the progress per segment

static inline void loading_bar(const char* name, size_t padding, float progress, float total, int barlen, bool absolute) {
    (void) absolute;
    for (size_t i = 0; i < strlen(loading_bar_buff); i++) {
        loading_bar_buff[i] = 0;
    }
    sprintf(loading_bar_buff,"%s",name);
    for (size_t i = strlen(name); i < padding; i++) {
        sprintf(loading_bar_buff+strlen(loading_bar_buff)," ");
    }
    sprintf(loading_bar_buff+strlen(loading_bar_buff),"%.3f%%",progress/total*100.f);
    for (size_t i = strlen(loading_bar_buff); i < padding + 9; i++) {
        sprintf(loading_bar_buff+strlen(loading_bar_buff)," ");
    }
    const float u = 1.f / (float)(barlen+1);
    float v = progress/total;
    for (int i = 0; i < barlen; i++) {
        if (v > 0.f) {
            loading_bar_segments[i] = fminf(u,v) / u;
            v -= u;
        } else {
            loading_bar_segments[i] = 0.f;
        }
    }
    sprintf(loading_bar_buff+strlen(loading_bar_buff),"[");
    for (int i = 0; i < barlen; i++) {
        sprintf(loading_bar_buff+strlen(loading_bar_buff),"%c",loading_bar_chars[(int)roundf(loading_bar_segments[i]*(float)(sizeof(loading_bar_chars)-2))]);
    }
    sprintf(loading_bar_buff+strlen(loading_bar_buff),"]");
    printf("\x1b[G%s\x1b[K",loading_bar_buff);
    fflush(stdout); // Just in case, probably useless in most cases
}

// Renders a scene onto an image
void render(Scene* scene, vec3* image) {
    
    vector<RenderThreadData*> threads = {};
    
    // Spawns all of the threads
    const float inc = ceilf(scene->vieww/(float)N_THREADS);
    for (float px = 0; px < scene->vieww; px += inc) {
        RenderThreadData* dat = new RenderThreadData{
            nullptr,
            scene,
            image,
            px,
            px + inc,
            0.f,
            0,
            false
        };
        Thread* t = new Thread(render_part,dat);
        dat->thread = t;
        threads.push_back(dat);
        while (!dat->started) Thread::sleep(10); // The current implementation is a bit broken, we have to wait for the threads to start manually
        loading_bar("starting threads:",20,(float)threads.size(),(float)N_THREADS,10,false);
    }
    printf("\n");
    
    // The size of the image, which is used to calculate the progress
    const int sz = (int)(scene->vieww*scene->viewh);
    
    // Waits for all the threads to finish, and displays the progress
    while (true) {
        int i = 0;
        for (RenderThreadData* t : threads) {
            i += t->processed;
        }
        loading_bar("rendering:",20,(float)i,(float)sz,10,false);
        if (i == sz) break;
        Thread::sleep(50);
    }
    
    // Free all the memory allocated for the threads
    for (RenderThreadData* t : threads) {
        delete t->thread;
        delete t;
    }
    threads.clear();
    
    printf("\n");

}

int main(int argc, const char** argv) {
    (void) argc; (void) argv;
    
    // Creates the scene
    scene = Scene();
    
    scene.renderables.push_back(
        new Sphere(
            vec3(0.f,0.f,8.f), // Position
            1.f,               // Radius
            vec3(0.f,0.f,1.f), // Color
            .1f                // Reflective
        )
    );
    scene.renderables.push_back(
        new Sphere(
            vec3(-1.5f,-.5f,7.f), // Position
            .5f,                  // Radius
            vec3(1.f,0.f,0.f),    // Color
            .5f                   // Reflective
        )
    );
    scene.renderables.push_back(
        new Cube(
            vec3(0.f,-10.f,0.f), // Position
            vec3(30.f,4.f,30.f), // Size
            vec3(0.f,1.f,0.f),   // Color
            .5f                  // Reflective
        )
    );
    scene.renderables.push_back(
        new Sphere( 
            vec3(2.f,0.f,7.f), // Position 
            1.f,               // Radius
            vec3(1.f,1.f,1.f), // Color
            .95f               // Reflective
        )
    );

    // Renders the scene
    vec3* image = new vec3[(int)(scene.vieww*scene.viewh)];
    render(&scene,image);
    
    // Turns the render image into an R8G8B8 image
    uint8_t* img = new uint8_t[(int)(scene.vieww*scene.viewh)*3];
    for (size_t i = 0; i < (size_t)(scene.vieww*scene.viewh); i++) {
        const vec3 c = image[i];
        img[i*3]   = (uint8_t)(c.x*255.f);
        img[i*3+1] = (uint8_t)(c.y*255.f);
        img[i*3+2] = (uint8_t)(c.z*255.f);
    }
    delete[] image;

    // Exports the image into PNG
    char* cmd = new char[1024];
    sprintf(cmd,"ffmpeg -y -f rawvideo -video_size %dx%d -pixel_format rgb24 -i pipe:0 -frames:v 1 output.png",(int)scene.vieww,(int)scene.viewh);
    FILE* ffmpeg = _popen(cmd,"w");
    fwrite(img,(size_t)(scene.vieww*scene.viewh)*3,1,ffmpeg);
    fflush(ffmpeg);
    fclose(ffmpeg);

    delete[] img;
    delete[] cmd;
}