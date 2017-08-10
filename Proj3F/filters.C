#include <filters.h>
#include <stdio.h>

void 
Filters::Update()
{
	if(img1 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        img1->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
	if(img2 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        img2->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }

	char msg[1024];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}
void 
Shrinker::Execute(){
	Image *input = GetImage1();
	Image *output = GetOutput();
	if(input == NULL){
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int half_w = (int)input->get_w()/2;
	int half_h = (int)input->get_h()/2;
	output->SetSize(half_w,half_h);
	output->setData(half_w,half_h);
	
    int i, j;
    for (i=0; i< half_w;i++){
    	for(j =0;j<half_h;j++){
    		output->getData()[3*(j*half_w+i)] = input->getData()[3*(4*j*half_w + 2*i)];
    		output->getData()[3*(j*half_w+i)+1] = input->getData()[3*(4*j*half_w + 2*i)+1];
    		output->getData()[3*(j*half_w+i)+2] = input->getData()[3*(4*j*half_w + 2*i)+2];
    	}
    }
};

void 
LRConcat::Execute(){
	Image* leftInput = GetImage1();
	Image* rightInput = GetImage2();
	if(leftInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(rightInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
	Image* output = GetOutput();

	int out_w = (int)leftInput->get_w() + (int)rightInput->get_w();
	int out_h = leftInput->get_h();
	int leftcheck = leftInput->get_w();
	int right_w = rightInput->get_w();

	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(leftInput->get_h()!=rightInput->get_h()){
		char msg[1024];
		sprintf(msg,"%s: heights must match: %d, %d", SinkName(),leftInput->get_h(),rightInput->get_h());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int i,j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(i < leftcheck){
				output->getData()[3*(j*out_w+i)] = leftInput->getData()[3*(j*leftcheck+i)];
				output->getData()[3*(j*out_w+i)+1] = leftInput->getData()[3*(j*leftcheck+i)+1];
				output->getData()[3*(j*out_w+i)+2] = leftInput->getData()[3*(j*leftcheck+i)+2];
			}else{
				output->getData()[3*(j*out_w+i)] = rightInput->getData()[3*(j*right_w+(i-leftcheck))];
				output->getData()[3*(j*out_w+i)+1] = rightInput->getData()[3*(j*right_w+(i-leftcheck))+1];
				output->getData()[3*(j*out_w+i)+2] = rightInput->getData()[3*(j*right_w+(i-leftcheck))+2];
			}
		}
	}

};

void 
TBConcat::Execute()
{
	Image *topInput = GetImage1();
	Image *bottomInput = GetImage2();
	Image *output = GetOutput();
	if(topInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(bottomInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

	int out_h = (int)topInput->get_h() + (int)bottomInput->get_h();
	int topcheck = topInput->get_h();
	int out_w = topInput->get_w();
	output->SetSize(out_w,out_h);
	output->setData(out_w,out_h);
	if(topInput->get_w()!=bottomInput->get_w()){
		char msg[1024];
		sprintf(msg,"%s: widths must match: %d, %d", SinkName(),topInput->get_w(),bottomInput->get_w());
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	int i, j;
	for(i = 0; i < out_w; i++){
		for (j=0;j<out_h; j++){
			if(j < topcheck){
				output->getData()[3*(j*out_w+i)] = topInput->getData()[3*(j*out_w+i)];
				output->getData()[3*(j*out_w+i)+1] = topInput->getData()[3*(j*out_w+i)+1];
				output->getData()[3*(j*out_w+i)+2] = topInput->getData()[3*(j*out_w+i)+2];
			}else{
				output->getData()[3*(j*out_w+i)] = bottomInput->getData()[3*((j-topcheck)*out_w+i)];
				output->getData()[3*(j*out_w+i)+1] = bottomInput->getData()[3*((j-topcheck)*out_w+i)+1];
				output->getData()[3*(j*out_w+i)+2] = bottomInput->getData()[3*((j-topcheck)*out_w+i)+2];
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
	Image *input1 = GetImage1();
	Image *input2 = GetImage2();
	Image *output = GetOutput();
	if(input1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL){
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

	int out_w = input1->get_w();
	int out_h = input1->get_h();
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
       
    		output->getData()[3*(j*out_w+i)] = input1->getData()[3*(j*out_w+i)]*factor + input2->getData()[3*(j*out_w+i)]*fac2;
    		output->getData()[3*(j*out_w+i)+1] = input1->getData()[3*(j*out_w+i)+1]*factor + input2->getData()[3*(j*out_w+i)+1]*fac2;
            output->getData()[3*(j*out_w+i)+2] = input1->getData()[3*(j*out_w+i)+2]*factor + input2->getData()[3*(j*out_w+i)+2]*fac2;

    	}
    }
};