#pragma once

#include <cmath>
#include <iostream>
#include <string.h>

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

const double pi = std::acos(-1);

struct vec2i{
    int x;
    int y;
};

struct vec3i{
    union {
        float x;
        float R;
    };

    union {
        float y;
        float G;
    };

    union {
        float z;
        float B;
    };
};

struct vec2f{
    union {
        float x;
        float u;
    };

    union {
        float y;
        float v;
    };

    vec2f(){ }

    vec2f(float _x, float _y){
        x = _x;
        y = _y;
    }

    float Length() const{
        float len = sqrtf(x*x + y*y);
        return len;
    }


    void Normalize(){
        float len = Length();
        if(!len){
            x /= len;
            y /= len;

        }
    }
};


inline vec2f operator*(const vec2f& l, float f){
    return {l.x*f, l.y*f};
}

struct vec4f;

struct vec3f{
    union {
        float x;
        float R;
    };

    union {
        float y;
        float G;
    };

    union {
        float z;
        float B;
    };

    vec3f() { }

    vec3f(float _x, float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }

    vec3f(const float* pFloat){
        x = pFloat[0];
        y = pFloat[1];
        z = pFloat[2];
    }

    vec3f(float f)
    {
        x = y = z = f;
    }

    vec3f(const vec4f& v);

    vec3f& operator+=(const vec3f& r){
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }

    vec3f& operator-=(const vec3f& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;

        return *this;
    }

    vec3f& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }

    bool operator==(const vec3f& r){
        return ((x == r.x) && (y == r.y) && (z == r.z));
    }

    bool operator!=(const vec3f& r){
        return !(*this == r);
    }

    operator const float*() const{
        return &(x);
    }

    vec3f Cross(const vec3f& v) const; //Complete

    float Dot(const vec3f& v) const{
        return x * v.x + y * v.y + z * v.z;;
    }

    float Distance(const vec3f& v) const{
        float delta_x = x - v.x;
        float delta_y = y - v.y;
        float delta_z = z - v.z;

        float distance = sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
        return distance;
    }

    float Length() const{
        return sqrtf(x * x + y * y + z * z);
    }

    bool IsZero() const{
        return ((x*x + y*y + z*z) == 0.0f);
    }

    vec3f& Normalize(); //Complete

    void Rotate(float Angle, const vec3f& Axis); //Complete
};


struct vec4f{
    float x;
    float y;
    float z;
    float w;

    vec4f()
    {
    }

    vec4f(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    vec4f(const vec3f& v, float _w){
        x = v.x;
        y = v.y;
        z = v.z;
        w = _w;
    }

    
    vec3f to3f() const{
        return {x, y, z};
    }

    float Length() const{
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    vec4f& Normalize(); //Complete

    float Dot(const vec4f& v) const{
        return x * v.x + y * v.y + z * v.z + w * v.w;;
    }
};

inline vec3f operator+(const vec3f& l, const vec3f& r){
    return {l.x + r.x,
            l.y + r.y,
            l.z + r.z};
}

inline vec3f operator-(const vec3f& l, const vec3f& r){
    return {l.x - r.x,
            l.y - r.y,
            l.z - r.z};
}

inline vec3f operator*(const vec3f& l, float f){
    return {l.x * f,
            l.y * f,
            l.z * f};
}

inline vec3f operator/(const vec3f& l, float f){
    return {l.x / f,
            l.y / f,
            l.z / f};
}

inline vec3f::vec3f(const vec4f& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

inline vec4f operator+(const vec4f& l, const vec4f& r){
    return {l.x + r.x,
            l.y + r.y,
            l.z + r.z,
            l.w + r.w};
}


inline vec4f operator-(const vec4f& l, const vec4f& r){
    return {l.x - r.x,
            l.y - r.y,
            l.z - r.z,
            l.w - r.w};
}

inline vec4f operator/(const vec4f& l, float f){
    return {l.x / f,
            l.y / f,
            l.z / f,
            l.w / f};
}

inline vec4f operator*(const vec4f& l, float f){
    return {l.x * f,
            l.y * f,
            l.z * f,
            l.w * f};
}

inline vec4f operator*(float f, const vec4f& l){
    return{l.x * f,
            l.y * f,
            l.z * f,
            l.w * f};
}

struct Quaternion{
    float x, y, z, w;

    Quaternion(float Angle, const vec3f& V);

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize(); //Complete

    Quaternion Conjugate() const; //Complete

    vec3f ToDegrees(); //Complete
};

Quaternion operator*(const Quaternion& l, const Quaternion& r); //Complete

Quaternion operator*(const Quaternion& q, const vec3f& v); //Complete


class mat4f{
public:
    float m[4][4];

    mat4f() { }

    mat4f(float a00, float a01, float a02, float a03,
          float a10, float a11, float a12, float a13,
          float a20, float a21, float a22, float a23,
          float a30, float a31, float a32, float a33)
    {
        m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
        m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
        m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
        m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
    }

    // constructor from Assimp matrix
    mat4f(float a00, float a01, float a02,
          float a10, float a11, float a12,
          float a20, float a21, float a22)
    {
        m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = 0.0;
        m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = 0.0;
        m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = 0.0;
        m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
    }

    void SetZero(){
        memset(m, 0, sizeof(m));
    }

    mat4f Transpose() const{
        mat4f n;

        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
                n.m[i][j] = m[j][i];
            }
        }
        return n;
    }


    inline void InitIdentity(){
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    inline mat4f operator*(const mat4f& Right) const{
        mat4f Ret;

        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                              m[i][1] * Right.m[1][j] +
                              m[i][2] * Right.m[2][j] +
                              m[i][3] * Right.m[3][j];
            }
        }

        return Ret;
    }

    vec4f operator*(const vec4f& v) const{
        vec4f r;

        r.x = m[0][0]* v.x + m[0][1]* v.y + m[0][2]* v.z + m[0][3]* v.w;
        r.y = m[1][0]* v.x + m[1][1]* v.y + m[1][2]* v.z + m[1][3]* v.w;
        r.z = m[2][0]* v.x + m[2][1]* v.y + m[2][2]* v.z + m[2][3]* v.w;
        r.w = m[3][0]* v.x + m[3][1]* v.y + m[3][2]* v.z + m[3][3]* v.w;

        return r;
    }

    operator const float*() const{
        return &(m[0][0]);
    }


    float Determinant() const; //Complete

    mat4f Inverse() const; //Complete
/*
    void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
    void InitScaleTransform(float Scale);
    void InitScaleTransform(const vec3f& Scale);

    void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
    void InitRotateTransformZYX(float RotateX, float RotateY, float RotateZ);
    void InitRotateTransform(const vec3f& Rotate);
    void InitRotateTransform(const Quaternion& quat);

    void InitTranslationTransform(float x, float y, float z);
    void InitTranslationTransform(const vec3f& Pos);

    void InitCameraTransform(const vec3f& Target, const vec3f& Up);

    void InitCameraTransform(const vec3f& Pos, const vec3f& Target, const vec3f& Up);

    void InitPersProjTransform(const PersProjInfo& p);

    void InitOrthoProjTransform(const OrthoProjInfo& p);

    void CalcClipPlanes(vec4f& l, vec4f& r, vec4f& b, vec4f& t, vec4f& n, vec4f& f) const;

private:
    void InitRotationX(float RotateX);
    void InitRotationY(float RotateY);
    void InitRotationZ(float RotateZ);
*/ //Complete
};


class mat3f
{
public:
    float m[3][3];

    mat3f()  {}

    // Initialize the matrix from the top left corner of the 4-by-4 matrix
    mat3f(const mat4f& a){
        m[0][0] = a.m[0][0]; m[0][1] = a.m[0][1]; m[0][2] = a.m[0][2];
        m[1][0] = a.m[1][0]; m[1][1] = a.m[1][1]; m[1][2] = a.m[1][2];
        m[2][0] = a.m[2][0]; m[2][1] = a.m[2][1]; m[2][2] = a.m[2][2];
    }

    vec3f operator*(const vec3f& v) const{
        vec3f r;

        r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;

        return r;
    }

    inline mat3f operator*(const mat3f& Right) const{
        mat3f Ret;

        for (unsigned int i = 0 ; i < 3 ; i++) {
            for (unsigned int j = 0 ; j < 3 ; j++) {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                              m[i][1] * Right.m[1][j] +
                              m[i][2] * Right.m[2][j];
            }
        }

        return Ret;
    }

    mat3f Transpose() const{
        mat3f n;

        for (unsigned int i = 0 ; i < 3 ; i++) {
            for (unsigned int j = 0 ; j < 3 ; j++) {
                n.m[i][j] = m[j][i];
            }
        }

        return n;
    }

};
