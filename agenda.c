#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void *pbuffer;

	
typedef struct controle{
	
	int contador;
	int tamanho;
	int opcao;

}control;

typedef struct cadastro{
	char nome[20];
	int num;

}user;

void inserir(control *ptrControl){

	user *ptrUser;
	
	ptrControl->tamanho+=1;
	
	pbuffer = realloc(pbuffer,(sizeof(control) + ptrControl->tamanho * sizeof(user)));
	ptrUser = pbuffer + sizeof(control) + sizeof(user)*ptrControl->tamanho;
	
	printf("Nome:");
	scanf("%[^\n]",ptrUser->nome);
	
	printf("\nNumero:");
	scanf("%d",&ptrUser->num);

}

void imprimir(control *ptrControl){

	user *ptrUser;
	ptrUser = pbuffer+sizeof(control) ;
	printf("%d\n", ptrControl->tamanho);
	for (ptrControl->contador = 0 ; ptrControl->contador < ptrControl->tamanho ; ptrControl->contador++ )
	{
		printf("Nome: %s",ptrUser->nome);
		printf("\nNumero: %d",ptrUser->num);
		ptrUser = pbuffer + sizeof(control) + ((1+ptrControl->contador)*sizeof(user));


	}

}


int main(int argc, char const *argv[])
{
	pbuffer = malloc(sizeof(control));

	control *ptrControl;

	ptrControl = pbuffer ;

	ptrControl->contador = 0 ;
	ptrControl->tamanho = 0; 

	int  *aux;
	aux = malloc(sizeof(int));

	for (;;){
			
			printf("\n(1) Inserir\n(2) Listar\nOpcao ->");
			scanf("%d",aux);
			switch (*aux){
				
				case 1:
					printf("Inserindo..!\n");
					inserir(ptrControl);

				case 2:
					printf("Listando...\n");
					imprimir(ptrControl);

			}

	
		}	
	
	

	return 0;
}
