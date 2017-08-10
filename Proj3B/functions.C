#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>
#include <image.h>




void
ReadImage(char *filename, Image &output)
{

	FILE *f = fopen(filename,"rb");
	char magicNum[128];
 	int maxval;
	

 	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &(output.width), &(output.height), &maxval);

 
 	
    output.data = (unsigned char*)malloc(output.width*output.height*3*sizeof(unsigned char));

    fread(output.data,sizeof(unsigned char),3*output.width*output.height,f);
   

    fclose(f);
}


void WriteImage(char *filename, Image &img)
{
	FILE *f = fopen(filename,"wb");
	if (f == NULL)
    {
        printf ("Unable to open '%s' for writing!\n", filename);
    
        return;
    }
    int max = 255;
	fprintf(f, "P6\n%d %d\n%d\n",  img.width, img.height, max);
	
	fwrite(img.data, sizeof(unsigned char), 3 * img.width * img.height,f);
	fclose(f);

}

void
HalveInSize(Image &input, Image &output)
{
	int half_w = (int)(input.width)/2;
	int half_h = (int)(input.height)/2;
	output.width = half_w;
	output.height = half_h;
	output.data = (unsigned char*)malloc(output.width*output.height*3*sizeof(unsigned char));
    int i, j;
    for (i=0; i< half_w;i++){
    	for(j =0;j<half_h;j++){
    		output.data[3*(j*half_w+i)] = input.data[3*(4*j*half_w + 2*i)];
    		output.data[3*(j*half_w+i)+1] = input.data[3*(4*j*half_w + 2*i)+1];
    		output.data[3*(j*half_w+i)+2] = input.data[3*(4*j*half_w + 2*i)+2];
    	}
    }
}

void 
LeftRightConcatenate(Image &leftInput, Image &rightInput, Image &output){
	int out_w = leftInput.width + rightInput.width;
	int out_h = leftInput.height;
	int leftcheck = leftInput.width;
	int right_w = rightInput.width;

	output.width = out_w;
	output.height = out_h;
	output.data = (unsigned char*)malloc(output.width*output.height*3*sizeof(unsigned char));
	int i,j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(i < leftcheck){
				output.data[3*(j*out_w+i)] = leftInput.data[3*(j*leftcheck+i)];
				output.data[3*(j*out_w+i)+1] = leftInput.data[3*(j*leftcheck+i)+1];
				output.data[3*(j*out_w+i)+2] = leftInput.data[3*(j*leftcheck+i)+2];
			}else{
				output.data[3*(j*out_w+i)] = rightInput.data[3*(j*right_w+(i-leftcheck))];
				output.data[3*(j*out_w+i)+1] = rightInput.data[3*(j*right_w+(i-leftcheck))+1];
				output.data[3*(j*out_w+i)+2] = rightInput.data[3*(j*right_w+(i-leftcheck))+2];
			}
		}
	}
}

void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
	int out_h = topInput.height + bottomInput.height;
	int topcheck = topInput.height;
	int bottom_h = bottomInput.height;
	int out_w = topInput.width;
	output.height = out_h;
	output.width = out_w;
	output.data = (unsigned char*)malloc(output.width*output.height*3*sizeof(unsigned char));
    int i, j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(j < topcheck){
				output.data[3*(j*out_w+i)] = topInput.data[3*(j*out_w+i)];
				output.data[3*(j*out_w+i)+1] = topInput.data[3*(j*out_w+i)+1];
				output.data[3*(j*out_w+i)+2] = topInput.data[3*(j*out_w+i)+2];
			}else{
				output.data[3*(j*out_w+i)] = bottomInput.data[3*((j-topcheck)*out_w+i)];
				output.data[3*(j*out_w+i)+1] = bottomInput.data[3*((j-topcheck)*out_w+i)+1];
				output.data[3*(j*out_w+i)+2] = bottomInput.data[3*((j-topcheck)*out_w+i)+2];
			}
		}
	}
}

void Blend(Image &input1, Image &input2, float factor, Image &output){
	float fac2 = 1 - factor;
	int out_w = input1.width;
	int out_h = input1.height;
	output.width = out_w;
	output.height = out_h;
	output.data = (unsigned char*)malloc(output.width*output.height*3*sizeof(unsigned char));
	int i, j;
	for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){

    		output.data[3*(j*out_w+i)] = input1.data[3*(j*out_w+i)]*factor + input2.data[3*(j*out_w+i)]*fac2;
    		output.data[3*(j*out_w+i)+1] = input1.data[3*(j*out_w+i)+1]*factor + input2.data[3*(j*out_w+i)+1]*fac2;
            output.data[3*(j*out_w+i)+2] = input1.data[3*(j*out_w+i)+2]*factor + input2.data[3*(j*out_w+i)+2]*fac2;

    	}
    }
}

