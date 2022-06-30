#pragma once
#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H
#include "Vector.hpp"

typedef Vector Point2D;

typedef struct Rectangle2D
{
    Point2D origin;
    Vector size;

    inline Rectangle2D() : size(1, 1) {}
    inline Rectangle2D(const Point2D &o, const Vector &s) : origin(o), size(s) {}
    inline Rectangle2D(const int x, const int y, const int width, const int height) : origin(x,y), size(width, height) {}

} Rectangle2D;

Vector GetMin(const Rectangle2D &rect);
Vector GetMax(const Rectangle2D &rect);

Rectangle2D FromMinMax(const Vector &min, const Vector &max);

bool RectangleRectangle(const Rectangle2D &rect1, const Rectangle2D &rect2);

#endif