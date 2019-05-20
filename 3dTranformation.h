#pragma once

#include "point.h"
#include <tuple>
#include <math.h>
using namespace std;

#define PI 3.14159

class mat
{
public:
    float m[4][4];
    mat()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0;
    }
};
class vec
{
public:
    float v[4];
    vec()
    {
        for (int i = 0; i < 4; i++)
            v[i] = 0;
    }
    vec(Point3D p)
    {
        v[0] = p.x;
        v[1] = p.y;
        v[2] = p.z;
        v[3] = 1;
    }
    Point3D toPoint()
    {
        return Point3D(v[0], v[1], v[2]);
    }
    void normalise()
    {
        int x = v[3];
        for(int i = 0; i < 4; i++)
            v[i] /= x;
    }
};

mat matxmat(mat mat1, mat mat2)
{
    mat ans;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                ans.m[i][j] += (mat1.m[i][k] * mat2.m[k][j]);
            }
        }
    }
    return ans;
}

vec matxvec(mat mat1, vec v)
{
    vec ans;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ans.v[i] += mat1.m[i][j] * v.v[j];
        }
    }
    return ans;
}

Point3D translate(Point3D p, int X, int Y, int Z)
{
    mat tmat;
    tmat.m[0][0] = tmat.m[1][1] = tmat.m[2][2] = tmat.m[3][3] = 1;
    tmat.m[0][3] = -X;
    tmat.m[1][3] = -Y;
    tmat.m[2][3] = -Z;

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    return ans.toPoint();
}

Point2D projectto2D(Point3D p)
{
    mat tmat;
    tmat.m[0][0] = tmat.m[1][1] = tmat.m[3][3] = 100;
    tmat.m[3][2] = 1;

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point2D(ans.v[0], ans.v[1]);
}

Point3D rotateX(Point3D p, float angle)
{
    mat tmat;
    float rad = (PI * angle)/180;
    tmat.m[0][0] = tmat.m[3][3] = 1;
    tmat.m[1][1] = cos(rad);
    tmat.m[1][2] = -sin(rad);
    tmat.m[2][1] = sin(rad);
    tmat.m[2][2] = cos(rad);

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point3D(ans.v[0], ans.v[1], ans.v[2]);
}

Point3D rotateY(Point3D p, float angle)
{
    mat tmat;
    float rad = (PI * angle)/180;
    tmat.m[1][1] = tmat.m[3][3] = 1;
    tmat.m[0][0] = cos(rad);
    tmat.m[2][0] = -sin(rad);
    tmat.m[0][2] = sin(rad);
    tmat.m[2][2] = cos(rad);

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point3D(ans.v[0], ans.v[1], ans.v[2]);
}

Point3D rotateZ(Point3D p, float angle)
{
    mat tmat;
    float rad = (PI * angle)/180;
    tmat.m[2][3] = tmat.m[3][3] = 1;
    tmat.m[0][0] = cos(rad);
    tmat.m[0][1] = -sin(rad);
    tmat.m[1][0] = sin(rad);
    tmat.m[1][1] = cos(rad);

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point3D(ans.v[0], ans.v[1], ans.v[2]);
}

Point3D aligntoZ(vec v, Point3D p)
{
    float a = v.v[0];
    float b = v.v[1];
    float c = v.v[2];
    float lambda = sqrt(b*b + c*c);
    float modV = sqrt(a*a + b*b + c*c);

    mat tmat;
    tmat.m[0][0] = lambda/modV;
    tmat.m[0][1] = (-1*a*b)/(lambda * modV);
    tmat.m[0][2] = (-1*a*c)/(lambda * modV);
    tmat.m[1][1] = c/lambda;
    tmat.m[1][2] = -b/lambda;
    tmat.m[2][0] = a/lambda;
    tmat.m[2][1] = b/lambda;
    tmat.m[2][2] = c/lambda;
    tmat.m[3][3] = 1;

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point3D(ans.v[0], ans.v[1], ans.v[2]);   
}

Point2D parrProjection(vec dir, Point3D p)
{
    Point3D pEcs = aligntoZ(dir, p);
    return Point2D(pEcs.x, pEcs.y);
}

Point2D persProjection(Point3D p, vec pos, vec normal, vec planepP)
{
    mat tmat;
    float n1 = normal.v[0], n2 = normal.v[1], n3 = normal.v[2];
    float x0 = planepP.v[0], y0 = planepP.v[1], z0 = planepP.v[2];
    float a = pos.v[0], b = pos.v[1], c = pos.v[2];

    float d0 = n1*x0 + n2*y0 + n3*z0;
    float d1 = n1*a + n2*b + n3*c;
    float d = d0 - d1;
    tmat.m[0][0] = d+a*n1;
    tmat.m[0][1] = a*n2;
    tmat.m[0][2] = a*n3;
    tmat.m[0][3] = -a*d0;
    tmat.m[1][0] = b*n1;
    tmat.m[1][1] = d + b*n2;
    tmat.m[1][2] = b*n3;
    tmat.m[1][3] = -b*d0;
    tmat.m[2][0] = c*n1;
    tmat.m[2][1] = c*n2;
    tmat.m[2][2] = d + c*n3;
    tmat.m[2][3] = -c*d0;
    tmat.m[3][0] = n1;
    tmat.m[3][1] = n2;
    tmat.m[3][2] = n3;
    tmat.m[3][3] = -d1;

    vec pv(p);
    vec ans = matxvec(tmat, pv);
    ans.normalise();
    return Point2D(ans.v[0], ans.v[1]);
}