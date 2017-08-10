#include <image.h>
#include <stdlib.h>
#include <source.h>

Image::Image(void)
{
	data = NULL;
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
Image::get_w() const{
	return this->width;
};

int
Image::get_h() const{
	return this->height;
};

void
Image::setData(int width, int height){
	if(data != NULL){
		delete[] data;
	}
	data = NULL;
	this->data = new unsigned char[width*height*3];
};

unsigned char*
Image::getData() const{
	return (this->data);
};

void 
Image::SetSrc(Source* src){
	this->src = src;
}
void
Image::Update() const{
	src->Update();
}
Image::~Image(){
	delete[] data;
};

