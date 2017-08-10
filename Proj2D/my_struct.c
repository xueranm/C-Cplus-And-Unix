/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

void 
InitializeCircle(struct Shape * s, double radius, double origin, double originY){
    s->st = ST_Circle;

	s->su.c.radius = radius;
	s->su.c.origin = origin;
	s->su.c.originY = originY;

    s->ft.GetArea = GetCircleArea;
    s->ft.GetBoundingBox = GetCircleBoundingBox;
}

void 
InitializeRectangle(struct Shape *s, double minX, double maxX, double minY, double maxY){
    s->st = ST_Rectangle;
	
    s->su.r.minX = minX;
	s->su.r.maxX = maxX;
	s->su.r.minY = minY;
	s->su.r.maxY = maxY;

    s->ft.GetArea = GetRectangleArea;
    s->ft.GetBoundingBox = GetRectangleBoundingBox;
}

void 
InitializeTriangle(struct Shape * s, double pt1X, double pt2X, double minY, double maxY){
    s->st = ST_Triangle;

    s->su.t.pt1X = pt1X;
    s->su.t.pt2X = pt2X;
    s->su.t.minY = minY;
    s->su.t.maxY = maxY;

    s->ft.GetArea = GetTriangleArea;
    s->ft.GetBoundingBox = GetTriangleBoundingBox;
}

double GetCircleArea(struct Shape * s){
	double radius = s->su.c.radius;
    double c_area = 3.14159*radius*radius;
    return c_area;
}

double GetRectangleArea(struct Shape * s){
    double r_area = ((s->su.r.maxY) - (s->su.r.minY))*((s->su.r.maxX) - (s->su.r.minX));
    return r_area;
}

double GetTriangleArea(struct Shape * s){
	double t_area = (((s->su.t.pt2X) - (s->su.t.pt1X))*((s->su.t.maxY) - (s->su.t.minY)))/2;
	return t_area;
}

void 
GetCircleBoundingBox(struct Shape * s, double *bbox){
    bbox[0] = (s->su.c.origin) - (s->su.c.radius);
    bbox[1] = (s->su.c.origin) + (s->su.c.radius);
    bbox[2] = (s->su.c.originY) - (s->su.c.radius);
    bbox[3] = (s->su.c.originY) + (s->su.c.radius);
}

void 
GetRectangleBoundingBox(struct Shape * s, double *bbox){
    bbox[0] = s->su.r.minX;
    bbox[1] = s->su.r.maxX;
    bbox[2] = s->su.r.minY;
    bbox[3] = s->su.r.maxY;
}

void
GetTriangleBoundingBox(struct Shape * s, double *bbox){
	bbox[0] = s->su.t.pt1X;
    bbox[1] = s->su.t.pt2X;
    bbox[2] = s->su.t.minY;
    bbox[3] = s->su.t.maxY;
}



