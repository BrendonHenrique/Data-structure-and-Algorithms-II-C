#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct control{
	int ContadorDePessoas;
	int ContadorDeExclusao;
	int TotalDePessoas;
	int OpcaoDoMenu;
	int i,j,k,pivot_id;
	char NomeDeBusca[20];
	char NomeDeExclusao[20];
	bool NaoEncontrado;
	char minimo[20],temporario[20],temporario2[20];
	int minimo_id;
	int i_aux;
	int n1,n2,med;
	bool ordenado;

}variaveis;

typedef struct user{
	char Nome[20];
	char Num[10];
}user;

//Variaveis globais
user *ptrUser;//ptrUser é uma variável utilizada para guardar todas as informações dos usuários
variaveis *ptrControl;//ptrControl Guarda todas as variaveis utilizadas no controle dos usuários
user *aux;//aux é a variável utilizada para guardar a posição do primeiro usuário
void *pbuffer;//pbuffer é a variável a qual todos os usuários estão guardados
user *userPivot;//userPivot foi criada para auxiliar a execução do QuickSort
user *ptrUserL;//ptrUserL  foi criado para auxiliar a execução do MergeSort
user *ptrUserR;//ptrUserR  foi criado para auxiliar a execução do MergeSort


/* Funções de controle */

     //Código para limpar a tela , irá manter a tela sempre limpa, diminuindo a poluição visual e facilitando a utilização do usuário
void cls()
{

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



//imprime apenas o usuario passado como parametro
//Função está funcionando corretamente, porém cabe-se a utilização da mesma apenas para testes
void imprimirUm(user *ptrUser){
	printf("|Nome: %s",ptrUser->Nome);
	printf("\n|Numero: %s",ptrUser->Num);

}

//Essa função irá imprimir todos os usuários disponíveis na agenda
void imprimirTodos(){
	printf("\n|====================[Lista De Contatos]==================|");
    user *ptrAtual;

    //Nessa linha ptrAtual recebe o primeiro dos usuários
	ptrAtual = aux;
	printf("\n|---------------------------------------------------------|");

	//For faz dois passos diferentes , o primeiro "ptrControl->ContadorDePessoas" é uma variável de controle que faz o loop , e a segunda "ptrAtual" é o loop de posições
	for(ptrControl->ContadorDePessoas = 0 ; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas ; ptrControl->ContadorDePessoas++,ptrAtual++ ){
		printf("\n|Nome: %s",ptrAtual->Nome);
		printf("\n|Numero: %s",ptrAtual->Num);
		printf("\n|---------------------------------------------------------|");
	}
	printf("\n|=========================================================|\n");
}

//Essa função faz a inserção de um novo usuário
void inserir(user *ptrUser){
	imprimirTodos();
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
	//Esse tipo de loop é reutilizado várias vezes ao decorrer do código
	for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1; ptrControl->ContadorDePessoas++,ptrUser++){}

	printf("|Nome:");
	scanf("%s",ptrUser->Nome);
	printf("|Numero:");
	scanf("%s",ptrUser->Num);
	printf("|=========================================================|\n");
	cls();
	imprimirTodos();
}

void buscar (variaveis *ptrControl){

	imprimirTodos();
	printf("\n|===================[Busca De Contatos]===================|\n");

	//Inicialização da variável booleana para o controle da busca de usuários
	ptrControl->NaoEncontrado = true;

	// acessa a primeira posicao dos usuarios
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
		imprimirTodos();
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
//Essa função faz a troca das informações dos usuários, ela é bastante utilizada nas funções de ordenação, com isso criei uma função genérica, para re-uso do código
void troca(user *user1, user *user2){

	user auxiliar = *user1;
	*user1 = *user2;
	*user2 = auxiliar;
}

//Essa Função auxilia na implementação do QuickSort, na qual é necessário "particionar" o vetor de informações , para encontrar o pivot
//no caso dessa função , ela retorna a posição do pivot, e não o pivot propriamente dito
int particionar (user *ptrUser , int low, int high )
{
   	ptrControl->j = high;
	userPivot = &ptrUser[ptrControl->j];
    ptrControl->i = low - 1;
	for (ptrControl->j = low; ptrControl->j <= high - 1; ptrControl->j++)
    {
	    if ((strcmp(ptrUser[ptrControl->j].Nome , userPivot->Nome))<0)
        {
            ptrControl->i++;

			troca(&ptrUser[ptrControl->i],&ptrUser[ptrControl->j]);
		}
    }
	troca(&ptrUser[ptrControl->i+1],&ptrUser[high]);
	return (ptrControl->i + 1);
}

//Essa Função faz o teste de ordenação, para confirmar que de fato após o uso das funções, as informações estão realmente ordenadas
//Faço o uso dessa função apenas no Merge Sort
bool TestaOrdenacao(){
	for(ptrControl->i = 0; ptrControl->i < ptrControl->TotalDePessoas - 1 ; ptrControl->i++)
	{
		if((strcmp(ptrUser[ptrControl->i].Nome,ptrUser[ptrControl->i+1].Nome))>0){
			return  false;
		}
	}
	return  true;
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
				troca(&ptrUser[ptrControl->i],&ptrUser[ptrControl->j]);
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
		strcpy(ptrControl->temporario2 , ptrUser[ptrControl->i].Num);
		for (ptrControl->j = ptrControl->i+1 ; ptrControl->j <  ptrControl->TotalDePessoas ; ptrControl->j++)
		{
			if((strcmp(ptrUser[ptrControl->j].Nome,ptrControl->minimo))<0)
			{
				strcpy(ptrControl->minimo,ptrUser[ptrControl->j].Nome);
				strcpy(ptrControl->temporario2,ptrUser[ptrControl->j].Num);
				ptrControl->minimo_id = ptrControl->j;
			}
		}
		troca(&ptrUser[ptrControl->i],&ptrUser[ptrControl->minimo_id]);
	}
}

void InsertionSort(variaveis *ptrControl){
	ptrControl = pbuffer ;
	ptrUser = pbuffer + sizeof(variaveis);
	for (ptrControl->i = 1; ptrControl->i < ptrControl->TotalDePessoas ; ptrControl->i++)
	{
		strcpy(ptrControl->temporario,ptrUser[ptrControl->i].Nome);
		strcpy(ptrControl->temporario2,ptrUser[ptrControl->i].Num);
		for(ptrControl->j = ptrControl->i - 1 ; ptrControl->j >= 0 ; ptrControl->j--)
		{
			if((strcmp(ptrControl->temporario,ptrUser[ptrControl->j].Nome))>=0){
				break;
			}
			troca(&ptrUser[ptrControl->j+1],&ptrUser[ptrControl->j]);
		}
		strcpy(ptrUser[ptrControl->j+1].Nome , ptrControl->temporario);
		strcpy(ptrUser[ptrControl->j+1].Num , ptrControl->temporario2);
	}
}

void QuickSort (user *ptrUser ,int low , int high){
	if(low < high){
		ptrControl->pivot_id = particionar(ptrUser,low,high);
		QuickSort(ptrUser , low , ptrControl->pivot_id - 1);
		QuickSort(ptrUser , ptrControl->pivot_id + 1 , high);
	}
}

//Essa função é a inicialização da função QuickSort , eu a utilizo para evitar conflitos de tipo na recursividade do algoritimo
void QuickSortMain(void *pbuffer){
	ptrControl = pbuffer;
	ptrUser = pbuffer + sizeof(variaveis);
	QuickSort(ptrUser,0,ptrControl->TotalDePessoas-1);
}

//Essa função é chamada para Dilatar o pbuffer conforme necessário para a função merge poder criar vetores
void mergeAuxFunction(){

	pbuffer = realloc(pbuffer,
	(sizeof(variaveis) + //ptrControl
	ptrControl->TotalDePessoas * sizeof(user))+ //ptrUser
	ptrControl->n1 * sizeof(user)+ //ptrL
	ptrControl->n2 * sizeof(user) //ptrR
	);

    ptrUser = pbuffer+sizeof(variaveis);
    aux = ptrUser;
    ptrControl = pbuffer;

    //ptrUserL recebe uma posição posterior ao vetor de usuarios
    //ptrUserR recebe uma posição posterior ao vetor de ptrUserL
    ptrUserL = pbuffer + sizeof(variaveis) + ptrControl->TotalDePessoas * sizeof(user) ;
    ptrUserR = ptrUserL + ptrControl->n1 * sizeof(user);
}

void merge(user *ptrUser , int left , int medium , int right){
    ptrControl->n1 = medium - left + 1 ;
    ptrControl->n2 = right - medium;

    mergeAuxFunction();

    for (ptrControl->i = 0; ptrControl->i < ptrControl->n1; ptrControl->i++)
        ptrUserL[ptrControl->i] = ptrUser[left+ ptrControl->i];

    for (ptrControl->j = 0; ptrControl->j < ptrControl->n2; ptrControl->j++)
        ptrUserR[ptrControl->j] = ptrUser[medium + 1 + ptrControl->j];

    ptrControl->i = 0 ;
    ptrControl->j = 0 ;
    ptrControl->k = left ;
    while (ptrControl->i < ptrControl->n1 && ptrControl->j < ptrControl->n2)
    {
        if((strcmp(ptrUserL[ptrControl->i].Nome,ptrUserR[ptrControl->j].Nome))<0)
        {
            strcpy(ptrUser[ptrControl->k].Nome , ptrUserL[ptrControl->i].Nome);
            strcpy(ptrUser[ptrControl->k].Num , ptrUserL[ptrControl->i].Num);
            ptrControl->i++;

        }
        else
        {
            strcpy(ptrUser[ptrControl->k].Nome , ptrUserR[ptrControl->j].Nome);
            strcpy(ptrUser[ptrControl->k].Num , ptrUserR[ptrControl->j].Num);
            ptrControl->j++;
        }
        ptrControl->k++;
    }
    while (ptrControl->i < ptrControl->n1)
    {
        strcpy(ptrUser[ptrControl->k].Nome , ptrUserL[ptrControl->i].Nome);
        strcpy(ptrUser[ptrControl->k].Num , ptrUserL[ptrControl->i].Num);
        ptrControl->i++;
        ptrControl->k++;
    }
    while (ptrControl->j < ptrControl->n2)
    {
       strcpy(ptrUser[ptrControl->k].Nome , ptrUserR[ptrControl->j].Nome);
       strcpy(ptrUser[ptrControl->k].Num , ptrUserR[ptrControl->j].Num);
       ptrControl->j++;
       ptrControl->k++;
    }

}

void MergeSort(user *ptrUser , int left , int right){
    if(left < right){
        ptrControl->med = left + (right-left)/2;
        MergeSort(ptrUser , left , ptrControl->med);
        MergeSort(ptrUser , ptrControl->med + 1 , right);
        merge(ptrUser , left , ptrControl->med , right);
    }
}

//Assim como o QuickSort, utilizo aqui a função mergeMain , para inicialização do algoritimo de ordenação , para evitar conflito de tipos na recursividade
void mergeMain(void *pbuffer){
    ptrControl = pbuffer;
    ptrUser = pbuffer + sizeof(variaveis);
    MergeSort(ptrUser , 0 , ptrControl->TotalDePessoas -1 );
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
		printf("| 8-QuickSort\n");
		printf("| 9-MergeSort\n");
		printf("| 10-Sair\n");
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
				cls();
				imprimirTodos();

				break;

			case 5:
				cls();
				if(ptrControl->ContadorDePessoas > 0 ){
					bubblesort(ptrControl);
					cls();
					imprimirTodos();

				}else{
					cls();
					imprimirTodos();
					printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
				}

				break;

			case 6:
				cls();
				if(ptrControl->ContadorDePessoas > 0 ){
					ptrControl->ordenado = false;
					while(!ptrControl->ordenado){
						SelectionSort(ptrControl);
						ptrControl->ordenado = TestaOrdenacao();
					}
					cls();
					imprimirTodos();

				}else{
					cls();
					imprimirTodos();
					printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
								}
				break;

			case 7:
				cls();
				if(ptrControl->ContadorDePessoas > 0) {
					InsertionSort(ptrControl);
					cls();
					imprimirTodos();
				}else{
					cls();
					imprimirTodos();
					printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");

				}break;

			case 8:
				cls();
				if(ptrControl->ContadorDePessoas > 0) {
					QuickSortMain(pbuffer);
					cls();
					imprimirTodos();
				}else{
					cls();
					imprimirTodos();
					printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
				}
				break;

			case 9:
				cls();
				if(ptrControl->ContadorDePessoas > 0) {
					ptrControl->ordenado = false;
					while(!ptrControl->ordenado){
						mergeMain(pbuffer);
						ptrControl->ordenado = TestaOrdenacao();
					}
					cls();
					imprimirTodos();
				}else{
					cls();
					imprimirTodos();
					printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
				}
				break;

			case 10:
				cls();
				printf("|====================== Ate logo! :D =====================|\n");
				free(pbuffer);
				free(userPivot);
				return 1;
				break;
			

			default:
				
				printf("\nOpção incorreta!");
		}			
	}

	return 0;
}
