#ifndef WRITER_H
#define WRITER_H
#include <sink.h>

class PNMwriter: public Sink
{
	public:
		void Write(char *filename);
};

#endif