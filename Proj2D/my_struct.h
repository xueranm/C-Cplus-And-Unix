/* This file should contain your struct definitions for Circle, Triangle, and 
   Rectangle */
typedef struct 
{
	double radius;
	double origin;
	double originY;
} Circle;

typedef struct 
{
	double minX;
	double maxX;
	double minY;
	double maxY;
} Rectangle;

typedef struct 
{
	double pt1X;
	double pt2X;
	double minY;
	double maxY;
} Triangle;

struct Shape;


typedef union
{
	Triangle t;
	Rectangle r;
	Circle c;
}ShapeUnion;

typedef struct 
{
	double (*GetArea)(struct Shape*);
	void (*GetBoundingBox)(struct Shape*,double *);
	
}FunctionTable;

typedef enum
{
	ST_Triangle,
	ST_Rectangle,
	ST_Circle
}ShapeType;

struct Shape
{
	ShapeType st;
	ShapeUnion su;
	FunctionTable ft;
}; 
