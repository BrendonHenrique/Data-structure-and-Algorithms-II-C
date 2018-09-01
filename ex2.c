#include <stdio.h>
#include <stdlib.h>


int * createVet(int n){

	int *pont;
	pont = (int*)malloc(n*sizeof(int));

	for (int i = 0; i < n; i++)
	{
		printf("[%d] - > ",i+1);
		scanf("%d",&(*(pont+i)));
	}

	return pont;
}

void printVet(int n,int *pont){

	for (int i = 0; i < n; i++)
	{
		printf("\n[%d] - > %d",i+1,*(pont+i));
	}
}

void freeVet(int *pont){
	free(pont);
}

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d",&n);
	int *ptr;

	ptr = createVet(n);
	printVet(n,ptr);
	freeVet(ptr);

	return 0;
}