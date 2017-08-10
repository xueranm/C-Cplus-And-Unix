#include <stdio.h>
#include <PNMreader.h>
#include <string.h>

PNMreader::PNMreader(char* filename){
	file = new char[strlen(filename)+1];
	int i;
	for (i = 0; i<(strlen(filename)+1); i++){
		file[i] = filename[i];
	}
};

void
PNMreader::Execute()
{
	FILE *f = fopen(file,"rb");
	Image* image = GetOutput();
	fscanf(f, "P6\n%d %d\n255\n", &width, &height);
	image->SetSize(width,height);
	image->setData(width, height);
	fread(image->getData(),sizeof(unsigned char), image->get_w()*image->get_h()*3,f);
	fclose(f);
};

PNMreader::~PNMreader(){
	delete[] file;
}