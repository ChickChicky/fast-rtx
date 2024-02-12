#pragma once

#include "impl.hpp"
#include "shape.hpp"

#include <iostream>

struct Sphere : public Shape {
    vec3   pos;
    float  radius;
    vec3   color;
    float  reflective;

    Sphere(vec3 pos, float radius, vec3 color, float reflective) IMPL({
        this->pos        = pos;
        this->radius     = radius;
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
        return this->pos.distance(point) <= this->radius;
    })
};