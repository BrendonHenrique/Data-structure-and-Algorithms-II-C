#include <stdio.h>
#include <stdlib.h>

//struct que pode conter qualquer variável , entretanto as variáveis deverão ser incluidas na memória de pbuffer
// struct that can contain any variable, however variables must be included in pbuffer memory
typedef struct control{
	
	int ContadorDePessoas; 
	int TotalDePessoas;
	int OpcaoDoMenu;
	int i;
	
}variaveis;

//Struct para armazenar nome e numero
//Struct to store name and number
typedef struct user{
	char Nome[20];
	int Num;
	
}user;

user *ptrUser;//usuarioAtual//current User
variaveis *ptrControl; 
user *aux;//primeiroUsuario //first user 
void *pbuffer;


void imprimirUm(user *ptrUser){

	printf("|Nome: %s",ptrUser->Nome);
	printf("\n|Numero: %d",ptrUser->Num); 
	
}
// function to list all 
void imprimirTodos(){
	
	printf("\n|=========================[Listar]========================|\n");

    user *ptrAtual;
	
	ptrAtual = aux;

	for(ptrControl->ContadorDePessoas = 0 ; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas ; ptrControl->ContadorDePessoas++,ptrAtual++ ){
		printf("\nNome: %s",ptrAtual->Nome);
		printf("\nNumero: %d\n",ptrAtual->Num); 
	}
	printf("|=========================================================|\n");
}
// function to insert  a new name and number
void inserir(user  *ptrUser){


	printf("\n|=========================[Inserir]=======================|\n");
	
	//ao inserir um usuario aumenta a variável de quantidade de pessoas
	//at inserting a new user , ptrControl->TotalDePessoas are incressing by one 
	ptrControl->TotalDePessoas++;

	//realocação de memória em pbuffer , o qual irá receber a primeira posição das variáveis mais a quantidade total de pessoas vezes o tamanho de usuarios		
	// memory relocation in pbuffer, which will receive the first position of the variables plus the total amount of people times the size of users
	pbuffer = realloc(pbuffer,(sizeof(variaveis) + ptrControl->TotalDePessoas * sizeof(user)));

	//ptrUser aponta pra pbuffer e pula a primeira posição que é a das variáveis de controle	
	// ptrUser points to pbuffer and skips the first position that actually is that of control variables
	ptrUser = pbuffer+sizeof(variaveis);
	
	// aux recebe a posição de ptrUser para o ponteiro não perder a referência da primeira posição de usuarios
	//aux receives the position of ptrUser so the pointer does not lose the reference of the first position of users
	aux = ptrUser;

	//ptrControl também aponta pra pbuffer porém , ele aponta para a posição a qual tem as variáveis 
	// mesmo caso que ptrUser porém o ptrUser aponta pra posição a frente das variáveis , as quais o ptrControl manipula
	// ptrControl also points to pbuffer however, it points to the position which has the variables
	// even if ptrUser however the ptrUser points to the forward position of the variables, which ptrControl manipulates
	ptrControl = pbuffer;
	
	//Faz um loop em ptrUser  , até que ptrControl->ContadorDePessoas vá de 0 , até ptrControl->TotalDePessoas-1 , ou seja , até o ultimo usuario inserido 
	// Loops in ptrUser, until ptrControl-> Person Counter goes from 0 to ptrControl-> TotalPeople-1, that is , until the last user inserting

	for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1; ptrControl->ContadorDePessoas++,ptrUser++){}

	printf("|Nome:");
	scanf("%s",ptrUser->Nome);
	printf("|Numero:");
	scanf("%d",&ptrUser->Num);
	printf("|=========================================================|\n");
}

int main(int argc, char const *argv[])
{
	
	//aloca a primeira posição de memória de pbuffer para caber as variaveis que estão na struct variaveis
	// allocates a first position of pbuffer memory to fit as variables that are in the variable structure
	pbuffer = malloc(sizeof(variaveis));

	//ptrControl aponta para a posição alocada para as variaveis
	// ptrControl points to the position allocated to the variables
	ptrControl = pbuffer;
	
	// testa se pbuffer conseguiu alocar
	// test if pbuffer was able to allocate
	if(pbuffer == NULL){
		return -1;
	}
	
	// Inicializa contador de pessoas e total de pessoas
	// Initialize counter of people and total of people
	ptrControl->ContadorDePessoas = 0 ; 
	ptrControl->TotalDePessoas =  0 ; 
	
	
	for (;;){
		printf("\n|=========================[Agenda]========================|\n");2
		printf("| 1-Novo contato\n");
		printf("| 2-Listar contatos\n");
		printf("| 3-Sair\n");
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
				
				free(pbuffer);
				free(ptrUser);
				free(ptrControl);

				return 0;
				break;
			
			default:
				
				printf("\nOpção incorreta!");

		}			
	}

	return 0;
}
