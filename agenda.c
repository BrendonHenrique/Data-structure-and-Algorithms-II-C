#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct control{
	int ContadorDePessoas;
	int ContadorDeExclusao;
	int TotalDePessoas;
	int OpcaoDoMenu,OpcaoDoMenu2;
	int i,j,k,pivot_id;
	char NomeDeBusca[20];
	char NomeDeExclusao[20];
	bool NaoEncontrado;
	char minimo[20],temporario[20],temporario2[20];
	int minimo_id;
	int i_aux;
	int n1,n2,med;
	bool ordenado;
	int TipoStruct;

}variaveis;
typedef struct user{
	char Nome[20];
	char Num[10];
}user;

//Variaveis globais
variaveis *ptrControl;
user *ptrUser,*aux,*userPivot,*ptrUserL,*ptrUserR;
void *pbuffer,*topo,*base;


//Controlhe agenda array//
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

//Imprimir Todos para tipo Stack foi implementado de forma genérica
//Deveria copiar para outro vetor , dar pop até o fim , e depois recoloca-lo MAS futuramente será implementada
void imprimirTodos(){
	user *ptrAtual;
    ptrAtual = aux;

	printf("\n|=====================[Contact List]======================|");
    printf("\n|---------------------------------------------------------|");
    for(ptrControl->ContadorDePessoas = 0 ;
    ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas ;
    ptrControl->ContadorDePessoas++,ptrAtual++ ){
        printf("\n|Nome: %s",ptrAtual->Nome);
        printf("\n|Numero: %s",ptrAtual->Num);
        printf("\n|---------------------------------------------------------|");
    }
    printf("\n|=========================================================|\n");
}
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
void excluir(variaveis *ptrControl){

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
void troca(user *user1, user *user2){

	user auxiliar = *user1;
	*user1 = *user2;
	*user2 = auxiliar;
}
int  particionar (user *ptrUser , int low, int high ){
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
bool TestaOrdenacao(){

	for(ptrControl->j = 0; ptrControl->j < ptrControl->TotalDePessoas - 1 ; ptrControl->j++)
	{
		if((strcmp(ptrUser[ptrControl->j].Nome,ptrUser[ptrControl->j+1].Nome))>0){
			return  false;
		}
	}
	return  true;
}

//Controlhe agenda Stack//
void reset(){
	ptrControl = pbuffer;
	aux = pbuffer;
	ptrUser = pbuffer+sizeof(variaveis);
	topo = ptrUser;
	base = ptrUser;
	ptrControl->TotalDePessoas = 0 ;
    printf("\n|---------------------------------------------------------|");
    printf("\n|======================[Reseted]==========================|");
    printf("\n|---------------------------------------------------------|");

}
bool empty(){
	if(ptrControl->TotalDePessoas == 0){
		return true;
	}else if(ptrControl->TotalDePessoas != 0){
		return false;
	}
}
void popDisplay(user *ptrAtual){
	printf("\n|Nome: %s",ptrAtual->Nome);
	printf("\n|Numero: %s",ptrAtual->Num);
}
void Display(){
    ptrUser = topo;
    user *ptrAux;
    ptrAux = ptrUser ;

    if(!empty()){
        printf("\n|=====================[Contact List]======================|");
        printf("\n|---------------------------------------------------------|");
        for(ptrControl->ContadorDePessoas = 0;
         ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas;
         ptrControl->ContadorDePessoas++,ptrAux--){
             popDisplay(ptrAux);
             printf("\n|---------------------------------------------------------|");
        }
    printf("\n|=========================================================|\n");
    }else{
        printf("\n|=======================[Pop Display]=====================|");
        printf("\n|---------------------------------------------------------|");
        printf("\n|Stack is empty");
        printf("\n|---------------------------------------------------------|");
        printf("\n|=========================================================|\n");
    }
}
void push(){

	ptrControl->TotalDePessoas++;

	pbuffer = realloc(pbuffer,(sizeof(variaveis) +	ptrControl->TotalDePessoas * sizeof(user)));

	ptrUser = pbuffer+sizeof(variaveis);
	aux = ptrUser;
	ptrControl = pbuffer;


	for(ptrControl->ContadorDePessoas = 0; ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1;
	ptrControl->ContadorDePessoas++,ptrUser++){}

	printf("|Nome:");
	scanf("%s",ptrUser->Nome);
	printf("|Numero:");
	scanf("%s",ptrUser->Num);

	base = aux;
	topo = ptrUser;

}
user* pop(){
    if(!empty()){
        ptrControl->TotalDePessoas--;
        pbuffer = realloc(pbuffer,(sizeof(variaveis) +	ptrControl->TotalDePessoas * sizeof(user)));
        ptrUser = pbuffer+sizeof(variaveis);
        aux = ptrUser;
        ptrControl = pbuffer;
        for(ptrControl->ContadorDePessoas = 0;
        ptrControl->ContadorDePessoas < ptrControl->TotalDePessoas-1;
        ptrControl->ContadorDePessoas++,ptrUser++){}
        topo = ptrUser;
    }else{
        printf("\n|=======================[Pop Display]=====================|");
        printf("\n|---------------------------------------------------------|");
        printf("\n|Stack is empty");
        printf("\n|---------------------------------------------------------|");
        printf("\n|=========================================================|\n");
    }
}

//Sorts
void bubblesort (){
	ptrUser = pbuffer + sizeof(variaveis);
	ptrControl=pbuffer;
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

	if(ptrControl->TipoStruct == 2 ){
	    ptrUser = topo;
	}
}
void SelectionSort(){

    ptrUser = pbuffer + sizeof(variaveis);
    ptrControl = pbuffer;

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
	if(ptrControl->TipoStruct == 2 ){
	    //ptrUser = topo;
	}
}

void InsertionSort(){
	ptrUser = pbuffer + sizeof(variaveis);
	ptrControl = pbuffer;
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
	if(ptrControl->TipoStruct == 2  ){
	    ptrUser = topo;
	}
}
void QuickSort (user *ptrUser ,int low , int high){
	if(low < high){
		ptrControl->pivot_id = particionar(ptrUser,low,high);
		QuickSort(ptrUser , low , ptrControl->pivot_id - 1);
		QuickSort(ptrUser , ptrControl->pivot_id + 1 , high);
	}
}
void QuickSortMain(){
	ptrUser = pbuffer + sizeof(variaveis);
	ptrControl = pbuffer;
	QuickSort(ptrUser,0,ptrControl->TotalDePessoas-1);
}
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
void mergeMain(){
    ptrControl = pbuffer;
    ptrUser = pbuffer + sizeof(variaveis);
    MergeSort(ptrUser , 0 , ptrControl->TotalDePessoas -1 );
}

//Menus
void menuStack(){
    printf("\n|====================[Schedule Stack]====================|\n");
	printf("| 1-Push\n");
    printf("| 2-Pop\n");
    printf("| 3-Display\n");
    printf("| 4-Reset\n");
    printf("| 5-BubbleSort\n");
    printf("| 6-SelectionSort\n");
    printf("| 7-InsertionSort\n");
    printf("| 8-QuickSort\n");
    printf("| 9-MergeSort\n");
    printf("| 10-Exit\n");
    printf("|=========================================================|\n");
    printf("|Select a number: ");
}
void menuArray(){
    printf("\n|====================[Schedule Array]=====================|\n");
    printf("| 1-New Contact\n");
    printf("| 2-Display Contacts\n");
    printf("| 3-Search\n");
    printf("| 4-Exclude\n");
    printf("| 5-BubbleSort\n");
    printf("| 6-SelectionSort\n");
    printf("| 7-InsertionSort\n");
    printf("| 8-QuickSort\n");
    printf("| 9-MergeSort\n");
    printf("| 10-Exit\n");
    printf("|=========================================================|\n");
    printf("|Select a number: ");
}
void menuInicial(){
	printf("\n|=====================[Which Structure?]==================|\n");
    printf("| 1-Array structure\n");
    printf("| 2-Stack Structure\n");
    printf("| 3-Exit\n");
    printf("|=========================================================|\n");
    printf("|Select a structure to start your schedule: ");
    scanf("%d",&ptrControl->OpcaoDoMenu);
    ptrControl->TipoStruct = ptrControl->OpcaoDoMenu;
}

int main(){

    pbuffer = malloc(sizeof(variaveis)+sizeof(user));
    reset();
    menuInicial();

    if(ptrControl->TipoStruct == 1 ){
        for(;;){
            menuArray();
            scanf("%d",&ptrControl->OpcaoDoMenu2);
            switch(ptrControl->OpcaoDoMenu2){

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
                    bubblesort();
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
                        SelectionSort();
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
                    InsertionSort();
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
                    QuickSortMain();
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
                        mergeMain();
                        ptrControl->ordenado = TestaOrdenacao();
                    }
                    cls();
                    imprimirTodos();
                }else{
                    cls();
                    imprimirTodos();
                    printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
                }
                free(userPivot);
                break;

            case 10:
                cls();
                printf("|====================== Ate logo! :D =====================|\n");
                free(pbuffer);
                return 1;
                break;


            default:
                printf("\nOpcao incorreta!");
            }
        }

    }
    else
    if(ptrControl->TipoStruct == 2){
        for(;;){
            menuStack();
            scanf("%d",&ptrControl->OpcaoDoMenu2);
            switch(ptrControl->OpcaoDoMenu2){

            case 1:
                cls();
                push();
                Display();
            break;

            case 2:
                cls();
                pop();
                Display();
            break;

            case 3:
                cls();
                Display();
            break;

            case 4:
                cls();
                reset();
                Display();
            break;

            case 5:
                cls();
                if(ptrControl->ContadorDePessoas > 0 ){
                    bubblesort();
                    cls();
                    Display();
                }else{
                    cls();
                    Display();
                    printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
                }
                break;

            case 6:
                cls();
                if(ptrControl->ContadorDePessoas > 0 ){
                    ptrControl->ordenado = false;
                    while(!ptrControl->ordenado){
                        SelectionSort();
                        ptrControl->ordenado = TestaOrdenacao();
                    }
                    cls();
                    Display();
                }else{
                        cls();
                        Display();
                        printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
                }
                break;

            case 7:
                cls();
                if(ptrControl->ContadorDePessoas > 0) {
                    InsertionSort();
                    cls();
                }else{
                    cls();
                    imprimirTodos();
                    printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");

                }
                Display();
                break;

            case 8:
                cls();
                if(ptrControl->ContadorDePessoas > 0) {
                    QuickSortMain();
                    cls();
                }else{
                    cls();
                    printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
                }
                if(ptrControl->TipoStruct == 2 ){
                    ptrUser = topo;
                }
                Display();
                break;

            case 9:
                cls();
                if(ptrControl->ContadorDePessoas > 0) {
                    ptrControl->ordenado = false;
                    while(!ptrControl->ordenado){
                        mergeMain();
                        ptrControl->ordenado = TestaOrdenacao();
                    }
                }else{
                    cls();
                    printf("| Nao foi possivel ordenar: quantidade de usuarios insuficiente ");
                }
                if(ptrControl->TipoStruct == 2 ){
                    ptrUser = topo;
                }
                free(userPivot);
                cls();
                Display();
                break;

            case 10:
                cls();
                printf("|====================== Ate logo! :D =====================|\n");
                free(pbuffer);
                return 1;
                break;


            default:
                printf("\nOpcao incorreta!");
            }

        }
    }
    else
    if(ptrControl->TipoStruct == 3){
        cls();
        printf("|====================== Ate logo! :D =====================|\n");
        free(pbuffer);
        free(userPivot);
        return 0;
    }

    return 1;
}
