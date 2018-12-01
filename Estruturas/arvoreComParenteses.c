#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	struct NO* esq;
	struct NO* dir;
};

typedef struct NO conteudo;
typedef struct NO* nodo;
typedef struct NO** raiz;

raiz cria_arvore(){

	raiz MinhaRaiz = (raiz)malloc(sizeof(nodo));//MinhaRaiz é uma raiz e ela guarda nodo  
	if(MinhaRaiz == NULL)return 0;

	*MinhaRaiz = NULL;//O conteudo da MinhaRaiz recebe NULL;
	return MinhaRaiz;
}

int insereNodo(raiz MinhaRaiz,int valor){
	
	if(MinhaRaiz==NULL)return 0;//testa a raiz passada

	nodo novoNodo = (nodo)malloc(sizeof(conteudo));//novoNodo é um nodo que armazena um conteudo

	if(novoNodo == NULL)return 0;

	novoNodo->info = valor;
	novoNodo->esq = NULL;
	novoNodo->dir = NULL;

	if(*MinhaRaiz == NULL){//Se o conteudo é igual a null então a raiz foi criada, mas ta vazia
		*MinhaRaiz = novoNodo;	
	}else{

		nodo ant = NULL;
		nodo atual = *MinhaRaiz;

		while(atual!=NULL){

			ant = atual;

			if(atual->info == valor){//Verifico se eu já possuo o valor inserido , se sim não irei duplica-lo
				free(novoNodo);//descarto o valor
				return 0;
			}
			if(valor > atual->info){//Se o valor que eu quero inserir é maior que o atual caminho pra direita se não esquerda 
				atual = atual->dir;
			}else{
				atual = atual->esq;
			}
		}//ao fim do laço eu encontro a posição correta pra inserir
		//sendo que ant está guardando a posição a qual devo inserir , e atual está em NULL e portanto não entra no laço

		if(valor > ant->info){
			ant->dir = novoNodo;
		}else{
			ant->esq = novoNodo;
		}
	}
	return 1;
}

int preOrdem(raiz MinhaRaiz){
	if(MinhaRaiz == NULL)return 0;

	int a=1;
	int b=1;

	if(*MinhaRaiz !=NULL){

		printf("(");
		printf("%d",(*MinhaRaiz)->info);
		a=preOrdem(&((*MinhaRaiz)->esq));
		b=preOrdem(&((*MinhaRaiz)->dir));
		if(a==0 && b==0)printf("()");
		if(a==0 && b!=0)printf("()");
		if(a!=0 && b==0)printf("()");
     	
	}else{
		return 0;
	}
	printf(")");

}

int main(int argc, char const *argv[])
{	
	int vet[6]={50,30,20,15,35,6};

	raiz r1 = cria_arvore();//printf("%d",r1);//criada com sucesso!
	printf("%d",(sizeof(vet)/sizeof(int)));

	for (int i = 0; i < (sizeof(vet)/sizeof(int)); i++)
	{
		printf("\n%s",insereNodo(r1,vet[i])?"true":"false");
	}
	printf("\n");

	preOrdem(r1);

	return 0;
}
