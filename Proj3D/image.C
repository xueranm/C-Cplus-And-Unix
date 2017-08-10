#include <image.h>
#include <stdlib.h>

Image::Image(void)
{
	unsigned char *data = NULL;
};

Image::Image(int w, int h)
{
	this->width = w;
	this->height = h;
	unsigned char *data = new unsigned char[width*height*3];
};

Image::Image(Image &img)
{
	this->width = img.width;
	this->height = img.height;
	unsigned char *data = new unsigned char[width*height*3];
	int i;
	for (i = 0; i<img.height*img.width*3;i++){
		data[i] = img.data[i];
	}
};

void
Image::ResetSize(int w, int h){
	this->width = w;
	this->height = h;
};

void
Image::SetSize(int w, int h){
	this->width = w;
	this->height = h;
};

int
Image::get_w(){
	return this->width;
};

int
Image::get_h(){
	return this->height;
};

void
Image::setData(int width, int height){
	this->data = new unsigned char[width*height*3];
};

unsigned char*
Image::getData(){
	return (this->data);
};

Image::~Image(){
	delete[] data;
};

