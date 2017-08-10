#ifndef FILTERS_H
#define FILTERS_H
#include <source.h>
#include <sink.h>
#include <logging.h>
#include <image.h>
#include <stdio.h>

class Filters: public Source, public Sink{
    public:
    	virtual void Update();
    	virtual const char *FilterName()=0;
    	const char *SourceName(){return FilterName();};
    	const char *SinkName(){return FilterName();};

};

class Shrinker: public Filters
{
	public:
		virtual void Execute();
		const char *FilterName(){return "Shrinker";};
};

class LRConcat: public Filters
{
	public:
		virtual void Execute();
		const char *FilterName(){return "LRConcat";};
};

class TBConcat: public Filters
{
	public:
		virtual void Execute();
		const char *FilterName(){return "TBConcat";};
};

class Blender: public Filters
{
	private:
		float factor;
	public:
		void SetFactor(float factor);
		float getFactor();
		virtual void Execute();
		const char *FilterName(){return "Blender";};
};

class Mirror: public Filters
{
	public:
		virtual void Execute();
		const char *FilterName(){return "Mirror";};
};

class Rotate: public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Rotate";};
};

class Subtract: public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Subtract";};
};

class Grayscale: public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Grayscale";};
};

class Blur: public Filters
{
    public:
        virtual void Execute();
        const char *FilterName(){return "Blur";};
};

class Color: public Source{

	protected:
    	int w, h, red, green, blue;
    public:
    	Color(int weight,int height,int r,int g,int b){
    		w = weight;
    		h = height;
    		red = r;
    		green = g;
    		blue = b;
    	}
    	virtual void Execute();
        const char *SourceName(){return "ConstantColor";};
    

};

class CheckSum: public Sink
{
	public:
		CheckSum(){
			red = 0;
			green = 0;
			blue = 0;
		}
		void OutputCheckSum(const char*);  ///??why this need virtual?
		const char *SinkName(){return "CheckSum";};
	private:
		unsigned char red, green, blue;

};
#endif