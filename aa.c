#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct data{
	int dia;
	int mes;
	int ano;
	int horas;
	int minutos;
}Data;

typedef struct arv{
	char nome[21];
	char nome_raiz[21];
	char tipo;
	int n_arqs;
	void* next;
	Data* data_cria;
	Data* ultima_mod;
	struct arv* prox;
	struct arv* prim;
}Tree;

Tree* pont_arv();
void arvv_insere(Tree* a, Tree* sa);
Tree* cria_arvore(Tree* t);
Tree* arv_aloca(Tree* t,char tipo, char* nome, int narqs, char* dat, char* hora, char* nomearquivo);

Tree* cria_raiz(Tree* t,char* nome_raiz){
	Tree* m = (Tree*)malloc(sizeof(Tree));
	m->prim = NULL;
	m->prox = NULL;
	strcpy(m->nome,nome_raiz);
	return m;
}

int main(){
	int op;
	Tree* c;
	c = pont_arv();
	c = cria_raiz(c,"C:");
	c = cria_arvore(c);
	while(op > 0 || op < 6){
		printf("(1) - Inserir diretorio  --  (2) - Destruir diretorio  --  (3) - Buscar diretorio  --  (4) - Renomear diretorio  --  (5) - Mover diretorio  --  (6) - Transformar arquivo\nInsira o comando da operacao desejada: ");
		scanf("%d",&op);
		if(op == 0){
			exit(1);
		}
	}
	return 0;
}

Tree* pont_arv(){
	return NULL;
}

Tree* arv_aloca(Tree* t,char tipo, char* nome, int narqs, char* dat, char* hora, char* nomearquivo){
	char ph[2],phb[4];
	int conv;
	Tree* a = (Tree*)malloc(sizeof(Tree));
	Data* d = (Data*)malloc(sizeof(Data));
	Data* dm = (Data*)malloc(sizeof(Data));
	a->data_cria = d;
	a->ultima_mod = dm;
	a->tipo = tipo;
	a->n_arqs = narqs;
	ph[0] = hora[0];
	ph[1] = hora[1];
	a->data_cria->horas = atoi(ph);
	ph[0] = hora[3];
	ph[1] = hora[4];
	a->data_cria->minutos = atoi(ph);
	ph[0] = dat[0];
	ph[1] = dat[1];
	a->data_cria->dia = atoi(ph);
	ph[0] = dat[2];
	ph[1] = dat[3];
	a->data_cria->mes = atoi(ph);
	phb[0] = dat[4];
	phb[1] = dat[5];
	phb[2] = dat[6];
	phb[3] = dat[7];
	a->data_cria->ano = atoi(ph);
	if(tipo == 'D'){
		strcpy(a->nome,nome);
		strcpy(a->nome_raiz,nomearquivo);
		arvv_insere(t,a);

	}
	else{
		strcpy(a->nome,nome);
		strcpy(a->nome_raiz,nomearquivo);
		arvv_insere(t,a);
	}
	return a;
}

void arvv_insere(Tree* a, Tree* sa){
	sa->next = a->prim;
	a->prim = sa;
}

Tree* cria_arvore(Tree* t){
	int cont = 1,thold;
	char ae, string[50];
	FILE* f = fopen("entrada.txt" , "r");
	Tree* a = (Tree*)malloc(sizeof(Tree));
	while((ae = fgetc(f))!= EOF){
		//printf("%c",ae);
		if(ae == '\n'){
			cont++;
		}
	}
	fclose(f);
	FILE* fp = fopen("entrada.txt", "r");
	for(int i=0; i<3; i++){
		int narqs,tam,cont=0,it=0;
		char tipo, nome[21], data[8], hora[5], nomearquivo[21], vnarqs[10];
		fgets(string, 50, fp);
		tam = strlen(string);
		tipo = string[0];
		for(int j=2; j<tam; j++){
			if(it == 0 && string[j] != '/'){
				nomearquivo[cont] = string[j];
			}
			if(it == 1 && string[j] != '/'){
				nome[cont] = string[j];
			}
			if(it == 2 && string[j] != '/'){
				vnarqs[cont] = string[j];
				if(string[j+1] == '/'){
					narqs = atoi(vnarqs);
				}
			}
			if(it == 3 && string[j] != '/'){
				data[cont] = string[j];
			}
			if(it == 4 && string[j] != '/'){
				hora[cont] = string[j];
			}
			cont++;
			if(string[j] == '/'){
				cont = 0;
				it++;
			}
		}
		a = arv_aloca(t, tipo, nome , narqs, data, hora, nomearquivo);
		printf("%s",string);
	}
	printf("\n");
	fclose(fp);
	return a;
}