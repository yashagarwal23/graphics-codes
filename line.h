#pragma once

#include "point.h"

class Line
{
public:
    Point2D p1, p2;
    float slope;
    Line()
    {
    }
    Line(Point2D pa, Point2D pb)
    {
        p1 = Point2D(pa.x, pa.y);
        p2 = Point2D(pb.x, pb.y);
        if(pa.x == pb.y)
            slope = __FLT_MAX__;
        else
            slope = (1.0 * (p2.y - p1.y)) / (1.0 * (p2.x - p1.x));
    }

    Line(float x1, float y1, float x2, float y2)
    {
        p1 = Point2D(x1, y1);
        p2 = Point2D(x2, y2);
    }

    void plotLine(int color = WHITE)
    {
        setcolor(color);
        line(p1.x, p1.y, p2.x, p2.y);
        setcolor(WHITE);
    }
};

void DrawLine(Point2D p1, Point2D p2, int color = WHITE)
{
    setcolor(color);
    line(p1.x, p1.y, p2.x, p2.y);
    setcolor(WHITE);
}

void DrawLine(float x1, float y1, float x2, float y2, int color = WHITE)
{
    setcolor(color);
    line(x1, y1, x2, y2);
    setcolor(WHITE);
}

void DDA(int X0, int Y0, int X1, int Y1) 
{ 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
        putpixel (X,Y,RED);
        X += Xinc; 
        Y += Yinc;          
    } 
} 