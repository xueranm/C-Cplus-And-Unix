#include <stdio.h>
#include <PNMreader.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

PNMreader::PNMreader(char* filename){
	file = new char[strlen(filename)+1];
	int i;
	for (i = 0; i<(strlen(filename)+1); i++){
		file[i] = filename[i];
	}
	width = 0;
	height = 0;
};

void
PNMreader::Execute()
{

	ifstream f;
    f.open(file);
    Image* image = GetOutput();
    char magicNumber[128];
    int w, h, max;
    f >> magicNumber;
    int ret = strncmp(magicNumber,"P6",2);
    if(ret != 0){
        char msg[1024];
        sprintf(msg,"%s: no pnm format!", SourceName());
        DataFlowException e(SourceName(),msg);
        throw e;
    }
    f >> w >> h;
    f >>max;
    f.ignore(256,'\n');
    image->SetSize(w,h);
    image->setData(w, h);
    f.read((char*)image->getData(),w*h*3);
    f.close();
};

PNMreader::~PNMreader(){
	delete[] file;
}