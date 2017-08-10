#include <logging.h>
#include <stdio.h>

DataFlowException::DataFlowException(const char *type, const char *error){
	sprintf(this->msg,"Throwing exception: (%s): %s", type, error);
	Logger::LogEvent(this->msg);
}

FILE *Logger::logger = fopen("testlogging", "w");//tester can change the file name 

void
Logger::LogEvent(const char *event){
	fprintf(logger, "%s\n", event);
}

void 
Logger::Finalize(){
	fclose(logger);
}