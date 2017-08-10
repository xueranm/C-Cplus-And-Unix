#include <PNMwriter.h>
#include <stdio.h>
#include <string.h>

void
PNMwriter::Write(char *filename)
{
	
	FILE *output = fopen(filename, "w");
	fprintf(output, "P6\n%d %d\n255\n", img1->get_w(),img1->get_h());
	fwrite(img1->getData(),sizeof(unsigned char), img1->get_w()*img1->get_h()*3,output);
	fclose(output);
}