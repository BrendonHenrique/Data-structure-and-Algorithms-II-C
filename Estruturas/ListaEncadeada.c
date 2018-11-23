#include <stdio.h>
#include <stdlib.h>

struct elementos {

	int num;
	char nome[20];

};

struct nodo{
	struct elementos dados;
	struct nodo* prox;
};

typedef struct nodo nodo;
typedef struct nodo* lista;

lista* cria_lista(){

	lista* li = (lista*) malloc(sizeof(lista));

	if(li!=NULL)
		*li = NULL;
	
	return li;
}
void libera_lista(lista* li){

	if(li!=NULL){

		nodo* aux;

		while((*li)!=NULL){
			aux = (*li);
			(*li)=(*li)->prox;
			free(aux);
		}
		free(li);
	}
}
int lista_naoIniciada(lista *li){
	if(li==NULL)
		return 1;
	
	return 0;
}
int lista_vazia(lista *li){
	if((*li)==NULL)
		return 1;
	
	return 0;
}
int inserir_inicio(lista *li){

	if(li!=NULL){

		nodo* newNodo = (nodo*) malloc(sizeof(nodo));

		if(newNodo!=NULL){

			printf("\nNumero do novo nodo:");
			scanf("%d",&newNodo->dados.num);
			printf("\nNome do novo nodo:");
			scanf("%s",newNodo->dados.nome);

			newNodo->prox = (*li);//o próximo nodo de newNodo é o primeiro nodo ou seja o conteúdo de li
			(*li) = newNodo;//
		}else{
			return 0;	
		}
	}else{
		return 0;
	}

	return 1;
}
int inserir_final(lista* li){

	if(lista_naoIniciada(li)){
		printf("\nnao iniciada!");
		return 0;

	}else{	
		nodo* aux;
		aux = (*li);

		while(aux->prox != NULL){
			aux = aux->prox;
		}//encontrei o ultimo

		nodo* newNodo = (nodo*) malloc(sizeof(nodo));
		if(newNodo!=NULL){//crie um novo nodo e o preenche

			printf("\nNumero do novo nodo:");
			scanf("%d",&newNodo->dados.num);
			printf("\nNome do novo nodo:");
			scanf("%s",newNodo->dados.nome);
		
			aux->prox = newNodo;
			newNodo = NULL;
			
			return 1;
		}
	}

	printf("\nNao inserido!");
	return 0;
}
int imprimir_lista(lista *li){

	if(lista_naoIniciada(li))
		return 0;
	if(lista_vazia(li))
		return 0;
	
	nodo* aux;
	int cont = 1 ;
	aux = (*li);

	while(aux!=NULL){
		printf("\n[#%d]\n[#Nome]->%s\n[#Num]->%d\n",
			cont,aux->dados.nome,aux->dados.num);

		cont++;
		aux = aux->prox;
	}


	return 1;
}

char* resultado(int y){
	if(y == 0) { return "Sucess\n"; }else{  return "Fail\n";}
}

int main(int argc, char const *argv[])
{
	int x;
	
	lista* newList;
	newList = cria_lista();
	printf("\nEnd da nova lista->%p\n",newList);

	for (int i = 0; i < 3; ++i)
	{
		if(i==0){
			x =inserir_inicio(newList);
			if(x==1){
				printf("\nInserido com sucesso\n");
			}else{
				printf("\nFalha ao inserir\n");
			}
		}
		else{
			x = inserir_final(newList);
			if(x==1){
				printf("\nInserido com sucesso\n");
			}else{
				printf("\nFalha ao inserir\n");
			}
		}
	}

	imprimir_lista(newList);
	libera_lista(newList);
	x = imprimir_lista(newList);

	printf("%s",resultado(x));

	return 0;
}
