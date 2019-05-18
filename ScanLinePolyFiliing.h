#include "polygon.h"
#include <vector>
#include <list>
#include <iostream>

class Edge
{
    public:
        float ymax;
        float x;
        float slopeInverse;
        float ymin;
};

bool comapre(Edge e1, Edge e2)
{
    if(e1.x <= e2.x)
        return true;
    else
        return false;
}

vector<Edge> getEdges(Polygon poly)
{
    vector<Edge> edges;
    int n = poly.points.size();
    for(int i = 0; i < n; i++)
    {
        Edge tmp;
        if(poly.points[i].y < poly.points[(i+1)%n].y)
        {
            tmp.ymax = poly.points[(i+1)%n].y;
            tmp.x = poly.points[i].x;
            tmp.ymin = poly.points[i].y;
        }
        else
        {
            tmp.ymax = poly.points[i].y;
            tmp.x = poly.points[(i+1)%n].x;
            tmp.ymin = poly.points[(i+1)%n].y;
        }
        tmp.slopeInverse = 1.0 / Line(poly.points[i], poly.points[(i+1)%n]).slope;
        edges.push_back(tmp);
    }
    return edges;
}

list<Edge> append(list<Edge> AET, list<Edge> GET)
{
    for(auto it = GET.begin(); it != GET.end(); it++)
    {
        AET.push_back(*it);
    }
    return AET;
}

void ScanLinePolyFilling(Polygon poly, int color = RED)
{
    vector<Edge> edges = getEdges(poly);
    list<Edge> GET[480];
    int n = edges.size();
    for(int i = 0; i < n; i++)
    {
        GET[(int)edges[i].ymin].push_back(edges[i]);
    } 

    list<Edge> AET;
    for(int y = 0; y < 480; y++)
    {
        AET = append(AET, GET[y]);
        auto it = AET.begin();
        while(it != AET.end())
        {
            Edge tmp = *it;
            if(tmp.ymax == y)
                it = AET.erase(it);
            else
                ++it;
        }
        AET.sort(comapre);
        it = AET.begin();
        while(it != AET.end())
        {
            float x1 = (*it).x;
            it++;
            float x2 = (*it).x;
            it++;
            DrawLine(x1, y, x2, y, color);
        }
        for(it = AET.begin(); it != AET.end(); it++)
        {
            (*it).x += (*it).slopeInverse;
        }
    }
    cout<<"coloring finished\n";
}