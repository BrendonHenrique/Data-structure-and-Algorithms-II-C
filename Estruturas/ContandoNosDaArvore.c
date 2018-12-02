#include <stdio.h>
#include <stdlib.h>

struct NO{
	int valor;
	struct NO* esq;
	struct NO* dir;
};

typedef struct NO no;
typedef struct NO* nodo;
typedef struct NO** raiz;

raiz cria_Raiz(){
	raiz novaRaiz = (raiz)malloc(sizeof(nodo));
	if(novaRaiz==NULL)return 0;

	(*novaRaiz) = NULL;
	return novaRaiz;
}
int inserirNodo(raiz MinhaRaiz,int valor){
	if(MinhaRaiz==NULL) return 0;
	nodo novoNodo = (nodo) malloc(sizeof(no));
	if(novoNodo==NULL) return 0;

	novoNodo->valor = valor;
	novoNodo->esq = NULL;
	novoNodo->dir = NULL;

	if(*MinhaRaiz == NULL){
		(*MinhaRaiz) = novoNodo;
		return 1;
	}else{

		nodo anterior = NULL;
		nodo atual = *MinhaRaiz;

		while(atual!=NULL){
			anterior = atual;

			if(atual->valor == valor){
				free(novoNodo);
				return 0;
			}

			if(valor > atual->valor){
				atual = atual->dir;
			}else{
				atual = atual->esq;
			}
		}

		if(valor > anterior->valor){
			anterior->dir = novoNodo;
		}else{
			anterior->esq = novoNodo;
		}
	}
	return 1;
}



int somaNos(raiz MinhaRaiz,int* x){
	if((*MinhaRaiz)!=NULL){

		*x += printf("_");
		somaNos(&((*MinhaRaiz)->esq),x);
		somaNos(&((*MinhaRaiz)->dir),x); 
	}
		return (*x);
}

int main(int argc, char const *argv[])
{
	int vet[11]={174,77,52,165,56,107,61,188,134,142,82};

	raiz r1 = cria_Raiz();
	
	for (int i = 0; i < (sizeof(vet)/sizeof(int)); i++)
	{
		inserirNodo(r1,vet[i]);
	}
	int *soma ;
	soma = (int*)malloc(sizeof(int));
	*soma = 0;

	somaNos(r1,soma);
	printf("\n%d",*soma);

	return 0;
}
