#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
	char CPF[13];
	char nome [80];
	int numcar;
	
} cliente ;

typedef struct carro{
	int regcar;
	int qcarro;
	int modelo;
	char marca[20];
	float valor;
}carro ;

void aloca_cliente (cliente **c,int qtde);

void aloca_carro(carro **ca,int qtde);

void registra_cliente(cliente *c,carro *ca);

void carros(carro *ca,int qtde);

void encerra_revisao(cliente *c,int qtde,carro *ca);

void registra_cliente2(cliente *c, carro *ca);

int busca_carro(carro *ca, char *mod, int modelo);



int main(){
	cliente *c = NULL;
	carro *ca = NULL;
	int op;
	int pos;
	int cont=0;
	aloca_carro(&ca,3);
	carros(ca,3);

	do{
		printf("\n Cadastro cliente[1] \n Encerrar revisao[2] \n sair [3]\n");
		scanf("%s", &op);
		fflush(stdin);
	switch (op)
	{
	case '1':
		aloca_cliente(&c,cont+1);
		registra_cliente2(c+cont,ca);
		cont++;
		break;
		
	case '2':
			encerra_revisao(c, pos,ca);
			break;
		}
	}while(op!='3');
}


void aloca_cliente(cliente **c,int qtde)
{
	if ((*c=(cliente*)realloc(*c,qtde*sizeof(cliente)))==NULL){
		exit(1);
	}
	
	
}


void aloca_carro(carro **ca,int qtde)
{
	if ((*ca=(carro*)realloc(*ca,qtde*sizeof(carro)))==NULL){
		exit(1);
	}
	
	
}

void carros(carro *ca,int qtde)
{    
    int i;
	char mod1[]="JEEP";
	char mod2[]="HONDA";
	char mod3[]="FIAT";
	
for(i=0;i<qtde;i++){
   (ca+i)->regcar = i+1;
   (ca+i)->qcarro = 0;
   if(i==0){
   	strcpy((ca + i)->marca, mod1);
   	(ca+i)->modelo=1;
   	(ca+i)-> valor=20;
   }else if (i==1){
   	strcpy((ca + i)->marca, mod2);
   	(ca+i)->modelo=1;
   	(ca+i)-> valor=10;
   }else{
   	strcpy((ca + i)->marca, mod3);
   	(ca+i)->modelo=1;
   	(ca+i)-> valor=30;
       		}			
	 	}
	
	}



void encerra_revisao(cliente *c,int qtde,carro *ca){
	int i;
	char cpf[13];
	printf("qual o cpf do cliente: \n");
	scanf("%s",cpf);
	
	for(i=0; i<qtde;i++){
		if (strcmp((c+i)->CPF,cpf)==0){
			carro *carro_do_cliente = (ca+((c+i)->numcar)-1);
			carro_do_cliente->qcarro--;
			printf("nome:%s/n tipo do carro:%i/n modelo do carro:%s/n", c->nome, c->numcar, carro_do_cliente->modelo);
		}
	}
}


void registra_cliente2(cliente *c, carro *ca) {
	char mod[20], nome[80], cpf[13];
	int modelo, numcar;
	
	printf("Qual e o seu nome?\n");
	gets(nome);
	fflush(stdin);
	printf("Qual e o seu CPF?\n");
	gets(cpf);
	fflush(stdin);
	printf("Escolha uma modelo: JEEP, HONDA, FIAT\n");
	gets(mod);
	fflush(stdin);
	printf("Escolha um grau: [1]pequeno, [2]medio, [3]grande\n");
	scanf("%i", &modelo);
	fflush(stdin);
	numcar = busca_carro(ca, mod, modelo);
    if (numcar == -1) {
        printf("n atendemos este modelo \n");
    } else {
        printf("O valor dessa revisao e %.2f\n",(ca + numcar - 1)->valor);
        strcpy(c->nome, nome);
        strcpy(c->CPF, cpf);
        c->numcar = numcar;
    }
	
}

int busca_carro(carro *ca, char *mod, int modelo) {
    int i;
    for (i = 0; i < 3; i++) {
        if ((strcmp((ca + i)->marca, mod) == 0) && (ca + i)->modelo == modelo) {
            (ca + i)->qcarro++;
            return (ca + i)->regcar;
        }
    }
    return -1;
}
