#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
/* data members go here */
	unsigned char *data;
	int width;
	int height;

} Image;

Image *
ReadImage(char *filename)
{

	FILE *f = fopen(filename,"rb");
	char magicNum[128];
 	int width, height, maxval;
	Image *img = NULL;
 	if (f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }
 	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

 	if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
        return NULL;
    }  
 	
 	
 	img = (Image *)malloc (sizeof(Image));
 	img->width = width;
 	img->height = height;
    img->data = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));

    fread(img->data,sizeof(unsigned char),3*width*height,f);
   

    fclose(f);
    return img;
}


void WriteImage(Image *img, char *filename)
{
	FILE *f = fopen(filename,"wb");
	if (f == NULL)
    {
        printf ("Unable to open '%s' for writing!\n", filename);
    
        return;
    }
    int max = 255;
	fprintf(f, "P6\n%d %d\n%d\n",  img->width, img->height, max);
	

	fwrite(img->data, sizeof(unsigned char), 3 * img->width * img->height,f);
	fclose(f);

}

Image *
YellowDiagonal(Image *input)
{
	int w, h;
	Image *img;
	img = (Image *)malloc (sizeof(Image));
	img->data = (unsigned char*)malloc(input->width*input->height*3*sizeof(unsigned char));
	memcpy(img->data,input->data,input->width*input->height*3*sizeof(unsigned char));

	img->width = input->width;
	img->height= input->height; 
	for (w = 0; w<input->width;w++){
		for (h = 0; h<input->height;h++){
			if (w == h){
				img->data[3*((w)*input->width+h)]=255;
				img->data[3*((w)*input->width+h)+1]=255;
				img->data[3*((w)*input->width+h)+2]=0;
			}
		}
	}
	
	return img;
}

int main(int argc, char *argv[])
{
   /* Read an image, apply yellow diagonal to it, then write */
	if (argc !=3){
		fprintf(stderr, "Usage: ./proj3A <input image file> <output image file>");
		exit(EXIT_FAILURE);
	}

	

	Image *img;
	Image *c_img;

	img = ReadImage(argv[1]);
    c_img = YellowDiagonal(img);
	WriteImage(c_img,argv[2]);
	free(img);
	free(c_img);
}
