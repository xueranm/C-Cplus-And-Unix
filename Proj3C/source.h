#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source
{
    private:
    	Image img;
    public:
    	virtual void Execute(void) = 0;
    	Image* GetOutput();
};

#endif