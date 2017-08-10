#ifndef IMAGE_H
#define IMAGE_H

struct Image
{

	unsigned char *data;
	int height,width;

	Image(void);
	Image(int width, int height);
	Image(Image &);
	void ResetSize(int width, int height);

};

#endif