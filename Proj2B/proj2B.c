#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *f_in, *f_out;
	int buff_size =5 * sizeof(int);
	int *buffer1;
	int *buffer2;
	int *buffer3;
	int *buffer4;
	int *buffer5;

	if (argc != 3){
		printf("Usage: %s <file1> <file2>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	f_in = fopen(argv[1],"rb");

	

	buffer1 = malloc(buff_size);
	buffer2 = malloc(buff_size);
	buffer3 = malloc(buff_size);
	buffer4 = malloc(buff_size);
	buffer5 = malloc(buff_size);

	fseek(f_in,0,SEEK_SET);
	for (int i = 0; i <5;i++){
		fread(&buffer1[i],sizeof(int),1, f_in);
	}
	

	fseek(f_in,40,SEEK_SET);
	for (int i = 0; i <5;i++){
		fread(&buffer2[i],sizeof(int),1, f_in);
	}
	
	fseek(f_in,80,SEEK_SET);
	for (int i = 0; i <5;i++){
		fread(&buffer3[i],sizeof(int),1, f_in);
	}
	
	fseek(f_in,120,SEEK_SET);
	for (int i = 0; i <5;i++){
		fread(&buffer4[i],sizeof(int),1, f_in);
	}
	
	fseek(f_in,160,SEEK_SET);
    for (int i = 0; i <5;i++){
		fread(&buffer5[i],sizeof(int),1, f_in);
	}

	f_out = fopen(argv[2],"w");
	for (int i =0; i<5; i++){
		fprintf(f_out, "%d\n",buffer1[i]);
	}

	for (int i =0; i<5; i++){
		fprintf(f_out, "%d\n",buffer2[i]);
	}

	for (int i =0; i<5; i++){
		fprintf(f_out, "%d\n",buffer3[i]);
	}

	for (int i =0; i<5; i++){
		fprintf(f_out, "%d\n",buffer4[i]);
	}

	for (int i =0; i<5; i++){
		fprintf(f_out, "%d\n",buffer5[i]);
	}
	

	fclose(f_in);
	fclose(f_out);

	return 0;

}
