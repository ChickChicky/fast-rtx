#pragma once

#include "impl.hpp"

#include "shapes.hpp"
#include "vec.hpp"

#include <vector>

using namespace std;

struct Scene {
    
    vector<Renderable*> renderables;
    
    vec3  campos;
    float camsize;
    float camlength;

    float viewh;
    float vieww;

    float precision;
    float range;

    vec3 voidcolor;

    bool shadows;
    int  reflections;

    vec3 lightpos;

    Scene(void) IMPL({
        this->renderables = {};
        
        this->campos = vec3(0.f,0.f,3.f);
        this->camsize = 5.f;
        this->camlength = 2.f;

        this->lightpos = vec3(0.f,5.f,3.f);

        this->viewh = 500.f;
        this->vieww = 500.f;

        this->precision = 300.f;
        this->range = 20.f;
        
        this->voidcolor = vec3(0.f,0.f,0.1f);

        this->shadows = true;
        this->reflections = 5;
    })

};
