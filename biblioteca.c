#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//------------------------------Estruturas------------------------------//
struct  info_livro{ 
 char  sigla;    // [L]ivre, [E]mprestado, [R]eservado 
 int  reg;   // registro do livro 
}; 

typedef struct  aluno{ 
 char   nome[80]; 
 char   RA[7]; 
 int   emprestado; // qtde de livros emprestados – Max=3 
 int   reservado;  // qtde de livros reservados – Max =1 
 struct info_livro tabela[4];  //Obs.: (p->tabela+i)->sigla 
}aluno;     				   //Obs.: (p->tabela+i)->reg
//------------------------------Functions------------------------------//
void aloca_aluno(aluno **p, int tam);
void cadastra_aluno(aluno *p);
void grava_aluno(aluno *p);
void mostra_aluno_total(aluno *p);
int verifica();
//------------------------------main------------------------------//
int main(){
	int op;
	aluno *paluno=NULL;
	
	aloca_aluno(&paluno, 1);
	do{
		system("cls");
		printf("\n\t\tBiblioteca\n\n\tMenu:\n\n\t[1] Cadastrar Aluno\n\t[2] Consultar Alunos Totalmente\n\t[3] Consultar Alunos Parcialmente\n\t[4] Sair\n\tEscolha: ");
		scanf("%i", &op);
		fflush(stdin);
		
		switch(op){
			case 1:
				cadastra_aluno(paluno);
			break; // case 1
			
			case 2:
				mostra_aluno_total(paluno);
			break; // case 2
			
			case 3:
				
			break; // case 3
		}// switch-case
	}while(op!=4);
}//main
//------------------------------Functions------------------------------
void aloca_aluno(aluno **p, int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno)))==NULL)
		exit(1);
} // aloca_aluno 

void cadastra_aluno(aluno *p){
	int i;
	
	p->emprestado = 0;
	p->reservado = 0;
	
	printf("\n\tDigite seu nome: ");
	gets(p->nome);
	fflush(stdin);
	
	printf("\n\tDigite seu RA: ");
	gets(p->RA);
	fflush(stdin);
	
	for(i=0; i<4; i++){
		(p->tabela+i)->reg = 0;
		(p->tabela+i)->sigla = 'L';
	}
	
	grava_aluno(p);
	system("pause");
}// cadastra_aluno 

void grava_aluno(aluno *p){
	FILE *falu=NULL;

	if((falu=fopen("alunos.bin","ab"))==NULL)
		printf("\nErro no Arquivo!");
	else
		fwrite(p, sizeof(aluno), 1, falu);
		
	fclose(falu);
}// grava_aluno 

void mostra_aluno_total(aluno *p){
	FILE *falu=NULL;
	int i, cont = verifica();
	
	if((falu=fopen("alunos.bin","rb"))==NULL)
		printf("\nErro no Arquivo!");
	else{
		for(i=0; i<cont; i++){
			fseek(falu, i*sizeof(aluno), 0);
			fread(p, sizeof(aluno), 1, falu);
			printf("\n\tNome: %s\n\tRA: %s\n\tQtde. de Livros Emprestados: %i\n\tQtde. de Livros Reservados: %i\n\n", p->nome, p->RA, p->emprestado, p->reservado);
		} // for
	system("pause");
	}
} // mostra_aluno_total 

int verifica(){
	FILE *falu=NULL;
	int cont;
	
	if((falu=fopen("alunos.bin","rb"))==NULL)
		return cont;
	
	else{
		fseek(falu, 0, 2);
		cont = ftell(falu)/sizeof(aluno);
		fclose(falu);
		return cont;
	}// else
} // verifica 