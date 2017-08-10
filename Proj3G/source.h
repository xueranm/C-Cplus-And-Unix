#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>
#include <logging.h>

class Source
{
    protected:
    	Image img;
    	virtual void Execute(void) = 0;
    public:
    	Source(){img.SetSrc(this);};
    	virtual void Update();
    	Image* GetOutput();
    	virtual const char *SourceName()=0; 
};

#endif