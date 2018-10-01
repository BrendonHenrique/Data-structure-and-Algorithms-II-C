#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estrutura.h"

void imprimir(user *ptrUser){

	
	for(aux->controle.ContadorDePessoas = 0 ; aux->controle.ContadorDePessoas < aux->controle.TotalDePessoas ; aux->controle.ContadorDePessoas++ ){
		printf("\nNome: %s",ptrUser->Nome);
		printf("\nNumero: %d",ptrUser->Num); 
		ptrUser++;
	}
}

void inserir(user  *ptrUser){
	
	
	ptrUser->controle.TotalDePessoas++;
	
	if(ptrUser->controle.TotalDePessoas > 1){
	
		ptrUser = realloc(ptrUser,(ptrUser->controle.TotalDePessoas * sizeof(user)));
		aux = ptrUser;
		
		for (aux->controle.ContadorDePessoas = 0; aux->controle.ContadorDePessoas < ptrUser->controle.TotalDePessoas; aux->controle.ContadorDePessoas++){
			ptrUser++;
		
		}
		
	}else{
		aux = ptrUser;
	}
	
		printf("Nome:");
		scanf("%[^\n]",ptrUser->Nome);
		printf("Numero:");
		scanf("%d",&ptrUser->Num);
		imprimir(aux);
		
		ptrUser++;
		
}



int main(int argc, char const *argv[])
{
	pbuffer = malloc(sizeof(user));
	ptrUser = pbuffer ;
	
	ptrUser->controle.TotalDePessoas = 0 ; 
	
	
	for (int i = 0; i < 3; i++)
	{
		printf("\nInserindo..!\n");
		inserir(ptrUser);
		getchar();	
	
	}
	
	printf("\nListando...\n");
	
	return 0;
}
