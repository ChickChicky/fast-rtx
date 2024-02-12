#pragma once

#include "impl.hpp"
#include "shape.hpp"

struct Cube : public Shape {
    vec3  pos;
    vec3  size;
    vec3  color;
    float reflective;

    Cube(vec3 pos, vec3 size, vec3 color, float reflective) IMPL({
        this->pos        = pos;
        this->size       = size;
        this->color      = color;
        this->reflective = reflective;
    })

    virtual vec3 getPosition(void) IMPL({
        return this->pos;
    })
    
    virtual float getReflective(void) IMPL({
        return this->reflective;
    })

    virtual vec3 getColor(void) IMPL({
        return this->color;
    })

    virtual bool intersects(vec3 point) IMPL({
        return (
            point.x<this->pos.x+this->size.x && point.x>this->pos.x-this->size.x &&
            point.y<this->pos.y+this->size.y && point.y>this->pos.y-this->size.y &&
            point.z<this->pos.z+this->size.z && point.z>this->pos.z-this->size.z
        );
    })
};