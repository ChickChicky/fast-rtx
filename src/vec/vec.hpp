#pragma once

#include "impl.hpp"

#include <math.h>

/*
    This library might be a little too much for this project :p
*/

struct vec2 {

    float x;
    float y;

    // Constructors

    vec2(void) IMPL({
        this->x = this->y = 0.f;
    })

    vec2(float v) IMPL({
        this->x = this->y = v;
    })

    vec2(float x, float y) IMPL({
        this->x = x;
        this->y = y;
    })

    inline static vec2 zero() IMPL({
        return vec2(0.f,0.f);
    })

    inline static vec2 one() IMPL({
        return vec2(1.f,1.f);
    })

    inline static vec2 neg() IMPL({
        return vec2(-1.f,-1.f);
    })

    // Methods

    inline float length(void) IMPL({
        return sqrtf(powf(this->x,2.f)+powf(this->y,2.f));
    })

    inline vec2 unit(void) IMPL({
        return *this / this->length();
    })

    inline vec2 clone(void) IMPL({
        return vec2(this->x,this->y);
    })

    inline vec2 blend(vec2 other, float alpha) IMPL({
        const float comp = 1.f-alpha;
        return vec2(
            this->x*comp + other.x*alpha,
            this->y*comp + other.y*alpha
        );
    })

    inline float dot(vec2 other) IMPL({
        return (
            this->x*other.x +
            this->y*other.y
        );
    })

    // Operators

    inline vec2 operator+(vec2 other) IMPL({
        return vec2(this->x+other.x,this->y+other.y);
    })

    inline vec2 operator-(vec2 other) IMPL({
        return vec2(this->x-other.x,this->y-other.y);
    })

    inline vec2 operator*(vec2 other) IMPL({
        return vec2(this->x*other.x,this->y*other.y);
    })

    inline vec2 operator/(vec2 other) IMPL({
        return vec2(this->x/other.x,this->y/other.y);
    })

    inline vec2& operator+=(vec2 other) IMPL({
        this->x += other.x;
        this->y += other.y;
        return *this;
    })

    inline vec2& operator-=(vec2 other) IMPL({
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    })

    inline vec2& operator*=(vec2 other) IMPL({
        this->x *= other.x;
        this->y *= other.y;
        return *this;
    })

    inline vec2& operator/=(vec2 other) IMPL({
        this->x /= other.x;
        this->y /= other.y;
        return *this;
    })

    inline vec2 operator+(float other) IMPL({
        return vec2(this->x+other,this->y+other);
    })

    inline vec2 operator-(float other) IMPL({
        return vec2(this->x-other,this->y-other);
    })

    inline vec2 operator*(float other) IMPL({
        return vec2(this->x*other,this->y*other);
    })

    inline vec2 operator/(float other) IMPL({
        return vec2(this->x/other,this->y/other);
    })

    inline vec2& operator+=(float other) IMPL({
        this->x += other;
        this->y += other;
        return *this;
    })

    inline vec2& operator-=(float other) IMPL({
        this->x -= other;
        this->y -= other;
        return *this;
    })

    inline vec2& operator*=(float other) IMPL({
        this->x *= other;
        this->y *= other;
        return *this;
    })

    inline vec2& operator/=(float other) IMPL({
        this->x /= other;
        this->y /= other;
        return *this;
    })

    // Accessors

    inline float& r(void) IMPL({
        return this->x;
    })

    inline float& g(void) IMPL({
        return this->y;
    })

};

struct vec3 {

    float x;
    float y;
    float z;

    // Constructors

    vec3(void) IMPL({
        this->x = this->y = this->z = 0.f;
    })

    vec3(float v) IMPL({
        this->x = this->y = this->z = v;
    })

    vec3(float x, float y, float z) IMPL({
        this->x = x;
        this->y = y;
        this->z = z;
    })

    inline static vec3 zero(void) IMPL({
        return vec3(0.f,0.f,0.f);
    })

    inline static vec3 one(void) IMPL({
        return vec3(1.f,1.f,1.f);
    })

    inline static vec3 neg(void) IMPL({
        return vec3(-1.f,-1.f,-1.f);
    })

    // Methods

    inline float length(void) IMPL({
        return sqrtf(powf(this->x,2.f)+powf(this->y,2.f)+powf(this->z,2.f));
    })

    inline float distance(vec3 other) IMPL({
        return sqrtf(powf(this->x-other.x,2.f)+powf(this->y-other.y,2.f)+powf(this->z-other.z,2.f));
    })

    inline vec3 unit(void) IMPL({
        return *this / this->length();
    })

    inline vec3 clone(void) IMPL({
        return vec3(this->x,this->y,this->z);
    })

    inline vec3 blend(vec3 other, float alpha) IMPL({
        const float comp = 1.f-alpha;
        return vec3(
            this->x*comp + other.x*alpha,
            this->y*comp + other.y*alpha,
            this->z*comp + other.z*alpha
        );
    })

    inline float dot(vec3 other) IMPL({
        return (
            this->x*other.x +
            this->y*other.y +
            this->z*other.z
        );
    })

    // Operators

    inline vec3 operator+(vec3 other) IMPL({
        return vec3(this->x+other.x,this->y+other.y,this->z+other.z);
    })

    inline vec3 operator-(vec3 other) IMPL({
        return vec3(this->x-other.x,this->y-other.y,this->z-other.z);
    })

    inline vec3 operator*(vec3 other) IMPL({
        return vec3(this->x*other.x,this->y*other.y,this->z*other.z);
    })

    inline vec3 operator/(vec3 other) IMPL({
        return vec3(this->x/other.x,this->y/other.y,this->z/other.z);
    })

    inline vec3& operator+=(vec3 other) IMPL({
        this->x += other.x;
        this->y += other.y;
        this->y += other.z;
        return *this;
    })

    inline vec3& operator-=(vec3 other) IMPL({
        this->x -= other.x;
        this->y -= other.y;
        this->y -= other.z;
        return *this;
    })

    inline vec3& operator*=(vec3 other) IMPL({
        this->x *= other.x;
        this->y *= other.y;
        this->y *= other.z;
        return *this;
    })

    inline vec3& operator/=(vec3 other) IMPL({
        this->x /= other.x;
        this->y /= other.y;
        this->y /= other.z;
        return *this;
    })

    inline vec3 operator+(float other) IMPL({
        return vec3(this->x+other,this->y+other,this->z+other);
    })

    inline vec3 operator-(float other) IMPL({
        return vec3(this->x-other,this->y-other,this->z-other);
    })

    inline vec3 operator*(float other) IMPL({
        return vec3(this->x*other,this->y*other,this->z*other);
    })

    inline vec3 operator/(float other) IMPL({
        return vec3(this->x/other,this->y/other,this->z/other);
    })

    inline vec3& operator+=(float other) IMPL({
        this->x += other;
        this->y += other;
        this->y += other;
        return *this;
    })

    inline vec3& operator-=(float other) IMPL({
        this->x -= other;
        this->y -= other;
        this->y -= other;
        return *this;
    })

    inline vec3& operator*=(float other) IMPL({
        this->x *= other;
        this->y *= other;
        this->y *= other;
        return *this;
    })

    inline vec3& operator/=(float other) IMPL({
        this->x /= other;
        this->y /= other;
        this->y /= other;
        return *this;
    })

    // Accessors

    inline float& r(void) IMPL({
        return this->x;
    })

    inline float& g(void) IMPL({
        return this->y;
    })

    inline float& b(void) IMPL({
        return this->z;
    })


};

struct vec4 {

    float x;
    float y;
    float z;
    float w;

    // Constructors

    vec4(void) IMPL({
        this->x = this->y = this->z = this->w = 0.f;
    })

    vec4(float v) IMPL({
        this->x = this->y = this->z = this->w = v;
    })

    vec4(float x, float y, float z, float w) IMPL({
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    })

    inline static vec4 zero(void) IMPL({
        return vec4(0.f,0.f,0.f,0.f);
    })

    inline static vec4 one(void) IMPL({
        return vec4(1.f,1.f,1.f,1.f);
    })

    inline static vec4 neg(void) IMPL({
        return vec4(-1.f,-1.f,-1.f,-1.f);
    })

    // Methods

    inline float length(void) IMPL({
        return sqrtf(powf(this->x,2.f)+powf(this->y,2.f)+powf(this->z,2.f)+powf(this->w,2.f));
    })

    inline vec4 unit(void) IMPL({
        return *this / this->length();
    })

    inline vec4 clone(void) IMPL({
        return vec4(this->x,this->y,this->z,this->w);
    })

    inline vec4 blend(vec4 other, float alpha) IMPL({
        const float comp = 1.f-alpha;
        return vec4(
            this->x*comp + other.x*alpha,
            this->y*comp + other.y*alpha,
            this->z*comp + other.z*alpha,
            this->w*comp + other.w*alpha
        );
    })

    inline float dot(vec4 other) IMPL({
        return (
            this->x*other.x +
            this->y*other.y +
            this->z*other.z +
            this->w*other.w
        );
    })

    // Operators

    inline vec4 operator+(vec4 other) IMPL({
        return vec4(this->x+other.x,this->y+other.y,this->z+other.z,this->w+other.w);
    })

    inline vec4 operator-(vec4 other) IMPL({
        return vec4(this->x-other.x,this->y-other.y,this->z-other.z,this->w-other.w);
    })

    inline vec4 operator*(vec4 other) IMPL({
        return vec4(this->x*other.x,this->y*other.y,this->z*other.z,this->w*other.w);
    })

    inline vec4 operator/(vec4 other) IMPL({
        return vec4(this->x/other.x,this->y/other.y,this->z/other.z,this->w/other.w);
    })

    inline vec4& operator+=(vec4 other) IMPL({
        this->x += other.x;
        this->y += other.y;
        this->y += other.z;
        this->w += other.w;
        return *this;
    })

    inline vec4& operator-=(vec4 other) IMPL({
        this->x -= other.x;
        this->y -= other.y;
        this->y -= other.z;
        this->w -= other.w;
        return *this;
    })

    inline vec4& operator*=(vec4 other) IMPL({
        this->x *= other.x;
        this->y *= other.y;
        this->y *= other.z;
        this->y *= other.z;
        return *this;
    })

    inline vec4& operator/=(vec4 other) IMPL({
        this->x /= other.x;
        this->y /= other.y;
        this->y /= other.z;
        this->w /= other.w;
        return *this;
    })

    inline vec4 operator+(float other) IMPL({
        return vec4(this->x+other,this->y+other,this->z+other,this->w+other);
    })

    inline vec4 operator-(float other) IMPL({
        return vec4(this->x-other,this->y-other,this->z-other,this->w-other);
    })

    inline vec4 operator*(float other) IMPL({
        return vec4(this->x*other,this->y*other,this->z*other,this->w*other);
    })

    inline vec4 operator/(float other) IMPL({
        return vec4(this->x/other,this->y/other,this->z/other,this->w/other);
    })

    inline vec4& operator+=(float other) IMPL({
        this->x += other;
        this->y += other;
        this->y += other;
        this->w += other;
        return *this;
    })

    inline vec4& operator-=(float other) IMPL({
        this->x -= other;
        this->y -= other;
        this->y -= other;
        this->w -= other;
        return *this;
    })

    inline vec4& operator*=(float other) IMPL({
        this->x *= other;
        this->y *= other;
        this->y *= other;
        this->y *= other;
        return *this;
    })

    inline vec4& operator/=(float other) IMPL({
        this->x /= other;
        this->y /= other;
        this->y /= other;
        this->w /= other;
        return *this;
    })

    // Accessors

    inline float& r(void) IMPL({
        return this->x;
    })

    inline float& g(void) IMPL({
        return this->y;
    })

    inline float& b(void) IMPL({
        return this->z;
    })

    inline float& a(void) IMPL({
        return this->w;
    })

};