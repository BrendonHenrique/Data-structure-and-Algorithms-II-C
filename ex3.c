#include <stdio.h>
#include <stdlib.h>

int** criaMatriz(int n, int m){

	int **mat;

	mat = (int **) malloc( m * sizeof(int*));
	
	for (int i = 0; i < m; ++i)
	{
		mat[i] = (int*) malloc( n * sizeof(int));
	}

	printf("Matriz criada!\n");
	return mat;

}

void liberaMatriz(int **mat,int m){

	for (int i = 0; i < m; ++i)
	{
		free(mat[i]);
	}

	free(mat);
	printf("Matriz liberada!\n");
}

int main(int argc, char const *argv[])
{
	int m=2, n=2;
	int **ptr;

	ptr = criaMatriz(m,n);
	liberaMatriz(ptr,m);
	

	return 0;
}