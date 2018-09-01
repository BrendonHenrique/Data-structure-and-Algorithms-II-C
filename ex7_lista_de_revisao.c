#include <stdio.h>
#include <stdlib.h>

void procuraDuplicados(int vector[],int num){
	
	int vet_dest[num];
	int count = 0,j = 0 ; 

	for(int m = 0; m < num; m++)
 	{
 		for(int k = m+1 ; k < num; k++)
 		{
			if(vector[m] == vector[k])
			{
				count++;
			}

 		}
		if(count<1)
		{
			vet_dest[j] = vector[m];
			j++;
		}	
		count = 0 ;
 	}

 	printf("\nVetor sem repeticoes\n");
 	for (int i = 0; i < j; i++)
 	{
 		printf("%d\n",vet_dest[i]);
 	}
 	system("pause");
}

 int main(int argc, char const *argv[])
 {
 	int vet[10];
 	int n;
 	
 	printf("n:");
 	scanf("%d",&n);
	
	printf("\nVetor:\n");
 	
 	for (int i = 0; i < n; i++)
 	{
 	 	scanf("%d",&(*(vet+i)));
 	} 

 	procuraDuplicados(vet,n);
 	
 	return 0;
 }
