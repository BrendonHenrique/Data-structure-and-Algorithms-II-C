#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void lerVet(int *p, int n){

	for (int i = 0; i < n; i++)
	{
		printf("[%d] - > ",i+1);
		scanf("%d",&(*(p+i)));
	}

}

int main(int argc, char const *argv[])
{
	int n;
	int *vet;
	scanf("%d",&n);

	vet = (int *) malloc(n * sizeof(int));
	lerVet(vet,n);

	for (int i = 0; i < n; i++)
	{
		printf("\n[%d] - > %d",i+1,*(vet+i));
	}

	free(vet);

	return 0;
}