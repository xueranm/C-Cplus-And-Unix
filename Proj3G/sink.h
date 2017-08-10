#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink{
    protected:
    	const Image *img1;
    	const Image *img2;
    public:
    	Sink();
    	void SetInput(const Image*);
    	void SetInput2(const Image*);
    	//Image* GetImage1();
    	//Image* GetImage2();
    	virtual const char *SinkName() = 0;
};

#endif