#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct control{	
	int ContadorDePessoas; 
	int ContadorDeExclusao;
	int TotalDePessoas;
	int OpcaoDoMenu;
	int i,j;
	char NomeDeBusca[20];
	char NomeDeExclusao[20];
	bool NaoEncontrado;
	char minimo[20],temporario[20];
	int minimo_id;

}variaveis;

//Struct para armazenar nome e numero
typedef struct user{
	char Nome[20];
	char Num[10];
}user;

//Variaveis globais 
user *ptrUser;//usuarioAtual
variaveis *ptrControl; 
user *aux;//primeiroUsuario
void *pbuffer;






/* Funções de controle */

// imprime apenas o  usuario passado pelo parametro   
void imprimirUm(user *ptrUser){

	printf("|Nome: %s",ptrUser->Nome);
	printf("\n|Numero: %s",ptrUser->Num); 
	
}

void imprimirTodos(){
	
	printf("\n|====================[Lista De Contatos]==================|");

    user *ptrAtual;
	
	ptrAtual = aux;

	printf("\n|---------------------------------------------------------|");

	for(ptrControl->ContadorDePessoas = 0 ; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas ; ptrControl->ContadorDePessoas++,ptrAtual++ ){
		printf("\n|Nome: %s",ptrAtual->Nome);
		printf("\n|Numero: %s",ptrAtual->Num); 
		printf("\n|---------------------------------------------------------|");
	}

	printf("\n|=========================================================|\n");
}

void inserir(user  *ptrUser){


	printf("\n|=========================[Inserir]=======================|\n");
	
	// ao inserir um usuario aumenta a variável de quantidade de pessoas
	ptrControl->TotalDePessoas++;

	//realocação de memória em pbuffer , o qual irá receber a primeira posição das variáveis mais a quantidade total de pessoas vezes o tamanho de usuarios		
	pbuffer = realloc(pbuffer,(sizeof(variaveis) + ptrControl->TotalDePessoas * sizeof(user)));

	//ptrUser aponta pra pbuffer e pula a primeira posição que é a das variáveis de controle	
	ptrUser = pbuffer+sizeof(variaveis);
	
	// aux recebe a posição de ptrUser para o ponteiro não perder a referência da primeira posição de usuarios
	aux = ptrUser;

	//ptrControl também aponta pra pbuffer porém , ele aponta para a posição a qual tem as variáveis 
	// mesmo caso que ptrUser porém o ptrUser aponta pra posição a frente das variáveis , as quais o ptrControl manipula
	ptrControl = pbuffer;
	
	//Faz um loop em ptrUser  , até que ptrControl->ContadorDePessoas vá de 0 , até ptrControl->TotalDePessoas-1 , ou seja , até o ultimo usuario inserido 
	for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1; ptrControl->ContadorDePessoas++,ptrUser++){}

	printf("|Nome:");
	scanf("%s",ptrUser->Nome);
	printf("|Numero:");
	scanf("%s",ptrUser->Num);
	printf("|=========================================================|\n");
}

void buscar (variaveis *ptrControl){
	
	printf("\n|===================[Busca De Contatos]===================|\n");
	
	// acessa a primeira posicao dos usuarios
	ptrControl->NaoEncontrado = true;

	ptrUser = pbuffer + sizeof(variaveis);
	
	printf("|Qual nome deseja procurar: ");
	scanf("%s",ptrControl->NomeDeBusca);

	
	for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas; ptrControl->ContadorDePessoas++,ptrUser++){

		if((strcmp(ptrUser->Nome,ptrControl->NomeDeBusca))==0){
		
			printf("|---------------------------------------------------------|\n");
			printf("|Usuario encontrado\n|Numero: %s",ptrUser->Num);
			printf("\n|---------------------------------------------------------|");
			ptrControl->NaoEncontrado = false;
		
			break;
		}
	}
	
	if(ptrControl->NaoEncontrado == true){
		printf("|Usuario nao encontrado");
	}
	
	printf("\n|=========================================================|\n");
}
 
void excluir(variaveis *ptrControl)
{

	ptrUser = pbuffer + sizeof(variaveis);

	ptrControl = pbuffer;

	variaveis *ptrControlTemp ;

	//printf("trocando %s por %s ",ptrUser->Nome,ptrUser->Nome+sizeof(user));
	
	if(ptrControl->TotalDePessoas > 1 )
	{
	
		printf("|Qual nome deseja excluir: ");
		scanf("%s",ptrControl->NomeDeExclusao);

		for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas; ptrControl->ContadorDePessoas++,ptrUser++)
		{
	
			if((strcmp(ptrUser->Nome,ptrControl->NomeDeExclusao))==0)
			{
				for (ptrControl->ContadorDeExclusao = ptrControl->ContadorDePessoas; ptrControl->ContadorDeExclusao < ptrControl->TotalDePessoas ; ptrControl->ContadorDeExclusao++,ptrUser++)
				{
					strcpy(ptrUser->Nome,ptrUser->Nome+sizeof(user));
					strcpy(ptrUser->Num,ptrUser->Num+sizeof(user));
				}

				ptrControl->TotalDePessoas = ptrControl->TotalDePessoas-1;
				ptrControl->ContadorDePessoas = ptrControl->ContadorDePessoas-1;		
 			}		
			
		}
		printf("\n|---------------------------------------------------------|");
		printf("\n|Usuario %s excluido!",ptrControl->NomeDeExclusao);
 		printf("\n|---------------------------------------------------------|\n");
	
	}else{

		ptrControl->TotalDePessoas = 0 ;
		printf("\n|---------------------------------------------------------|");
		printf("\n|Usuario %s excluido!",ptrUser->Nome);
		printf("\n|---------------------------------------------------------|\n");
	
	}

}


void cls()
 {
  	//Código para limpar a tela 

     #ifdef LINUX
     //código especifico para linux
     //system ("clear");//poderia ser este mas escolhi este outro pois é mais a cara do C
     printf("\e[H\e[2J");
     #elif defined WIN32
     //código específico para windows
     system ("cls");
     #else
     printf("\e[H\e[2J");
     #endif
 
 }


/*Funcoes de ordenação*/
void bubblesort (variaveis *PtrControl){
	ptrControl = pbuffer ;
	ptrUser = pbuffer + sizeof(variaveis);

	for(ptrControl->i = 0; ptrControl->i < ptrControl->TotalDePessoas - 1 ; ptrControl->i++)
	{

		for (ptrControl->j = ptrControl->i+1 ; ptrControl->j <  ptrControl->TotalDePessoas ; ptrControl->j++)
		{
	
			if((strcmp(ptrUser[ptrControl->i].Nome,ptrUser[ptrControl->j].Nome))>0)
			{

				strcpy(ptrControl->NomeDeBusca,ptrUser[ptrControl->i].Nome);
				strcpy(ptrUser[ptrControl->i].Nome,ptrUser[ptrControl->j].Nome);
				strcpy(ptrUser[ptrControl->j].Nome,ptrControl->NomeDeBusca);
			}

		}
		
	}
}

void SelectionSort(variaveis *ptrControl){

	ptrControl = pbuffer ;
	ptrUser = pbuffer + sizeof(variaveis);

	for(ptrControl->i = 0; ptrControl->i < ptrControl->TotalDePessoas - 1 ; ptrControl->i++)
	{

		strcpy(ptrControl->minimo , ptrUser[ptrControl->i].Nome);

		for (ptrControl->j = ptrControl->i+1 ; ptrControl->j <  ptrControl->TotalDePessoas ; ptrControl->j++)
		{

			if((strcmp(ptrUser[ptrControl->j].Nome,ptrControl->minimo))<0)
			{
				strcpy(ptrControl->minimo,ptrUser[ptrControl->j].Nome);
				ptrControl->minimo_id = ptrControl->j;

			}
		
		}
		strcpy(ptrControl->temporario , ptrUser[ptrControl->i].Nome);
		strcpy(ptrUser[ptrControl->i].Nome , ptrUser[ptrControl->minimo_id].Nome);
		strcpy(ptrUser[ptrControl->minimo_id].Nome, ptrControl->temporario) ;
	}
}

void InsertionSort(variaveis *ptrControl){
	
	ptrControl = pbuffer ;
	ptrUser = pbuffer + sizeof(variaveis);

	for (ptrControl->i = 1; ptrControl->i < ptrControl->TotalDePessoas ; ptrControl->i++)
	{

		strcpy(ptrControl->temporario,ptrUser[ptrControl->i].Nome);
	
		for(ptrControl->j = ptrControl->i - 1 ; ptrControl->j >= 0 ; ptrControl->j--)
		{

			if((strcmp(ptrControl->temporario,ptrUser[ptrControl->j].Nome))>=0){
				break;
			}

			strcpy(ptrUser[ptrControl->j+1].Nome,ptrUser[ptrControl->j].Nome);
		}

		strcpy(ptrUser[ptrControl->j+1].Nome , ptrControl->temporario);
	
	}

}

/*
#################### Quicksort Padrão ####################

void troca(int *a,int*b){
	int aux  = *a;
	*a = *b;
	*b = aux;
}
int particao(int arr[], int low, int high){
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1 ; j++)
	{
		if(arr[j]<= pivot){
			i++;
			troca(&arr[i],&arr[j]);
		}
	}
	troca(&arr[i+1],&arr[high]);
	return (i+1);
}
void quicksort(int arr[], int low , int high){
	if(low < high){
		int pi = particao(arr,low,high);

		quicksort(arr,low,pi-1);
		quicksort(arr,pi+1,high);
	}
}
void printArray(int arr[],int size){
	for (int i = 1; i < size; i++)
	{
		printf("%d ",arr[i]);
		printf("\n");
	}
}
int main(int argc, char const *argv[])
{
	int vet[10]= {0,4,8,9,2,5,7,3,1};

	//divide o tamanho do vetor pelo tipo de dado contido nele 
	//resulta na quantidade total de elementos no vetor
	int n = (int)(sizeof(vet)/sizeof(int));;
	quicksort(vet,0,n-1);
	printArray(vet,n);
	return 0;
}

#################### QuickSort Adaptado para Strings  ####################

void  troca( char a[],char b[]){
	char aux[20] ;
	strcpy(aux,a);
	strcpy(a,b);
	strcpy(b,aux);
}
//essa é a funcao do quicksort , entra nela a string, e inteiros do incio e do fim
void QuickSort(char strings[][20],int left , int right){
	int i,j;
	char *x;
	char temp[20];
	i = left;
	j = right;
	x = strings[(left+right)/2];
	do{
		while((strcmp(strings[i],x) <0) && (i < right)){
			i++;
		}
		while((strcmp(strings[j],x) >0) &&(j > left)){
			j--;
		}
		if(i<=j){
			troca(strings[i],strings[j]);
			i++;
			j--;
		}
	}while(i<=j);
	if(left<j){
		QuickSort(strings,left,j);
	}	
	if(i<right){
		QuickSort(strings,i,right);
	}
}
//essa funcao incializa a quicksort , entram nela a string e a quantidade de strings
void QuickSortMain(char strings[][20],int contador){
	QuickSort(strings,0,contador-1);
}
int main(int argc, char const *argv[])
{	
  int i;
  char str[][20] = { "Brendon","Carlos","Amanda","Joao"};
  QuickSortMain(str, 4);
  for(i=0; i<4; i++) {
     printf("%s ", str[i]);
  }
  
	return 0;
}

*/


int main(int argc, char const *argv[])
{
	
	//aloca a primeira posição de memória de pbuffer para caber as variaveis que estão na struct variaveis
	pbuffer = malloc(sizeof(variaveis));

	//ptrControl aponta para a posição alocada para as variaveis
	ptrControl = pbuffer;
	
	// testa se pbuffer conseguiu alocar
	if(pbuffer == NULL){
		return -1;
	}
	
	// Inicializa contador de pessoas e total de pessoas
	ptrControl->ContadorDePessoas = 0 ; 
	ptrControl->TotalDePessoas =  0 ; 
	
	
	for (;;){

		printf("\n|=========================[Agenda]========================|\n");
		printf("| 1-Novo contato\n");
		printf("| 2-Listar contatos\n");
		printf("| 3-Buscar\n");
		printf("| 4-Excluir\n");
		printf("| 5-BubbleSort\n");
		printf("| 6-SelectionSort\n");
		printf("| 7-InsertionSort\n");
		printf("| 8-Sair\n");
		printf("|=========================================================|\n");
		
		printf("|Selecione uma das opcoes: ");
		
		scanf("%d",&ptrControl->OpcaoDoMenu);
		
		switch(ptrControl->OpcaoDoMenu){
			
			case 1:
				
				cls();
				inserir(ptrUser);
				ptrUser = pbuffer;
				getchar();	

				break;
			
			case 2:
				
				cls();
				imprimirTodos();
				break;
			
			case 3:

				cls();
				buscar(ptrControl);
				break;

			case 4:

				cls();
				excluir(ptrControl);
				break;

			case 5:
				
				cls();
				if(ptrControl->ContadorDePessoas > 0 ){
					bubblesort(ptrControl);
				}else{
					printf("| Quantidade de usuarios insuficiente ");
				}

				break;

			case 6:

				cls();
				if(ptrControl->ContadorDePessoas > 0 ){
					SelectionSort(ptrControl);
				}else{
					printf("| Quantidade de usuarios insuficiente ");
				}
				
				break;
	
			case 7:
				cls();
				if(ptrControl->ContadorDePessoas > 0) {
					InsertionSort(ptrControl);
				}else{
					printf("| Quantidade de usuarios insuficiente ");
				}
				
				break;

			case 8:

				free(pbuffer);

				return 1;
				break;
					
			default:
				
				printf("\nOpção incorreta!");
		}			
	}

	return 0;
}
