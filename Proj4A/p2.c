// The author believes it has <6> memory errors

#include <stdio.h>
#include <stdlib.h>

int main(){

	int var;
	int arr[3];
	arr[0] = 12;
	arr[1] = 15;
	arr[2] = 18;
	var = arr[3];


	char *ptr;

	ptr =  (char *)malloc(sizeof(char)*11);

	free (ptr);
	free (ptr);

	int array[3];
	array[0] = 12;
	array[1] = 5;
	array[2] = 6;

	free (array);

	char *ptr1 = NULL;
	printf("%s\n", ptr1);
	ptr1[1] = 'Q';


	int *ptr3 = malloc(3*sizeof(int));
	int var1 = ptr[3];

};
