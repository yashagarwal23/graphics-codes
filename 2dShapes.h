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

void ellipse(int centreX, int centreY, int a, int b, int color = WHITE, float rotateAngle = 0)
{
    float d = a * a + 0.25 * (float)(b)*b - a * b * b;
    int x = a, y = 0;

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
        Point2D rotated = rotate(Point2D(x,y) , rotateAngle);
        show4symmetry(rotated, centreX, centreY, color);
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
        Point2D rotated = rotate(Point2D(x,y) , rotateAngle);
        show4symmetry(rotated, centreX, centreY, color);
    }
}

// TODO correct errors

// int arcCheck(double x, double y, double s, double e)
// {
//     double angle;
//     if(x == 0)
//     {
//         if(y > 0)
//         {
//             angle = 90;
//         }
//         else
//         {
//             angle = 270;
//         }
//     }
//     else
//     {
//         angle = (atan(abs(y)/abs(x))*180)/PI;
//         if(x < 0 && y < 0)
//             angle = 180 - angle;
//         else if(x < 0 && y > 0)
//             angle += 180;
//         else if(x > 0 && y > 0)
//             angle = 360 - angle;
//     }

//     if((angle >= s && angle <= e) || (360+angle >= s && 360+angle <= e))
//         return 1;
//     return 0;
// }

// void midarc(int X, int Y, int r, int startAngle, int endAngle, int color)
// {
//     int x = 0;
//     int y = 0 + r;
//     int d = 1-r;
//     double s = startAngle;
//     double e = endAngle;
//     putpixel(x,y, color);
//     while(x <= y)
//     {
//         if(d <= 0)
//             d += 2*x+3;
//         else
//         {
//             d += 2*(x-y) + 5;
//             y--;
//         }
//         x++;
//         if(arcCheck(x,y,s,e))
//             putpixel(x + X,y + Y,color);
//         if(arcCheck(x,-y,s,e))
//             putpixel(x + X,-y + Y,color);
//         if(arcCheck(-x,y,s,e))
//             putpixel(-x + X,y + Y,color);
//         if(arcCheck(-x,-y,s,e))    
//             putpixel(-x + X,-y + Y,color);
//         if(arcCheck(y,x,s,e))
//             putpixel(y + X,x + Y,color);
//         if(arcCheck(y,-x,s,e))
//             putpixel(y + X,-x + Y,color);
//         if(arcCheck(-y,-x,s,e))
//             putpixel(-y + X,-x + Y,color);
//         if(arcCheck(-y,x,s,e))
//             putpixel(-y + X,x + Y,color);
//     }
// }