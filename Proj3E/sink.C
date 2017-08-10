#include <sink.h>
#include <stdlib.h>

Sink::Sink(){
	img1 = NULL;
    img2 = NULL;	
};

void
Sink::SetInput(Image *image1){
	this -> img1 = image1;
};

void
Sink::SetInput2(Image *image2){
	this->img2 = image2;
};

Image*
Sink::GetImage1(){
	return img1;
};

Image*
Sink::GetImage2(){
	return img2;
};