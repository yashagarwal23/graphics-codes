#pragma once

#include <graphics.h>
using namespace std;

class Point2D
{
public:
    float x, y;
    Point2D()
    {
    }
    Point2D(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    void show(int color = WHITE)
    {
        putpixel(x, y, color);
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