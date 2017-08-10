#ifndef WRITER_H
#define WRITER_H
#include <sink.h>

class PNMwriterCPP: public Sink
{
	public:
		void Write(char *filename);
};

#endif