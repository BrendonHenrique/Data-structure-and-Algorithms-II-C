#include <stdio.h>
#include <stdlib.h>

typedef struct DATA{
	int dia;
	int mes;
	int ano;
}data;

typedef struct cadastro{

	char nome[20];
	data nascimento;
	double cpf;

}user;

void preenche(user *ptr1){

	printf("nome:");
	scanf("%s",ptr1->nome);

	printf("cpf:");
	scanf("%lf",&ptr1->cpf);
	
	printf("Dia de nascimento:");
	scanf("%d",&ptr1->nascimento.dia);
	
	printf("Mes de nascimento:");
	scanf("%d",&ptr1->nascimento.mes);
	
	printf("Ano de nascimento:");
	scanf("%d",&ptr1->nascimento.ano);
}

void printa(user *ptr2){
	printf("\nnome:%s",ptr2->nome);
	printf("\ncpf:%.0lf",ptr2->cpf);
	printf("\nData de nascimento: %d/%d/%d",ptr2->nascimento.dia,ptr2->nascimento.mes,ptr2->nascimento.ano);
}

int main(int argc, char const *argv[])
{

	user *ptr;
	ptr = (user*)malloc(sizeof(user));

	preenche(ptr);
	printa(ptr);

	return 0;
}