#include <PNMwriter.h>
#include <stdio.h>
#include <string.h>

void
PNMwriter::Write(char *filename)
{
	Image *image = GetImage1();
	FILE *output = fopen(filename, "w");
	fprintf(output, "P6\n%d %d\n255\n", image->get_w(),image->get_h());
	fwrite(image->getData(),sizeof(unsigned char), image->get_w()*image->get_h()*3,output);
	fclose(output);
}