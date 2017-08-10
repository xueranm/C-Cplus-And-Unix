#ifndef PNMREADER_H
#define PNMREADER_H
#include <source.h>

class PNMreader : public Source
{
    private:
    	char *file;
    	int width;
    	int height;

    public:
    	PNMreader(char* filename);
    	~PNMreader();
    	virtual void Execute();

};
#endif