#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

class Vector
{
public:
    float x;
    float y;

    Vector() : x(0), y(0)
    {}

    Vector(int _x, int _y) : x(_x), y(_y)
    {}

    void Add(Vector v1)
    {
        x += v1.x;
        y += v1.y;
    }

    void Sub(Vector v1)
    {
        x -= v1.x;
        y -= v1.y;
    }

    void Mult(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    void Div(float scalar)
    {
        if(scalar != 0)
        {
            x /= scalar;
            y /= scalar;
        }
    }

    float Length()
    {
        return sqrt(x*x + y*y);
    }

    void Normalize()
    {
        float len = Length();
        if(len != 0)
        {
            Div(len);
        }
    }

    void Limit(float max_speed)
    {
        if(Length() > max_speed)
        {
            Normalize();
            Mult(max_speed);
        }
    }

    Vector Copy()
    {
        return Vector(x, y);
    }

    static Vector Add(Vector v1, Vector v2)
    {
        return Vector(v1.x + v2.x, v1.y + v2.y);
    }

    /**
     *  @brief Return a new Vector that is the difference 
     *  between Vector v1 and v2
     *  @param Vector v1 first Vector
     *  @param Vector v2 second Vector
     *  @return Vector(v1 - v2)
     * */
    static Vector Sub(Vector v1, Vector v2)
    {
        return Vector(v1.x - v2.x, v1.y - v2.y);
    }

    static Vector Mult(Vector v1, float scalar)
    {
        return Vector(v1.x * scalar, v1.y * scalar);
    }

    static Vector Div(Vector v1, float scalar)
    {
        return Vector(v1.x / scalar, v1.y / scalar);
    }

    static float Distance(Vector v1, Vector v2)
    {
        return Sub(v1, v2).Length();
    }

    /**
     * @brief Return the angle of the vector in radians
     * @return The angle in radians
     * */
    float Heading()
    {
        return atan2f(y, x);
    }
};

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3 &v2) { return Vector3(this->x + v2.x, this->y + v2.y, this->z + v2.z); }
    Vector3 operator-(const Vector3 &v2) { return Vector3(this->x - v2.x, this->y - v2.y, this->z - v2.z); }
    Vector3 operator*(const float x) { return Vector3(this->x * x, this->y * x, this->z * z); }
    Vector3 operator/(const float x) { return Vector3(this->x / x, this->y / x, this->z / x); }
    bool operator==(const Vector3 &v2) { return this->x == v2.x && this->y == v2.y && this->z == v2.z; }
    bool operator!=(const Vector3 &v2) { return this->x != v2.x || this->y != v2.y || this->z != v2.z; }
};

#endif // !VECTOR_H