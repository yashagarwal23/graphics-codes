#pragma once

#include "polygon.h"
#include <math.h>
#include <utility>
#define PI 3.14159265

Point2D translate(Point2D p, int X, int Y)
{
    Point2D ans;
    ans.x = p.x - X;
    ans.y = p.y - Y;
    return ans;
} 

Point2D rotate(Point2D p, float angle)
{
    float radAngle = (PI * angle) / 180;
    float cosA = cos(radAngle);
    float sinA = sin(radAngle);
    Point2D ans;
    ans.x = p.x*cosA - p.y*sinA;
    ans.y = p.x*sinA + p.y*cosA;
    return ans;
}

Point2D scale(Point2D p, double scaleX, double scaleY)
{
    Point2D ans;
    ans.x = p.x * scaleX;
    ans.y = p.y * scaleY;
    return ans;
}

Point2D invert(Point2D p)
{
    return Point2D(p.x, -p.y);
}