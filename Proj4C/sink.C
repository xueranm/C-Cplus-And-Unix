#include <sink.h>
#include <stdlib.h>
#include <image.h>
#include <logging.h>



Sink::Sink(){
	img1 = NULL;
    img2 = NULL;	
};

void
Sink::SetInput(const Image *image1){
	this -> img1 = image1;

	
};

void
Sink::SetInput2(const Image *image2){
	this->img2 = image2;

};

//const Image*
//Sink::GetImage1(){
//	return img1;
//};

//const Image*
//Sink::GetImage2(){
//	return img2;
//};