#pragma once

#include <graphics.h>
#include <utility>
#include <iostream>
using namespace std;

class Point2D
{
public:
    float x, y;
    Point2D()
    {
    }
    Point2D(float x1, float y1)
    {
        x = x1;
        y = y1;
    }
    void show(int color = WHITE)
    {
        putpixel(x, y, color);
    }
    pair<float,float> toPair()
    {
        return {x, y};
    }
};

void show4symmetry(Point2D p, int X, int Y, int color = WHITE)
{
    int x = p.x;
    int y = p.y;
    putpixel(x + X, y + Y, color);
    putpixel(-x + X, y + Y, color);
    putpixel(x + X, -y + Y, color);
    putpixel(-x + X, -y + Y, color);
}
void show8symmetry(Point2D p, int X, int Y, int color = WHITE)
{
    int x = p.x;
    int y = p.y;
    putpixel(x + X, y + Y, color);
    putpixel(-x + X, y + Y, color);
    putpixel(x + X, -y + Y, color);
    putpixel(-x + X, -y + Y, color);
    putpixel(y + X, x + Y, color);
    putpixel(-y + X, x + Y, color);
    putpixel(y + X, -x + Y, color);
    putpixel(-y + X, -x + Y, color);
}

class Point3D
{
public:
    float x, y, z;
    Point3D()
    {
    }
    Point3D(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};