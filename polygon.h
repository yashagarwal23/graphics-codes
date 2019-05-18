#pragma once

#include "line.h"
#include "point.h"
#include <vector>
#include <utility>

class Polygon
{
    public:
        vector<Point2D> points;
        Polygon()
        {
        }
        Polygon(vector<Point2D> points)
        {
            this->points = points;
        }
        Polygon(vector<pair<float, float> > p)
        {
            for (int i = 0; i < p.size(); i++)
            {
                this->points.push_back(Point2D(p[i].first, p[i].second));
            }
        }
        void plotPolygon(int color = WHITE)
        {
            int n = points.size();
            for (int i = 0; i < n; i++)
            {
                DrawLine(points[i], points[(i + 1) % n]);
            }
        }
};