#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define RED   1
#define BLACK 0

struct Node{
    int          value;
    char         color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

typedef struct Node No;
typedef struct Node* Node;
typedef struct Node** raiz;


No NullNode;
Node T_Nil = &NullNode;
Node newRaiz = NULL;

Node newNode(int value){

    Node temp    = (Node) malloc(sizeof(No));
    temp->value  = value;
    temp->color  = RED;
    temp->left   = NULL;
    temp->right  = NULL;
    temp->parent = NULL;

    return temp;
}

void rotateLeft( raiz newRaiz, Node aux2){

    Node aux1  = aux2->left;    
    aux2->left  = aux1->right;    
   
    if (aux1->right != T_Nil)
        aux1->right->parent = aux2;
    
    aux1->parent = aux2->parent;  
    
    if (aux2->parent == T_Nil)
       *newRaiz = aux1;
    
    else if (aux2 == aux2->parent->right)
       aux2->parent->right = aux1;
    
    else
       aux2->parent->left  = aux1;
   
    aux1->right  = aux2;         
    aux2->parent = aux1;
}

void rotateRight(raiz newRaiz, Node aux1){

    Node aux2  = aux1->right;    
    aux1->right = aux2->left;     
   
    if (aux2->left != T_Nil)
        aux2->left->parent = aux1;
   
    aux2->parent = aux1->parent;  
    
    if (aux1->parent == T_Nil)
       *newRaiz = aux2;
    
    else if (aux1 == aux1->parent->left)
       aux1->parent->left = aux2;
    
    else
       aux1->parent->right = aux2;
    
    aux2->left   = aux1;            
    aux1->parent = aux2;  
}

void FixUp(raiz newRaiz, Node New){

    Node temp;
    
    while(New->parent->color == RED){

        if(New->parent->value == New->parent->parent->value){

            temp = New->parent->parent->right;
            
            if(temp->color == RED){

                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }

            else if(New->value == New->parent->right->value){

                New = New->parent;
                rotateRight(newRaiz,New);
            }

            New->parent->color = BLACK;
            New->parent->parent->color = RED;
            rotateLeft(newRaiz,New->parent->parent);
        }
        else{

            temp = New->parent->parent->left;
            if(temp->color == RED){

                New->parent->color = BLACK;
                New->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else if(New->value == New->parent->left->value){

                New = New->parent;
                rotateLeft(newRaiz,New);
            }

            New->parent->color = BLACK;
            New->parent->parent->color = RED;
            rotateRight(newRaiz, New->parent->parent);
        }
    }
    newRaiz[0]->color = BLACK;
}

int redBlackInsert(raiz newRaiz, int value){

    Node aux3 =  newNode(value);
    Node aux2 =  T_Nil;
    Node aux1 = *newRaiz;

    while (aux1 != T_Nil) {
       aux2 = aux1;
      
       if (aux3->value < aux1->value)
          aux1 = aux1->left;
    
       else
          aux1 = aux1->right;
    }

    aux3->parent = aux2;
    
    if (aux2 == T_Nil)
       *newRaiz = aux3;

    else if (aux3->value < aux2->value)
        aux2->left  = aux3;
   
    else
        aux2->right = aux3;

    aux3->left  = T_Nil;
    aux3->right = T_Nil;
    aux3->color = RED;

    FixUp(newRaiz,aux3);

}

bool DisplayPreOrdem(raiz newRaiz){
    if(*newRaiz == NULL){
        return -1;
    }else{
        printf("%d\n",(*newRaiz)->value);
        DisplayPreOrdem(&((*newRaiz))->left);
        DisplayPreOrdem(&((*newRaiz))->right);
        
        return true;
    }
}

bool DisplayEmOrdem(raiz newRaiz){
    if(*newRaiz == NULL){
        return -1;
    }else{

        DisplayEmOrdem(&((*newRaiz))->left);
        printf("%d\n",(*newRaiz)->value);
        DisplayEmOrdem(&((*newRaiz))->right);
        return true;
    }
}

bool DisplayPosOrdem(raiz newRaiz){
    if(*newRaiz == NULL){
        return -1;
    }else{
        DisplayPosOrdem(&(*(newRaiz))->left);
        DisplayPosOrdem(&(*(newRaiz))->right);
        printf("%d\n",((*newRaiz))->value);
    }
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
    printf("|=========================================================|\n");
    printf("|Selecione : ");
}


int main(int argc, char const *argv[]){

    int choice;
    int x;

    Node Root = T_Nil;
    
    for(;;){
        
        menuTreeRB();
        scanf("%d",&choice);

        switch (choice){

            case 1:
                cls();
                printf("\nQual valor inserir?");
                scanf("%d",&x);
                redBlackInsert(&Root, x);
            break;
            case 2:
                cls();
                DisplayPreOrdem(&Root);
            break;
            case 3:
                cls();
                DisplayEmOrdem(&Root);
            break;
            case 4:
                cls();
                DisplayPosOrdem(&Root);
            break;
        }    
    }

    return 0;
}
