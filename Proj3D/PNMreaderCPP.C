#include <stdio.h>
#include <PNMreaderCPP.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

PNMreaderCPP::PNMreaderCPP(char* filename){
	file = new char[strlen(filename)+1];
	int i;
	for (i = 0; i<(strlen(filename)+1); i++){
		file[i] = filename[i];
	}
};

void
PNMreaderCPP::Execute()
{
	ifstream f;
	f.open(file);
	Image* image = GetOutput();
	char p6[3];
	int width, height, max;
	f >> p6;
	f >> width >> height;
	f >> max;
	f.ignore(256,'\n');
	image->SetSize(width,height);
	image->setData(width, height);
	f.read((char*)image->getData(), width*height*3);
	f.close();
};

PNMreaderCPP::~PNMreaderCPP(){
	delete[] file;
}