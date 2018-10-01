#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct control{
	
	int ContadorDePessoas;
	int TotalDePessoas;
	int OpcaoDoMenu;

}control;

typedef struct user{
	char Nome[20];
	int Num;
	control controle;

}user;
user *ptrUser;//ptrUser//usuarioAtual
user *aux;//aux//primeiroUsuario
void *pbuffer;


void imprimirUm(user *ptrUser){

	//for(aux->controle.ContadorDePessoas = 0 ; aux->controle.ContadorDePessoas < aux->controle.TotalDePessoas ; aux->controle.ContadorDePessoas++ ){
	printf("\nNome: %s",ptrUser->Nome);
	printf("\nNumero: %d",ptrUser->Num); 
	ptrUser++;
	
}

void imprimirTodos(){

    user *ptrAtual;
	
	ptrAtual = aux;

	for(aux->controle.ContadorDePessoas = 0 ; aux->controle.ContadorDePessoas < aux->controle.TotalDePessoas ; aux->controle.ContadorDePessoas++,ptrAtual++ ){
		printf("\nNome: %s",ptrAtual->Nome);
		printf("\nNumero: %d",ptrAtual->Num); 
	}

}

void inserir(user  *ptrUser){
	
	ptrUser->controle.TotalDePessoas++;
	
	if(ptrUser->controle.TotalDePessoas > 1){
	
		
		ptrUser = realloc(ptrUser,(ptrUser->controle.TotalDePessoas * sizeof(user)));
		aux = ptrUser;

		printf("ops aux: %u\n",aux);
		
		for (aux->controle.ContadorDePessoas = 0; aux->controle.ContadorDePessoas < ptrUser->controle.TotalDePessoas; aux->controle.ContadorDePessoas++){
			ptrUser++;
		}
	}else{
		aux = ptrUser;
		
		printf("ops aux: %u\n",aux);
	}

	printf("Nome:");
	scanf("%[^\n]",ptrUser->Nome);
	printf("Numero:");
	scanf("%d",&ptrUser->Num);
	//imprimirUm(ptrUser);
	ptrUser++;
}


int main(int argc, char const *argv[])
{
	
	pbuffer = malloc(sizeof(user));
	
	if(pbuffer == NULL){
		return -1;
	}

	ptrUser = pbuffer ;
	ptrUser->controle.TotalDePessoas = 0 ; 
	
	
	for (int i = 0; i < 3; i++){
		inserir(ptrUser);
		getchar();	
	}


	imprimirTodos();

	
	return 0;
}
