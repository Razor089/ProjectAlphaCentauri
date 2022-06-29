#include "Geometry2D.hpp"
#include <math.h>

Vector GetMin(const Rectangle2D &rect)
{
    Vector p1 = rect.origin;
    Vector p2 = Vector::Add(rect.origin, rect.size);
    
    return Vector(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}

Vector GetMax(const Rectangle2D &rect)
{
    Vector p1 = rect.origin;
    Vector p2 = Vector::Add(rect.origin, rect.size);
    
    return Vector(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

Rectangle2D FromMinMax(const Vector &min, const Vector &max)
{
    return Rectangle2D(min, Vector::Sub(max, min));
}

bool RectangleRectangle(const Rectangle2D &rect1, const Rectangle2D &rect2)
{
    Vector aMin = GetMin(rect1);
    Vector aMax = GetMax(rect1);

    Vector bMin = GetMin(rect2);
    Vector bMax = GetMax(rect2);

    bool over_x = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
    bool over_y = ((bMin.y <= aMax.y) && (aMin.y <= bMax.y));

    return over_x && over_y;
}