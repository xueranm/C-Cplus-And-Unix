#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink{
    private:
    	Image *img1;
    	Image *img2;
    public:
    	Sink();
    	void SetInput(Image*);
    	void SetInput2(Image*);
    	Image* GetImage1();
    	Image* GetImage2();
};

#endif