#include <stdio.h>
#include <stdlib.h>

typedef struct CONTACT{
	char name[20];
	int age;
}contact;

void NewContact(contact *pBuffer){
	
	printf("Age:");
	scanf("%d",&pBuffer->age);

	printf("name:");
	scanf("%s",pBuffer->name);

}

void ShowContact(contact *pBuffer){
	printf("Name:%s\n",pBuffer->name);
	printf("Age:%d\n",pBuffer->age);
}

void menu(){
	int *pointerOption;
	
	printf("|=========================[Agenda]========================|\n");
    printf("| 1-Novo contato\n");
	printf("| 2-Listar contatos\n");
	printf("| 3-Ordenar contatos\n");
	printf("| 4-Excluir contato\n");
	printf("| 5-Sair\n");
	printf("Selecione uma das opcoes: ");

}


int main(int argc, char const *argv[])
{
	void *pBuffer;

	pBuffer = (contact *) malloc(sizeof(contact));
	NewContact(pBuffer);
	ShowContact(pBuffer);

	return 0;
}