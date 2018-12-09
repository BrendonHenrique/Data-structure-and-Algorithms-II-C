#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLACK 0
#define RED 1

struct no{
	int valor;
	int color;
	struct no* esq;
	struct no* dir;
	struct no* pai;
};
typedef struct no no;
typedef struct no* nodo;
typedef struct no** raiz;

nodo pai = NULL;

raiz cria(){
	raiz newRaiz = (raiz) malloc(sizeof(nodo));
	if(newRaiz == NULL)
		return 0;
	*newRaiz = NULL;
	return newRaiz;
}
nodo GetAvo(nodo no){
	if(no == NULL && no->pai == NULL)
		return NULL;

	return no->pai->pai;
}
nodo GetTio(nodo no){
	if(no == NULL)
		return NULL;

	nodo avo = GetAvo(no);

	if(avo == NULL) 
		return NULL;

	if(no->pai == avo->esq){
		return avo->dir;
	}else{
		//se nao é o filho a esquerda
		return avo->esq;
	}
}
void RotacaoL(nodo no){
	nodo aux = no->esq;
	no->esq = aux->dir;
	aux->dir =  no;
	no = aux;
}
void RotacaoR(nodo no){
	nodo aux = no->dir;
	no->dir = aux->esq;
	aux->esq = no;
	no = aux;
}
void insert(nodo no){
	if(no->pai == NULL || no->pai->color == BLACK){
		no->color = BLACK;
	}else{
		
		nodo u = GetTio(no);
		nodo g = GetAvo(no);

		if((u != NULL) && (u->color == RED)){
			no->pai->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			
			if(no->pai == NULL)
				no->color = BLACK;
		}else{
	
			nodo g = GetAvo(no);
			
			if((no == no->pai->dir) && (no->pai == g->esq)){
				RotacaoR(no->pai);
				no = no->dir;
			
			}else{
				no->pai->color = BLACK;
				g->color = RED;
				if((no == no->pai->esq) && (no->pai == g->esq)){
					RotacaoL(g);
				}else{
					RotacaoR(g);
				}
			}
		}
	}
}
nodo inserir(int novo,raiz p){
    if(*p == NULL){
        *p = malloc(sizeof(no));
        (*p)->valor = novo;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        (*p)->pai = pai;
        return *p;
    }
    else if(novo < (*p)->valor){
        pai = *p;
        inserir(novo,&(*p)->esq);
        return *p;
    }
    else if(novo > (*p)->valor){
        pai = *p;
        inserir(novo,&(*p)->dir);
        return *p;
    }
}
void imprimePre(raiz newRaiz){
	if(*newRaiz == NULL)
		return;
	printf("\n%d",(*newRaiz)->valor);
	imprimePre(&((*newRaiz)->esq));
	imprimePre(&((*newRaiz)->dir));
}
void imprimeEm(raiz newRaiz){
	if(*newRaiz == NULL)
		return;
	imprimeEm(&((*newRaiz)->esq));
	printf("\n%d",(*newRaiz)->valor);
	imprimeEm(&((*newRaiz)->dir));
}
void imprimePos(raiz newRaiz){
	if(*newRaiz == NULL)
		return;
	imprimePos(&((*newRaiz)->esq));
	imprimePos(&((*newRaiz)->dir));
	printf("\n%d",(*newRaiz)->valor);
}
bool Buscar(int valor,raiz newRaiz){

	nodo atual = *newRaiz;

 	while(atual!= NULL){
 		
 	 	if(atual->valor == valor){
	        return true;
	    }
	 
	    if(valor < atual->valor){
	    	atual = atual->esq;
	    }else{
	    	atual = atual->dir;
	    }
    }
    
    return false;
}

void cls(){
     //testa se o sistema operacional está definido como LINUX ou WINDOWS
     //código especifico para linux
     #ifdef __linux__
     printf("\e[H\e[2J");

     #elif _WIN32
     //código específico para windows
     system ("cls");
     #else
     printf("\e[H\e[2J");
     #endif
}
void menuTreeRB(){
    printf("\n|===================[Arvore Rubo Negra]===================|\n");
    printf("| 1-Inserir na Arvore\n");
    printf("| 2-Listar por Pre Ordem\n");
    printf("| 3-Listar Em Ordem\n");
    printf("| 4-Listar por Pos Ordem\n");
    printf("| 5-Buscar algum numero\n");
    printf("| 6-Sair\n");
    printf("|=========================================================|\n");
    printf("|Selecione : ");
}
int main(int argc, char const *argv[])
{
	raiz newRaiz = cria();
	int x,y;


	for (;;){
		menuTreeRB();
		scanf("%d",&x);

		switch(x){
			case 1:
				cls();
				printf("\nQual numero inserir?");
				scanf("%d",&y);
    			insert(inserir(y,newRaiz));	
			break;

			case 2:	
				cls();
				imprimePre(newRaiz);
			break;
			case 3:
				cls();
				imprimeEm(newRaiz);
			break;
			case 4:
				cls();
				imprimePos(newRaiz);
			break;
			case 5:
				cls();
				printf("\nQual numero buscar?");
				scanf("%d",&y);
				printf("\n%s",Buscar(y,newRaiz) ? "Encontrado":"Nao encontrado");
			break;
			case 6:
				cls();
				printf("\nThkx ! c'u!");
				return 1;
			break;
			default:
				printf("\nEscolha incorreta!");
			break;
		}
	}

	return 0;
}
