#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct control{
	
	int ContadorDePessoas; 
	int ContadorDeExclusao;
	int TotalDePessoas;
	int OpcaoDoMenu;
	int i;
	char NomeDeBusca[20];
	char NomeDeExclusao[20];
	bool NaoEncontrado;

}variaveis;

//Struct para armazenar nome e numero
typedef struct user{
	char Nome[20];
	char Num[10];
	
}user;

user *ptrUser;//usuarioAtual
variaveis *ptrControl; 
user *aux;//primeiroUsuario
void *pbuffer;


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
		printf("| 5-Sair\n");
		printf("|=========================================================|\n");
		
		printf("|Selecione uma das opcoes: ");
		
		scanf("%d",&ptrControl->OpcaoDoMenu);
		
		switch(ptrControl->OpcaoDoMenu){
			
			case 1:
				
				inserir(ptrUser);
				ptrUser = pbuffer;
				getchar();	

				break;
			
			case 2:
				
				imprimirTodos();
				break;
			
			case 3:

				buscar(ptrControl);
				break;

			case 4:

				excluir(ptrControl);
				break;

			case 5:
				
				free(pbuffer);

				return 0;
				break;
			
			default:
				
				printf("\nOpção incorreta!");
		}			
	}

	return 0;
}
