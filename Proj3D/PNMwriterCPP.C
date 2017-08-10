#include <PNMwriterCPP.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

void
PNMwriterCPP::Write(char *filename)
{
	ofstream output;
	output.open(filename);
	Image *image = GetImage1();
	char P6[3] = "P6";
	int max = 255;
	int width = image->get_w();
	int height = image->get_h();
	output << P6 << endl;
	output << width << " "<<height << endl;
	output << max << endl;
	
	output.write((char*)image->getData(),3*width*height);
	output.close();
}