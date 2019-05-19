#pragma once

#include "polygon.h"
#include <vector>
#include <tuple>
#include "lineclipping.h"

bool visited[640][320] = {false};

Point2D intersectC(Line l1, Line l2)
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
        if (x >= min(A.x, B.x) && x <= max(A.x, B.x) && y >= min(A.y, B.y) && y <= max(A.y, B.y) && x >= min(C.x, D.x) && x <= max(C.x, D.x) && y >= min(C.y, D.y) && y <= max(C.y, D.y))
            return Point2D(x, y);
        else
            return Point2D(INT16_MAX, INT16_MAX);
    }
}

vector<tuple<Point2D, bool, int, int>> getList(Polygon subject, Polygon clip)
{
    vector<tuple<Point2D, bool, int, int>> ans;
    int subn = subject.points.size();
    int clipn = clip.points.size();
    for (int i = 0; i < subn; i++)
    {
        vector<tuple<Point2D, bool, int, int>> tmp;
        tmp.push_back({subject.points[i], false, -1, -1});
        for (int j = 0; j < clipn; j++)
        {
            Point2D instersection = intersectC(Line(subject.points[i], subject.points[(i + 1) % subn]), Line(clip.points[j], clip.points[(j + 1) % clipn]));
            if (instersection.x != INT16_MAX)
            {
                int diff = abs(instersection.x - subject.points[i].x);
                auto it = tmp.begin();
                for (; it != tmp.end(); it++)
                {
                    Point2D tp = get<0>(*it);
                    int currdiff = abs(tp.x - subject.points[i].x);
                    if (currdiff > diff)
                        break;
                }
                tmp.insert(it, {instersection, true, i, j});
            }
        }
        ans.insert(ans.end(), tmp.begin(), tmp.end());
    }
    return ans;
}

bool isEnter(Polygon subject, Polygon clip, int i, int j, int k)
{
    if (k == 0)
    {
        pff sub = subject.points[i].toPair() - subject.points[(i - 1) % subject.points.size()].toPair();
        pff cli = clip.points[j].toPair() - clip.points[(j - 1) % clip.points.size()].toPair();
        float cross = sub.first * cli.second - sub.second * cli.first;
        // vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0]
        if (cross < 0)
            return false;
        else
            return true;
    }
    else
    {
        pff sub = clip.points[i].toPair() - clip.points[(i - 1) % clip.points.size()].toPair();
        pff cli = subject.points[j].toPair() - subject.points[(j - 1) % subject.points.size()].toPair();
        float cross = sub.first * cli.second - sub.second * cli.first;
        // vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0]
        if (cross < 0)
            return false;
        else
            return true;
    }
}

void weilerAthertonPolyClipping(Polygon subject, Polygon clip)
{
    // make the lists
    for (int i = 0; i < 640; i++)
    {
        for (int j = 0; j < 320; j++)
            visited[i][j] = false;
    }
    vector<tuple<Point2D, bool, int, int>> lists[2];
    lists[0] = getList(subject, clip); //sublist
    lists[1] = getList(clip, subject); //cliplist

    vector<Polygon> ans;
    int k = 0;
    for (int t = 0; t < subject.points.size() + clip.points.size(); t++)
    {
        // find an intersection not visited yet
        int i = 0;
        vector<Point2D> poly;
        bool found = false;
        for (; i < lists[k].size(); i++)
        {   
            if (get<1>(lists[k][i]) == true)
            {
                Point2D p = get<0>(lists[k][i]);
                if (!visited[(int)p.x][(int)p.y])
                {
                    found = true;
                    break;
                }
            }
        }

        if(!found)
            continue;
        
        Point2D p = get<0>(lists[k][i]);
        while (!visited[(int)p.x][(int)p.y])
        {
            visited[(int)p.x][(int)p.y] = true;
            poly.push_back(p);
            if (get<1>(lists[k][i]))
            {
                // intersection point
                bool f = isEnter(subject, clip, get<2>(lists[k][i]), get<3>(lists[k][i]), k);
                if (!f)
                {
                    k = (k + 1) % 2;
                    for (int c = 0; c < lists[k].size(); c++)
                    {
                        Point2D ptmp = get<0>(lists[k][c]);
                        if (ptmp.x == p.x && ptmp.y == p.y)
                        {
                            i = (c + 1)%lists[k].size();
                            p = get<0>(lists[k][i]);
                            break;
                        }
                    }
                }
                else
                {
                    i = (i + 1) % lists[k].size();
                    p = get<0>(lists[k][i]);
                }
            }
            else
            {
                // vertex
                i = (i + 1) % lists[k].size();
                p = get<0>(lists[k][i]);
            }
        }
        if(poly.size() > 1)
            ans.push_back(Polygon(poly));
    }
    for (int i = 0; i < ans.size(); i++)
    {
        ans[i].plotPolygon(RED);
    }
}