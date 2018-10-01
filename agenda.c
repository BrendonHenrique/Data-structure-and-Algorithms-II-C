#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct control{
	
	int ContadorDePessoas;
	int TotalDePessoas;
	int OpcaoDoMenu;
	int i;
	
}variaveis;

typedef struct user{
	char Nome[20];
	int Num;
	
}user;

user *ptrUser;//ptrUser//usuarioAtual
variaveis *ptrControl; 
user *aux;//aux//primeiroUsuario
void *pbuffer;


void imprimirUm(user *ptrUser){

	//for(aux->controle.ContadorDePessoas = 0 ; aux->controle.ContadorDePessoas < aux->controle.TotalDePessoas ; aux->controle.ContadorDePessoas++ ){
	printf("|Nome: %s",ptrUser->Nome);
	printf("\n|Numero: %d",ptrUser->Num); 
	ptrUser++;
	
}

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

void inserir(user  *ptrUser){


	printf("\n|=========================[Inserir]=======================|\n");
	
	ptrControl->TotalDePessoas++;
		
	pbuffer = realloc(pbuffer,(sizeof(variaveis) + ptrControl->TotalDePessoas * sizeof(user)));
	
	ptrUser = pbuffer+sizeof(variaveis);
	
	aux = ptrUser;
	ptrControl = pbuffer;
	
	
	for (ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1; ptrControl->ContadorDePessoas++){
		ptrUser++;
	}
	
	
	ptrControl->ContadorDePessoas = 0 ; 
	
	printf("|Nome:");
	scanf("%s",ptrUser->Nome);
	printf("|Numero:");
	scanf("%d",&ptrUser->Num);
	//imprimirUm(ptrUser);
	printf("|=========================================================|\n");
}

int main(int argc, char const *argv[])
{
	
	pbuffer = malloc(sizeof(variaveis));
	ptrControl = pbuffer;
	
	if(pbuffer == NULL){
		return -1;
	}

	ptrUser = pbuffer ;
	ptrControl->ContadorDePessoas = 0 ; 
	ptrControl->TotalDePessoas =  0 ; 
	
	
	for (;;){
		printf("\n|=========================[Agenda]========================|\n");
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
				return 0;
				break;
			
		}			
	}

	imprimirTodos();
	
	return 0;
}
