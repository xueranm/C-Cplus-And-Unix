/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

void 
InitializeCircle(Circle * c, double radius, double origin, double originY){
	c->radius = radius;
	c->origin = origin;
	c->originY = originY;
}

void 
InitializeRectangle(Rectangle * r, double minX, double maxX, double minY, double maxY){
	r->minX = minX;
	r->maxX = maxX;
	r->minY = minY;
	r->maxY = maxY;
}

void 
InitializeTriangle(Triangle * t, double pt1X, double pt2X, double minY, double maxY){
    t->pt1X = pt1X;
    t->pt2X = pt2X;
    t->minY = minY;
    t->maxY = maxY;
}

double GetCircleArea(Circle * c){
	double radius = c->radius;
    double c_area = 3.14159*radius*radius;
    return c_area;
}

double GetRectangleArea(Rectangle * r){
    double r_area = (r->maxY - r->minY)*(r->maxX - r->minX);
    return r_area;
}

double GetTriangleArea(Triangle * t){
	double t_area = (t->pt2X - t->pt1X)*(t->maxY - t->minY)/2;
	return t_area;
}

void 
GetCircleBoundingBox(Circle * c, double *bbox){
    bbox[0] = c->origin - c->radius;
    bbox[1] = c->origin + c->radius;
    bbox[2] = c->originY - c->radius;
    bbox[3] = c->originY + c->radius;
}

void 
GetRectangleBoundingBox(Rectangle * r, double *bbox){
    bbox[0] = r->minX;
    bbox[1] = r->maxX;
    bbox[2] = r->minY;
    bbox[3] = r->maxY;
}

void
GetTriangleBoundingBox(Triangle * t, double *bbox){
	bbox[0] = t->pt1X;
    bbox[1] = t->pt2X;
    bbox[2] = t->minY;
    bbox[3] = t->maxY;
}



