#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct element{
	int num;
	char name[20];
};

struct nodo{
	struct element data;
	struct nodo* next;
};

typedef struct nodo nodo;
typedef struct nodo* head;

head* create_list(){
	head* lista = (head*) malloc(sizeof(head));
	
	if(lista==NULL){
		return 0;
	}
	(*lista)=NULL;
	return lista;
}
bool isEmpty(head* list){
	if((*list)==NULL)return true;
	return false;
}
bool delet_list(head* list){

	if(list != NULL){
		nodo* aux;

		while((*list)->next!= NULL){
			aux = (*list);
			(*list) = (*list)->next;
			free(aux);
		}
		
		free(list);
		return true;
	}	
	return false;
}
bool insert_begining(head* list){

	if(list == NULL)return false;

	nodo* newList;
	newList = (nodo*) malloc(sizeof(nodo));
	
	if(newList==NULL)return false;

	newList->next = (*list);
	(*list) = newList;

	printf("\nNumero:");
	scanf("%d",&newList->data.num);
	printf("\nNome: ");
	scanf("%s",newList->data.name);

	return true;
}
bool insert_end(head* list){
	if(isEmpty(list)){ 
		insert_end(list);
	}else{

		nodo* aux ;
		if(aux!=NULL){ 
			aux = (*list);
			
			while(aux->next != NULL){
				aux = aux->next;
			}

			printf("\nNumero:");
			scanf("%d",&aux->data.num);
			printf("\nNome: ");
			scanf("%s",aux->data.name);
			aux->next = NULL;

		}else return false;
		
	} 
	return true;
}
bool display_list(head* list){

	if(isEmpty(list)){
		return false;
	}else{

		nodo* aux;
		aux = (*list);

		while(aux!=NULL){
			
			printf("\nNumero: %d",aux->data.num);
			printf("\nNome: %s",aux->data.name);

			aux = aux->next;
		}
		return true; 
	}
}

int main(int argc, char const *argv[])
{
	bool test;

	head* newList;
	newList = create_list();

	printf("\n%s\n",isEmpty(newList) ? "true -> isEmpty":"false -> isEmpty");
	printf("\n%s\n",insert_begining(newList) ?  "true -> Insert Beginning":"false -> Insert Beginning");
	printf("\n%s\n",insert_begining(newList) ?  "true -> insert end":"false -> insert end");	
	printf("\n%s\n",display_list(newList) ?  "true -> display list":"false -> display list");
	printf("\n%s\n",delet_list(newList) ?  "true -> isEmpty":"false -> isEmpty");
			

	return 0;
}
