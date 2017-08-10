#include <image.h>
#include <stdlib.h>

Image::Image(void)
{
	unsigned char *data = NULL;
}

Image::Image(int w, int h)
{
	width = w;
	height = h;
	unsigned char *data = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
}

Image::Image(Image &img)
{
	width = img.width;
	height = img.height;
	unsigned char *data = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
	int i;
	for (i = 0; i<img.height*img.width*3;i++){
		data[i] = img.data[i];
	}
}

void
Image::ResetSize(int w, int h){
	width = w;
	height = h;
}