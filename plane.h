#pragma once

#include "point.h"
#include "3dTranformation.h"
#include "2dtransform.h"
#include "line.h"
#include <vector>

class Plane
{
    public:
        vector<Point3D> points;
        Plane()
        {
        }
        Plane(vector<Point3D> points)
        {
            this->points = points;
        }
        void show2D(int color = WHITE, int X = -300, int Y = -200)
        {
            int n = points.size();
            for(int i = 0; i < n ;i++)
            {
                Point3D p1 = points[i];
                Point3D p2 = points[(i+1)%n];

                vec dir(Point3D(0,0,1));
                DrawLine(translate(parrProjection(dir, p1), X, Y), translate(parrProjection(dir, p2), X, Y), color);
            }
        }
        void rotatealongX(float angle)
        {
            for(int i = 0; i < points.size(); i++)
            {
                points[i] = rotateX(points[i], angle);
            }
        }
        void rotatealongY(float angle)
        {
            for(int i = 0; i < points.size(); i++)
            {
                points[i] = rotateY(points[i], angle);
            }
        }
        void rotatealongZ(float angle)
        {
            for(int i = 0; i < points.size(); i++)
            {
                points[i] = rotateZ(points[i], angle);
            }
        }
        void translatePlane(int X, int Y, int Z)
        {
            for(int i = 0; i < points.size(); i++)
            {
                points[i] = translate(points[i], X, Y, Z);
            }
        }
        void getnormal()
        {
            // TODO
        }
};