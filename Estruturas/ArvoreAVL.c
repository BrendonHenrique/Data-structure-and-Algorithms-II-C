#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct NO{
	int dados;
	//Dado Adcional para Arvore AVL Com a Altura  é possível saber se é necessário ou não balancear.
	int altura;
	struct NO* left;
	struct NO* right;
};

typedef struct NO Nodo; 
typedef struct NO* Raiz; 

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

void menuTreeAVL(){
    printf("\n|====================[Schedule Queue]=====================|\n");
    printf("| 1-Criar Arvore\n");
    printf("| 2-Liberar Arvore\n");
    printf("| 3-Altura Arvore\n");
    printf("| 4-Total de Nodos\n");
    printf("| 5-Listar por Pre Ordem\n");
    printf("| 6-Listar Em Ordem\n");
    printf("| 7-Listar por Pos Ordem\n");
    printf("| 8-Inserir na Arvore AVL\n");
    printf("|=========================================================|\n");
    printf("|Select a number: ");
}

//retorna ponteiro para ponteiro , para o head da arvore.
Raiz* cria_Arvore(){

	Raiz* raiz = (Raiz*)malloc(sizeof(Raiz));
	//conteudo do ponteiro p/ ponteiro recebe NULL
	(*raiz) == NULL;
	
	//raiz é igual a null, se sim retorna null (Não foi possível criar a raiz), se não retorna a raiz criada
	return (raiz==NULL)?  NULL : raiz;	
}
bool libera_NO(Nodo* Nodo){

	if(Nodo == NULL) return false;

	//liberação do nó é feita em Pós ordem
	libera_NO(Nodo->left);
	libera_NO(Nodo->right);
	free(Nodo);
	Nodo = NULL;

	return true;
}
bool libera_Arvore(Raiz* raiz){
	if(raiz == NULL) return false;
	
	libera_NO(*raiz);
	free(raiz);

	return true;
}
bool isVazia(Raiz* raiz){
	//se raiz == NULL a arvore não foi criada corretamente.
	//se (*raiz) == NULL a arvore foi criada porém o conteúdo da arvore está vazio, ou seja NULL.
	return (raiz == NULL)||((*raiz) == NULL)? true:false;
}
int altura_Nodo(Nodo* No){
	if(No == NULL) return -1;
	return No->altura;
}
int altura_Arvore(Raiz* raiz){
	if(isVazia(raiz)){ 
		return -1;
	}else{
		//Contagem de nós feita por pós ordem
		int altura_left = altura_Arvore(&((*raiz)->left));
		int altura_right = altura_Arvore(&((*raiz)->right));
		return (altura_left > altura_right )? altura_left +1 : altura_right +1;  
	}
}
int totalNO_ArvBin(Raiz* raiz){
	if(isVazia(raiz)){
		return -1;
	}else{
		//Contagem de nós feita por pós ordem
		int altura_left = altura_Arvore(&((*raiz)->left));
		int altura_right = altura_Arvore(&((*raiz)->right));
		//Se eu passar só (*raiz)->left ou right ele tentar passar o conteúdo, porém eu preciso passar o endereço de memória  
		return (altura_right + altura_left + 1);	
	}
}
bool insere_NovaFolha(Raiz* raiz,int valor){
	if(raiz == NULL) return false;

	Nodo* NovaFolha;
	NovaFolha = (Nodo*) malloc(sizeof(Nodo));

	if(NovaFolha==NULL) return false;

	NovaFolha->dados = valor;
	NovaFolha->left = NULL;
	NovaFolha->right = NULL;

	if((*raiz) == NULL){
		*raiz = NovaFolha;//Caso a Arvore esteja criada mas vazia		
	}else{//caso que não esteja vazia

		Nodo* atual = (*raiz);
		Nodo* anterior = NULL;

		while(atual != NULL){

			anterior = atual;

			if(valor == atual->dados){
				free(NovaFolha);
				return false; //Se o valor já possui na arvore eu o descarto
			}

			if(valor > atual->dados)
				atual = atual->right;
			else
				atual = atual->left;
		
		}//loop até encontrar a posição para inserir ou um valor igual
		//ao final do loop atual estará em null , e ant estará na ultima posição 
		if(valor > anterior->dados)
			anterior->right = NovaFolha;
		else
			anterior->left = NovaFolha;
	}

	return true;
}
//Displays da arvore
bool DisplayPreOrdem(Raiz* raiz){
	if(isVazia(raiz)){
		return -1;
	}else{

		printf("%d\n",(*raiz)->dados);
		DisplayPreOrdem(&((*raiz))->left);
		DisplayPreOrdem(&((*raiz))->right);
		
		return true;
	}
}
bool DisplayEmOrdem(Raiz* raiz){
	if(isVazia(raiz)){
		return -1;
	}else{

		DisplayEmOrdem(&((*raiz))->left);
		printf("%d\n",(*raiz)->dados);
		DisplayEmOrdem(&((*raiz))->right);
		return true;
	}
}
bool DisplayPosOrdem(Raiz* raiz){
	if(isVazia(raiz)){
		return -1;
	}else{
		DisplayPosOrdem(&(*(raiz))->left);
		DisplayPosOrdem(&(*(raiz))->right);
		printf("%d\n",((*raiz))->dados);
	}
}
int maior(int n1,int n2){
	return (n1>n2)? n1:n2;
}
int fatorDeBalanceamento(Nodo* No){
	//labs retorna o valor absoluto da diferença
	return labs(altura_Nodo(No->left) - altura_Nodo(No->right));
}
void SimpleTurnLeft(Raiz* raiz){
	
	Nodo* nodo = (*raiz)->left;
	(*raiz)->left = nodo->right;
	nodo->right = (*raiz);

	(*raiz)->altura = maior(altura_Nodo((*raiz)->left),altura_Nodo((*raiz)->right)) + 1;
	nodo->altura = maior(altura_Nodo(nodo->left) , (*raiz)->altura)+1;

	*raiz = nodo;
}
void SimpleTurnRight(Raiz* raiz){

	Nodo* nodo = (*raiz)->right;
	(*raiz)->right = nodo->left;
	nodo->left = (*raiz);

	(*raiz)->altura = maior(altura_Nodo((*raiz)->left),
		altura_Nodo((*raiz)->right)) + 1;
	
	nodo->altura = maior(altura_Nodo(nodo->right) ,
	 (*raiz)->altura)+1;

	*raiz = nodo;
}
void DoubleTurnLeft(Raiz* raiz){
	SimpleTurnRight(&(*raiz)->left);
	SimpleTurnLeft(raiz);
}
void DoubleTurnRight(Raiz* raiz){
	SimpleTurnLeft(&(*raiz)->right);
	SimpleTurnRight(raiz);
}
bool Insere_ArvAVL(Raiz* raiz,int valor){
	
	int res;
    
    if(*raiz == NULL){
        
        Nodo* newNodo;
        newNodo = (Nodo*)malloc(sizeof(Nodo));

        if(newNodo == NULL)return false;

        newNodo->dados = valor;
        newNodo->altura = 0;
        newNodo->left = NULL;
        newNodo->right = NULL;
        *raiz = newNodo;
        
        return true;
    }

    Nodo* atual = *raiz;
    
    if(valor < atual->dados){
        if((res = Insere_ArvAVL(&(atual->left), valor)) == 1){
            if(fatorDeBalanceamento(atual) >= 2){
                if(valor < (*raiz)->left->dados ){
                    SimpleTurnLeft(raiz);
                }else{
                    DoubleTurnLeft(raiz);
                }
            }
        }
    }else{
        if(valor > atual->dados){
            if((res = Insere_ArvAVL(&(atual->right), valor)) == 1){
                if(fatorDeBalanceamento(atual) >= 2){
                    if((*raiz)->right->dados < valor){
                        SimpleTurnRight(raiz);
                    }else{
                        DoubleTurnRight(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return false;
        }
    }

    atual->altura = maior(altura_Nodo(atual->left),altura_Nodo(atual->right)) + 1;

    return res;
}

int main(int argc, char const *argv[])
{	
	Raiz* arvore1 ;
	int x;
	int choice;
	for(;;){
		

		menuTreeAVL();
		scanf("%d",&choice);

		switch (choice){

		case 1:
			cls();
			arvore1 = cria_Arvore();
		break;
		case 2:
			cls();
			printf("\nArvore liberada ? %s",libera_Arvore(arvore1)? "true":"false");
		break;
		case 3:
			cls();
			printf("\nAltura -> %d",altura_Arvore(arvore1));
		break;
		case 4:
			cls();
			printf("\nTotal de Nodos -> %d",totalNO_ArvBin(arvore1));
		break;
		case 5:
			cls();
			DisplayPreOrdem(arvore1);
		break;
		case 6:
			cls();
			DisplayEmOrdem(arvore1);
		break;
		case 7:
			cls();
			DisplayPosOrdem(arvore1);
		break;
		case 8:
			cls();
			printf("\nQual valor inserir?");
			scanf("%d",&x);
			printf("\nInserido na arvore? %s",Insere_ArvAVL(arvore1,x) ? "true":"false");
		break;
		}
		
	}

	return 0;
}
