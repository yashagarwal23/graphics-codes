#pragma once

#include "line.h"
#include "polygon.h"
#include "2dtransform.h"
#include <algorithm>

typedef pair<float, float> pff;

struct tstruct
{
    float t;
    bool isEnter;
};

int dot(pair<int, int> p1, pair<int, int> p2)
{
    return (round(p1.first) * round(p2.first) + round(p1.second) * round(p2.second));
}
pff operator-(pff p1, pff p2)
{
    return {p1.first - p2.first, p1.second - p2.second};
}
pff operator+(pff p1, pff p2)
{
    return {p1.first + p2.first, p1.second + p2.second};
}

pff getnormal(pff p)
{
    float x = p.first;
    float y = p.second;
    pff ans = rotate(Point2D(x, y), 90).toPair();
    return {round(ans.first), round(ans.second)};
}

void draw(pff p1, pff p2, float t1, float t2)
{
    pff del = p2 - p1;
    Line(Point2D(p1.first + del.first * t1, p1.second + del.second * t1), Point2D(p1.first + del.first * t2, p1.second + del.second * t2)).plotLine();
}

void cyrus_beck(Line line, Polygon poly)
{
    pff p1 = line.p1.toPair(), p2 = line.p2.toPair();
    int n = poly.points.size();
    // float min = 1.5;
    // int minI = 0;
    vector<tstruct> tvalues;
    for (int i = n-1; i >= 0; i--)
    {
        pff pe1 = poly.points[i].toPair();
        pff pe2 = poly.points[(i + 1) % n].toPair();
        pff edgedir = pe2 - pe1;
        pff normal = getnormal(edgedir);
        float num = dot(p1 - pe1, normal);
        float den = dot(p2 - p1, normal);
        if (den != 0)
        {
            float t = -num / den;
            if (den < 0 && t <= 1.0 && t >= 0.0)
            {
                tvalues.push_back({t, true});
            }
            else if (den > 0 && t <= 1.0 && t >= 0.0)
            {
                tvalues.push_back({t, false});
            }
        }
    }

    vector<tstruct>::iterator req;
    vector<tstruct>::iterator it = tvalues.begin();
    for (int i = 0; i < tvalues.size(); i++)
    {
        it++;
        if (tvalues[i].t > tvalues[(i + 1) % tvalues.size()].t)
        {
            req = it;
            break;
        }
    }

    it = tvalues.insert(it, {1, false});
    it++;
    it = tvalues.insert(it, {0, true});

    vector<double> entries;
    vector<double> exits;

    int entryI = 0;
    int exitI = 0;
    for (int i = 0; i < tvalues.size(); i++)
    {
        if (tvalues[i].t == 0)
        {
            entryI = i;
            exitI = (i - 1) % tvalues.size();
            break;
        }
    }
    
    n = tvalues.size();
    int i = entryI;
    vector<float> tmp;
    do
    {
        if (tvalues[i].isEnter)
        {
            tmp.push_back(tvalues[i].t);
        }
        else if(tvalues[i].isEnter == false && tmp.size() > 0)
        {
            auto it = max_element(tmp.begin(), tmp.end());
            entries.push_back(*it);
            tmp.clear();
        }
        i = (i + 1) % n;
    } while (i != entryI);

    tmp.clear();
    i = exitI;
    do
    {
        if (tvalues[i].isEnter && tmp.size() > 0)
        {
            auto it = min_element(tmp.begin(), tmp.end());
            exits.push_back(*it);
            tmp.clear();
        }
        else
        {
            tmp.push_back(tvalues[i].t);
        }
        i = (i - 1 + n) % n;
    } while (i != exitI);

    sort(entries.begin(), entries.end());
    sort(exits.begin(), exits.end());

    for (int x = 0; x < entries.size(); x++)
    {
        if(entries[x] <= exits[x])
            draw(line.p1.toPair(),line.p2.toPair(), entries[x], exits[x]);
    }
}

bool check(Line l, Point2D p)
{
    pair<int, int> pv = p.toPair() - l.p1.toPair();
    pair<int, int> lv = l.p2.toPair() - l.p1.toPair();
    pair<int, int> normal = getnormal(lv);
    float d = normal.first * pv.first + normal.second * pv.second;
    if (d > 0)
        return false;
    else
        return true;
}

int generateCode(Point2D p, Polygon poly)
{
    int n = poly.points.size();
    int x = 1;
    int code = 0;
    for (int i = 0; i <= n; i++)
    {
        if (!check(Line(poly.points[i], poly.points[(i + 1) % n]), p))
        {
            int tmp = pow(2, i);
            code = code | tmp;
        }
    }
    return code;
}

Point2D getm(Point2D p1, Point2D p2)
{
    return Point2D((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
}

void midPointSubdivision(Line line, Polygon poly)
{
    Point2D p1 = line.p1, p2 = line.p2;
    int code1 = generateCode(p1, poly);
    int code2 = generateCode(p2, poly);
    if (code1 == 0 && code2 == 0)
    {
        line.plotLine();
        return;
    }
    if (code1 & code2 != 0)
    {
        return;
    }
    Point2D pm = getm(p1, p2);
    int codepm = generateCode(pm, poly);

    while (codepm != 0)
    {
        if (code1 & codepm != 0)
        {
            p1 = pm;
            pm = getm(p1, p2);
            codepm = generateCode(pm, poly);
            code1 = generateCode(p1, poly);
        }
        else
        {
            p2 = pm;
            pm = getm(p1, p2);
            codepm = generateCode(pm, poly);
            code2 = generateCode(p2, poly);
        }
    }
    bool f1 = false, f2 = false;
    if (code1 == 0)
        f1 = true;
    if (code2 == 0)
        f2 = true;

    Point2D pmd;
    int codepmd;
    if (!f1)
    {
        while (!(round(pm.x) == round(p1.x) && round(pm.y) == round(p1.y)))
        {
            pmd = getm(p1, pm);
            codepmd = generateCode(pmd, poly);
            code1 = generateCode(p1, poly);
            codepm = generateCode(pm, poly);
            if (codepmd != 0)
                p1 = pmd;
            else
                pm = pmd;
            DrawLine(p1, p2, RED);
            delay(1000);
            DrawLine(p1, p2, BLACK);
        }
    }

    if (!f2)
    {
        while (!(round(pm.x) == round(p2.x) && round(pm.y) == round(p2.y)))
        {
            pmd = getm(p2, pm);
            codepmd = generateCode(pmd, poly);
            code2 = generateCode(p2, poly);
            codepm = generateCode(pm, poly);
            if (codepmd != 0)
                p2 = pmd;
            else
                pm = pmd;
            DrawLine(p1, p2, RED);
            delay(1000);
            DrawLine(p1, p2, BLACK);
        }
    }
    cout << "finished\n";
    DrawLine(p1, p2, RED);
}
