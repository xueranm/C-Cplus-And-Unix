#ifndef PNMREADER_H
#define PNMREADER_H
#include <source.h>

class PNMreaderCPP : public Source
{
    private:
    	char *file;
    	int width;
    	int height;

    public:
    	PNMreaderCPP(char* filename);
    	~PNMreaderCPP();
    	virtual void Execute();

};
#endif