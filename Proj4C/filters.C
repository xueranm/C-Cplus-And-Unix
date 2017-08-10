#include <filters.h>
#include <stdio.h>
#include <image.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sys/time.h>

using namespace std;

static vector<Image*> allfilters;


void 
Filters::Update()
{
	if(img1 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        int pos1 = allfilters.size();
        allfilters.push_back(GetOutput());
        int pos2 =allfilters.size();
        if (allfilters.size()!=0){
        	for (int i = 0; i< allfilters.size();i++){
        		if (allfilters[i] == img1){
        			char msg[1024];
					sprintf(msg, "%s: input points to same object's output!", SourceName());
					DataFlowException e(SourceName(),msg);
					throw e;
        		}
        	}
        }
        
        img1->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
        if (pos1!=pos2 &&allfilters.size()!=0){
        	allfilters.pop_back();
        }
    }
	if(img2 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        int pos3 = allfilters.size();
        allfilters.push_back(GetOutput());
        int pos4 = allfilters.size();
        if (allfilters.size()!=0){
        	for (int i = 0; i< allfilters.size();i++){
        		if (allfilters[i] == img2){
        			char msg[1024];
					sprintf(msg, "%s: input points to same object's output!", SourceName());
					DataFlowException e(SourceName(),msg);
					throw e;
        		}
        	}
        }
        img2->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
        if (pos3!=pos4 &&allfilters.size()!=0){
        	allfilters.pop_back();
        }
    }

	char msg[1024];
	struct timeval startTime;
	gettimeofday(&startTime, 0);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    struct timeval endTime;
    gettimeofday(&endTime,0);
    double seconds = double(endTime.tv_sec - startTime.tv_sec)+double(endTime.tv_usec - startTime.tv_usec)/1000000;
    sprintf(msg, "%s: done executing with time: %f", SourceName(),seconds);
    Logger::LogEvent(msg);
}
void 
Shrinker::Execute(){
	Image *output = GetOutput();
	if(img1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int width = (int)img1->get_w();
	int height = (int)img1->get_h();
	int half_w = width/2;
	int half_h = height/2;

	output->SetSize(half_w,half_h);
	output->setData(half_w,half_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
    int i, j;
    for (i=0; i< half_w;i++){
    	for(j =0;j<half_h;j++){
    		output->getData()[3*(j*half_w+i)] = img1->getData()[3*(2*j*width + 2*i)];
    		output->getData()[3*(j*half_w+i)+1] = img1->getData()[3*(2*j*width + 2*i)+1];
    		output->getData()[3*(j*half_w+i)+2] = img1->getData()[3*(2*j*width + 2*i)+2];
    	}
    }
};

void 
LRConcat::Execute(){
	
	if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2== NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
	Image* output = GetOutput();

	int out_w = (int)img1->get_w() + (int)img2->get_w();
	int out_h = img1->get_h();
	int leftcheck = img1->get_w();
	int right_w = img2->get_w();

	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	if(img1->get_h()!=img2->get_h()){
		char msg[1024];
		sprintf(msg,"%s: heights must match: %d, %d", SinkName(),img1->get_h(),img2->get_h());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int i,j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(i < leftcheck){
				output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*leftcheck+i)];
				output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*leftcheck+i)+1];
				output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*leftcheck+i)+2];
			}else{
				output->getData()[3*(j*out_w+i)] = img2->getData()[3*(j*right_w+(i-leftcheck))];
				output->getData()[3*(j*out_w+i)+1] = img2->getData()[3*(j*right_w+(i-leftcheck))+1];
				output->getData()[3*(j*out_w+i)+2] = img2->getData()[3*(j*right_w+(i-leftcheck))+2];
			}
		}
	}

};

void 
TBConcat::Execute()
{
	
	Image *output = GetOutput();
	if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

	int out_h = (int)img1->get_h() + (int)img2->get_h();
	int topcheck = img1->get_h();
	int out_w =img1->get_w();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(img1->get_w()!=img2->get_w()){
		char msg[1024];
		sprintf(msg,"%s: widths must match: %d, %d", SinkName(),img1->get_w(),img2->get_w());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}
	int i, j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(j < topcheck){
				output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*out_w+i)];
				output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*out_w+i)+1];
				output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*out_w+i)+2];
			}else{
				output->getData()[3*(j*out_w+i)] = img2->getData()[3*((j-topcheck)*out_w+i)];
				output->getData()[3*(j*out_w+i)+1] = img2->getData()[3*((j-topcheck)*out_w+i)+1];
				output->getData()[3*(j*out_w+i)+2] = img2->getData()[3*((j-topcheck)*out_w+i)+2];
			}
		}
	}
};

void 
Blender::SetFactor(float factor)
{
	this->factor = factor;
};

float
Blender::getFactor(){
	return this->factor;
};

void Blender::Execute(){
	float factor = getFactor();
	float fac2 = 1 - getFactor();
	
	Image *output = GetOutput();
	if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (factor<0 || factor>1){
    	char msg[1024];
    	sprintf(msg, "Invalid factor for Blender: %f",factor);
    	DataFlowException e(SinkName(), msg);
    	throw e;
    }

	int out_w = img1->get_w();
	int out_h = img2->get_h();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	if(img1->get_w()!=img2->get_w()){
		char msg[1024];
		sprintf(msg,"%s: widths must match: %d, %d", SinkName(),img1->get_w(),img2->get_w());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	if(img1->get_h()!=img2->get_h()){
		char msg[1024];
		sprintf(msg,"%s: heights must match: %d, %d", SinkName(),img1->get_h(),img2->get_h());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	
	int i, j;
	for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
       
    		output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*out_w+i)]*factor + img2->getData()[3*(j*out_w+i)]*fac2;
    		output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*out_w+i)+1]*factor + img2->getData()[3*(j*out_w+i)+1]*fac2;
            output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*out_w+i)+2]*factor + img2->getData()[3*(j*out_w+i)+2]*fac2;

    	}
    }
};

void Mirror::Execute(){
	
	Image *output = GetOutput();
	if(img1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int out_w = img1->get_w();
	int out_h = img1->get_h();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	int i, j;
    for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
    		output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*out_w + out_w-1-i)];
    		output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*out_w + out_w-1-i)+1];
    		output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*out_w + out_w-1-i)+2];
    	}
    }

};

void Rotate::Execute(){
	
	Image *output = GetOutput();
	if(img1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int out_w = img1->get_h();
	int out_h = img1->get_w();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	int i, j;
    for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
    		int p = out_w - i -1; //input's j
    		int q = j;            //input's i
    		output->getData()[3*(j*out_w+i)] = img1->getData()[3*(p*out_h + q)];
    		output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(p*out_h + q)+1];
    		output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(p*out_h + q)+2];
    	}
    }
};

void Subtract::Execute(){
	
	Image *output = GetOutput();
	if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

	int out_h = img1->get_h();
	int out_w = img1->get_w();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(img1->get_w()!=img2->get_w()){
		char msg[1024];
		sprintf(msg,"%s: widths must match: %d, %d", SinkName(),img1->get_w(),img2->get_w());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	if(img1->get_h()!=img2->get_h()){
		char msg[1024];
		sprintf(msg,"%s: heights must match: %d, %d", SinkName(),img1->get_h(),img2->get_h());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	int i, j;
    for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
    		if(img1->getData()[3*(j*out_w + i)]>img2->getData()[3*(j*out_w + i)]){
    			output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*out_w + i)] - img2->getData()[3*(j*out_w + i)];
    		}else{
    			output->getData()[3*(j*out_w+i)] = 0;
    		}
    		if(img1->getData()[3*(j*out_w + i)+1]>img2->getData()[3*(j*out_w + i)+1]){
    			output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*out_w + i)+1] - img2->getData()[3*(j*out_w + i)+1];
    		}else{
    			output->getData()[3*(j*out_w+i)+1] = 0;
    		}
    		if(img1->getData()[3*(j*out_w + i)+2]>img2->getData()[3*(j*out_w + i)+2]){
    			output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*out_w + i)+2] - img2->getData()[3*(j*out_w + i)+2];
    		}else{
    			output->getData()[3*(j*out_w+i)+2] = 0;
    		}
    	}
    }
};

void Grayscale::Execute(){
	
	Image *output = GetOutput();
	if(img1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int out_w = img1->get_w();
	int out_h = img1->get_h();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	int i, j;
    for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
    		//I not sure int or unsigned char in order to use integer division
    		unsigned char grayscale = img1->getData()[3*(j*out_w + i)]/5 + img1->getData()[3*(j*out_w + i)+1]/2 + img1->getData()[3*(j*out_w + i)+2]/4;
    		output->getData()[3*(j*out_w+i)] = grayscale;
    		output->getData()[3*(j*out_w+i)+1] = grayscale;
    		output->getData()[3*(j*out_w+i)+2] = grayscale;
    	}
    }
};

void Blur::Execute(){
	
	
	if(img1 == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	Image *output = GetOutput();
	int out_w = img1->get_w();
	int out_h = img1->get_h();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(output == NULL){
		char msg[1024];
		sprintf(msg, "%s: no output!", SourceName());
		DataFlowException e(SourceName(),msg);
		throw e;
	}

	int i, j;
    for (i=0; i< out_w;i++){
    	for(j =0;j<out_h;j++){
    		if (i==0||i==out_w-1||j==0||j==out_h-1){
    			output->getData()[3*(j*out_w+i)] = img1->getData()[3*(j*out_w+i)];
    		    output->getData()[3*(j*out_w+i)+1] = img1->getData()[3*(j*out_w+i)+1];
    		    output->getData()[3*(j*out_w+i)+2] = img1->getData()[3*(j*out_w+i)+2];
    		}else{
    			unsigned char red = img1->getData()[3*((j-1)*out_w+i-1)]/8 + img1->getData()[3*((j-1)*out_w+i)]/8+img1->getData()[3*((j-1)*out_w+i+1)]/8 +img1->getData()[3*(j*out_w+i-1)]/8 +img1->getData()[3*(j*out_w+i+1)]/8 +img1->getData()[3*((j+1)*out_w+i-1)]/8+img1->getData()[3*((j+1)*out_w+i)]/8+img1->getData()[3*((j+1)*out_w+i+1)]/8;
    			unsigned char green = img1->getData()[3*((j-1)*out_w+i-1)+1]/8 + img1->getData()[3*((j-1)*out_w+i)+1]/8+img1->getData()[3*((j-1)*out_w+i+1)+1]/8 +img1->getData()[3*(j*out_w+i-1)+1]/8 +img1->getData()[3*(j*out_w+i+1)+1]/8 +img1->getData()[3*((j+1)*out_w+i-1)+1]/8+img1->getData()[3*((j+1)*out_w+i)+1]/8+img1->getData()[3*((j+1)*out_w+i+1)+1]/8;
    			unsigned char blue = img1->getData()[3*((j-1)*out_w+i-1)+2]/8 + img1->getData()[3*((j-1)*out_w+i)+2]/8+img1->getData()[3*((j-1)*out_w+i+1)+2]/8 +img1->getData()[3*(j*out_w+i-1)+2]/8 +img1->getData()[3*(j*out_w+i+1)+2]/8 +img1->getData()[3*((j+1)*out_w+i-1)+2]/8+img1->getData()[3*((j+1)*out_w+i)+2]/8+img1->getData()[3*((j+1)*out_w+i+1)+2]/8;
    			output->getData()[3*(j*out_w+i)] = red;
    		    output->getData()[3*(j*out_w+i)+1] = green;
    		    output->getData()[3*(j*out_w+i)+2] = blue;
    		}
    		
        }
    }
};


void 
Color::Execute(){
	Image *output = GetOutput();
	output->SetSize(w,h);
	output->setData(w,h);
	int dimen = w*h;
	int i;
	for (i = 0; i< dimen;i++){
		output->getData()[3*i] = red;
		output->getData()[3*i+1] = green;
		output->getData()[3*i+2] = blue;
	}
};


void 
CheckSum::OutputCheckSum(const char *filename){
	FILE *file = fopen(filename,"w");
	int dimen = img1->get_w()*img1->get_h();
	int i;
	for (i = 0; i< dimen;i++){
		red += img1->getData()[3*i];
		green += img1->getData()[3*i+1];
		blue += img1->getData()[3*i+2];
	}
	red = red %256;
	green = green %256;
	blue = blue%256;
	fprintf(file, "CHECKSUM: %d, %d, %d\n", red, green, blue);
	fclose(file);
}