#include "polygon.h"
#include "lineclipping.h"
#include <iostream>

Point2D intersect(Line l1, Line l2)
{
    Point2D A = l1.p1, B = l1.p2, C = l2.p1, D = l2.p2;
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1 * (A.x) + b1 * (A.y);

    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2 * (C.x) + b2 * (C.y);

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        return Point2D(INT16_MAX, INT16_MAX);
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        return Point2D(x, y);
    }
}

void sutherland_hodgeman(Polygon subjectPoly, Polygon clipWindow)
{
    int num_clip_sides = clipWindow.points.size();

    vector<Point2D> resultPolypoints = subjectPoly.points;
    vector<Point2D> clipPoints = clipWindow.points;

    for (int i = 0; i < num_clip_sides; i++)
    {
        Polygon(resultPolypoints).plotPolygon(RED);
        getch();
        Polygon(resultPolypoints).plotPolygon(BLACK);
        int n = resultPolypoints.size();
        vector<Point2D> tmpPoints;
        Line l = Line(clipPoints[i], clipPoints[(i + 1) % num_clip_sides]);
        for (int j = 0; j < n; j++)
        {
            Point2D p1 = resultPolypoints[j];
            Point2D p2 = resultPolypoints[(j + 1) % n];

            bool f1 = check(l, p1);
            bool f2 = check(l, p2);
            if (f1 && f2)
            {
                tmpPoints.push_back(p2);
            }
            else if (!f1 && f2)
            {
                Point2D intersectP = intersect(l, Line(p1, p2));
                tmpPoints.push_back(intersectP);
                tmpPoints.push_back(p2);
            }
            else if (f1 && !f2)
            {
                Point2D intersectP = intersect(l, Line(p1, p2));
                tmpPoints.push_back(intersectP);
            }
            else
            {
            }
        }
        resultPolypoints.clear();
        resultPolypoints = tmpPoints;
    }
    Polygon(resultPolypoints).plotPolygon(RED);
    cout << "finished\n";
    getch();
}