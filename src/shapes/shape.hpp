#pragma once

#include "impl.hpp"

#include "vec.hpp"

namespace RenderableType {
    static const int Invalid = -1;
    static const int Object  = 1;
    static const int Shape   = 2;
}

struct Renderable {
    virtual int type(void) IMPL({
        return RenderableType::Invalid;
    })

    virtual bool intersects(vec3 point) IMPL({
        (void) point;
        return false;
    })
};

struct Object : public Renderable {
    virtual int type(void) IMPL({
        return RenderableType::Object;
    })
};

struct Shape : public Renderable {
    virtual int type(void) IMPL({
        return RenderableType::Shape;
    })

    virtual vec3 getPosition(void) IMPL({
        return NAN;
    })

    virtual float getReflective(void) IMPL({
        return false;
    })

    virtual vec3 getColor(void) IMPL({
        return vec3(0.f,1.f,0.f);
    })

    virtual bool intersects(vec3 point) IMPL({
        (void) point;
        return false;
    })
};