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

	for (ptrControl->j = 1; ptrControl->j < ptrControl->TotalDePessoas ; ptrControl->j++)
	{

		strcpy(ptrControl->temporario,ptrUser[ptrControl->j].Nome);

		ptrControl->i = ptrControl->j - 1 ;

		while(ptrControl->i >= 0 )
		{	

			if((strcmp(ptrUser[ptrControl->j].Nome,ptrControl->temporario))<=0){
				break;
			}
		
			strcpy(ptrUser[ptrControl->i + 1].Nome,ptrUser[ptrControl->i].Nome);
			ptrControl->i = ptrControl->i - 1;

		}
		strcpy(ptrUser[ptrControl->i+1].Nome , ptrControl->temporario);

	}

}

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
					printf("| Existe apenas 1 usuario impossivel ordenar");
				}

				break;

			case 6:

				cls();
				if(ptrControl->ContadorDePessoas > 0 ){
				SelectionSort(ptrControl);
				}else{
					printf("| Existe apenas 1 usuario impossivel ordenar");
				}
				
				break;
	
			case 7:
				cls();
				InsertionSort(ptrControl);
				
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
