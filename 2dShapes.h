#pragma once

#include "point.h"
#include "2dtransform.h"

void midcircle(int centreX, int centreY, int radius, int color = WHITE)
{
    int x = 0;
    int y = radius;
    int d = 1-radius;
    while(x <= y)
    {
        show8symmetry(Point2D(x,y), centreX, centreY, color);
        if(d <= 0)
            d += 2*x+3;
        else
        {
            d += 2*(x-y)+5;
            y--;
        }
        x++;
    }
}

void midarc(int centreX, int centreY, int radius, int startangle, int endangle, int color = WHITE)
{
    setcolor(color);
    arc(centreX, centreY, startangle, endangle, radius);
    setcolor(WHITE);
}

void midellipse(int centreX, int centreY, int a, int b, int color = WHITE, float rotateAngle = 0)
{
    float d = a * a + 0.25 * (float)(b)*b - a * b * b;
    float x = a, y = 0;
    vector<Point2D> points;

    while ((a * a * y) <= (b * b * x))
    {
        if (d <= 0)
        {
            d += a * a * (2 * y + 3);
        }
        else
        {
            d += a * a * (2 * y + 3) + b * b * 2 * (1 - x);
            x--;
        }
        y++;
        points.push_back(Point2D(x, y));
        points.push_back(Point2D(x, -y));
        points.push_back(Point2D(-x, y));
        points.push_back(Point2D(-x, -y));
    }
    d = b * b * (x - 1) * (x - 1) + a * a * (y + 0.5) * (y + 0.5) - a * a * b * b;
    while (x > 0)
    {
        if (d > 0)
        {
            d += (b * b * (3 - 2 * x));
        }
        else
        {
            d += b * b * (3 - 2 * x) + 2 * a * a * (y + 1);
            y++;
        }
        x--;
        points.push_back(Point2D(x, y));
        points.push_back(Point2D(x, -y));
        points.push_back(Point2D(-x, y));
        points.push_back(Point2D(-x, -y));
    }
    for(int i = 0; i < points.size(); i++)
    {
        Point2D rotated = rotate(points[i], rotateAngle);
        Point2D translated = translate(rotated, -centreX, -centreY);
        translated.show(color);     
    }
}

void parabola(int X, int Y, int a, int l, int color = WHITE, float rotateAngle = 0)
{
    int x = 0, y = 0;
    int d = 1 - 2*a;

    vector<Point2D> points;

    while(x <= a && x <= l)
    {
        points.push_back(Point2D(x, y));
        points.push_back(Point2D(x, -y));
        if(d < 0)
        {
            d += 2*y + 3;
        }
        else
        {
            d += 2*y + 3 - 4*a;
            x++;
        }
        y++;
    }
    while(x <= l)
    {
        points.push_back(Point2D(x, y));
        points.push_back(Point2D(x, -y));
        if(d > 0)
        {
            d -= 4*a;
        }
        else
        {
            d += 2*y + 2 - 4*a;
            y++;
        }
        x++;
    }
    for(int i = 0; i < points.size(); i++)
    {
        Point2D rotated = rotate(points[i], rotateAngle);
        Point2D translated = translate(rotated, -X, -Y);
        translated.show(color);     
    }
}