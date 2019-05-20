#include <iostream>
#include "point.h"
#include <vector>

using namespace std;

float P0x = 130, P0y = 100, P1x = 140, P1y = 115, P2x = 140, P2y = 135, P3x = 130, P3y = 150, Px = 0, Py = 0, Pz = 0;

void calcP(float &Px, float &Py, float t)
{
    Px = (-4.5 * t * t * t + 9 * t * t - 5.5 * t + 1) * P0x + (13.5 * t * t * t - 22.5 * t * t + 9 * t) * P1x + (-13.5 * t * t * t + 18 * t * t - 4.5 * t) * P2x + (4.5 * t * t * t - 4.5 * t * t + t) * P3x;
    Py = (-4.5 * t * t * t + 9 * t * t - 5.5 * t + 1) * P0y + (13.5 * t * t * t - 22.5 * t * t + 9 * t) * P1y + (-13.5 * t * t * t + 18 * t * t - 4.5 * t) * P2y + (4.5 * t * t * t - 4.5 * t * t + t) * P3y;
}

vector<Point2D> hermite1()
{
    vector<Point2D> points;
    float t = 0;
    P0x = 0, P0y = 100, P1x = 0, P1y = 50, P2x = 0, P2y = -50, P3x = 0, P3y = -100, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    return points;
}

vector<Point2D> hermite6()
{
    vector<Point2D> points;
    float t = 0;
    P0x = 0, P0y = 50, P1x = -25, P1y = 25, P2x = -25, P2y = -25, P3x = 0, P3y = -50, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    t = 0;
    P0x = 0, P0y = -50, P1x = 12, P1y = -37, P2x = 12, P2y = -12, P3x = 0, P3y = 0, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    t = 0;
    P0x = 0, P0y = 0, P1x = -2, P1y = -2, P2x = -20, P2y = -15, P3x = -25, P3y = -25, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    return points;
}

vector<Point2D> hermite3()
{
    vector<Point2D> points;
    float t = 0;
    P0x = 0, P0y = 50, P1x = 15, P1y = 40, P2x = 16, P2y = 12, P3x = 5, P3y = 0, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    t = 0;
    P0x = 5, P0y = 0, P1x = 16, P1y = -12, P2x = 15, P2y = -40, P3x = 0, P3y = -50, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }
    return points;
}

vector<Point2D> hermite8()
{
    vector<Point2D> points;
    float t = 0;
    P0x = 0, P0y = 50, P1x = 12, P1y = 37, P2x = 12, P2y = 12, P3x = 0, P3y = 0, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }   
    t = 0;
    P0x = 0, P0y = 50, P1x = -12, P1y = 37, P2x = -12, P2y = 12, P3x = 0, P3y = 0, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }   
    t = 0;
    P0x = 0, P0y = 0, P1x = 12, P1y = -12, P2x = 12, P2y = -37, P3x = 0, P3y = -50, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }   
    t = 0;
    P0x = 0, P0y = 0, P1x = -12, P1y = -12, P2x = -12, P2y = -37, P3x = 0, P3y = -50, Px = 0, Py = 0;
    while (t < 1)
    {
        calcP(Px, Py, t);
        t += 0.001;
        points.push_back(Point2D(Px, Py));
    }   
    return points;
}