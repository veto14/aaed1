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
void arvv_imprime(Tree* t);
void printa_data(Data* d);
char* qual_mes(int m);
Data* insere_data(int a,int b, int c, int d, int e);
void insere_irmao(Tree* pai, Tree* irmao,char* nome);
void insere_diretorio(Tree* t, Tree* dir, char* nome);
Tree* busca(Tree* t, char* nome);
void printa_arquivo(Tree* t);


Tree* cria_raiz(Tree* t,char* nome_raiz){
	Tree* m = (Tree*)malloc(sizeof(Tree));
	m->prim = NULL;
	m->prox = NULL;
	strcpy(m->nome,nome_raiz);
	m->tipo = 'R';
	m->n_arqs = 1024000000;
	m->data_cria = insere_data(14,4,2000,22,32);
	m->ultima_mod = insere_data(14,4,2000,22,32);
	strcpy(m->nome_raiz,nome_raiz);
	return m;
}


int main(){
	int op;
	Tree* c;
	c = pont_arv();
	c = cria_raiz(c,"c");
	c = cria_arvore(c);
	arvv_imprime(c);
	while(op > 0 || op < 6){
		printf("\n\n(1) - Inserir diretorio  --  (2) - Destruir diretorio  --  (3) - Buscar diretorio  --  (4) - Renomear diretorio  --  (5) - Mover diretorio  --  (6) - Transformar arquivo\nInsira o comando da operacao desejada: ");
		scanf("%d",&op);
		if(op == 0){
			exit(1);
		}
	}
	return 0;
}

Data* insere_data(int a, int b, int c, int d, int e){
	Data* dat = (Data*)malloc(sizeof(Data));
	dat->dia = a;
	dat->mes = b;
	dat->ano = c;
	dat->horas = d;
	dat->minutos = e;
	return dat;
}

void printa(Tree* t, char* nome){
	Tree* p;
	p = (Tree*)malloc(sizeof(Tree));
	p = busca(p,nome);
	if(p->tipo == 'D'){
		printf("Diretorio\n");
	}
	if(p->tipo == 'B'){
		printf("Arquivo Binario\n");
	}
	if(p->tipo == 'T'){
		printf("Arquivo Texto\n");
	}
	printf("%s\n",p->nome);
	if(p->tipo != 'R'){
		printf("%s\n",p->nome_raiz);
	}
	if(p->tipo == 'D'){
		printf("Quantidade de arquivos: %d\n",p->n_arqs);
	}
	else{
		printf("Tamanho do arquivo: %d\n",p->n_arqs);
	}
	printf("Data de criacao: ");
	printa_data(p->data_cria);
	printf("Ultima modificacao feita em: ");
	printa_data(p->ultima_mod);
}

void printa_data(Data* d){
	printf("%d de %s de %d, %d H e %d M\n",d->dia,qual_mes(d->mes),d->ano,d->horas,d->minutos);
}

void arvv_imprime(Tree* t){
	Tree* p;
	printf("\n\n\n\n");
	if(t->tipo == 'D'){
		printf("Diretorio\n");
	}
	if(t->tipo == 'B'){
		printf("Arquivo Binario\n");
	}
	if(t->tipo == 'T'){
		printf("Arquivo Texto\n");
	}
	printf("%s\n",t->nome);
	if(t->tipo != 'R'){
		printf("%s\n",t->nome_raiz);
	}
	if(t->tipo == 'D'){
		printf("Quantidade de arquivos: %d\n",t->n_arqs);
	}
	else{
		printf("Tamanho do arquivo: %d\n",t->n_arqs);
	}
	printf("Data de criacao: ");
	printa_data(t->data_cria);
	printf("Ultima modificacao feita em: ");
	printa_data(t->ultima_mod);
	/*for(p = t->prim; p != NULL; p = p->prox){
		if(p->tipo != 'R' && p->prim != NULL){
			arvv_imprime(p);
			if(p->prim->prox == NULL){
				return;
			}
		}
	}*/
	for(p = t->prim; p != NULL; p = p->prox){
		arvv_imprime(p);
	}
	
}

char* qual_mes(int m){
	switch(m){
		case 1:
			return "Janeiro";
		case 2:
			return "Fevereiro";
		case 3:
			return "Março";
		case 4:
			return "Abril";
		case 5:
			return "Maio";
		case 6:
			return "Junho";
		case 7:
			return "Julho";
		case 8:
			return "Agosto";
		case 9:
			return "Setembro";
		case 10:
			return "Outubro";
		case 11:
			return "Novembro";
		case 12:
			return "Dezembro";
	}
	return "O numero dado do mes de criacao do arquivo nao e valido.";
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
	a->ultima_mod->horas = atoi(ph);
	ph[0] = hora[3];
	ph[1] = hora[4];
	a->data_cria->minutos = atoi(ph);
	a->ultima_mod->minutos = atoi(ph);
	ph[0] = dat[0];
	ph[1] = dat[1];
	a->data_cria->dia = atoi(ph);
	a->ultima_mod->dia = atoi(ph);
	ph[0] = dat[2];
	ph[1] = dat[3];
	a->data_cria->mes = atoi(ph);
	a->ultima_mod->mes = atoi(ph);
	phb[0] = dat[4];
	phb[1] = dat[5];
	phb[2] = dat[6];
	phb[3] = dat[7];
	a->data_cria->ano = atoi(phb);
	a->ultima_mod->ano = atoi(phb);
	if(tipo == 'D'){
		strcpy(a->nome,nome);
		strcpy(a->nome_raiz,nomearquivo);

	}
	else{
		strcpy(a->nome,nome);
		strcpy(a->nome_raiz,nomearquivo);
	}
	if(a->tipo == 'D'){
		Tree* search;
		insere_diretorio(t,a,a->nome_raiz);
		search = busca(t,"Usuarios");
	}
	if(a->tipo == 'B' || 'T'){
		Tree* dir;
		dir = (Tree*)malloc(sizeof(Tree));
		dir = busca(t,a->nome);
		insere_irmao(dir,a,dir->nome); //(UMA DESSAS DUAS TA COM PROBLEMA RESOLVER QUANDO NAO ESTIVER PUTO)
	}
	return t;
}

Tree* busca(Tree* t, char* nome){
	Tree* p;
	if(strcmp(t->nome_raiz,nome) == 0){
		return t;
	}
	for(p = t->prim; p != NULL; p = p->prim){
		//printf("%s",p->nome);
		if(strcmp(p->nome_raiz,nome) == 0){
			return p;
		}
		Tree* j;
		for(j = p; j != NULL; j = p->prox){
			if(strcmp(j->nome_raiz,nome) == 0){
				return j;
			}
		}
	}
	printf("Não foi possivel encontrar o diretório %s na árvore.\n",nome);
	return t;
}

void insere_diretorio(Tree* t, Tree* dir, char* nome){
	Tree* p;
	if(t->prim == NULL){
		t->prim = dir;
	}
	for(p = t; p->prim !=NULL; p = p->prim){
		if(strcmp(nome,p->nome_raiz) != 0){
			Tree* j;
			for(j = p; j->prox != NULL; j = j->prox){
				if(j->prox == NULL){
					j->prox = dir;
				}
			}
		}
	}
}

void arvv_insere(Tree* a, Tree* sa){
	sa->prox = a->prim;
	a->prim = sa;
}

void insere_irmao(Tree* pai, Tree* irmao, char* nome){
	Tree* p;
	if(pai->prim == NULL){
		pai->prim = irmao;
	}
	else {
		Tree* j;
		printf(j->nome_raiz); 
		for(j = pai->prim; j != NULL; j = j->prox){
			//printf("%s",p->nome_raiz);
			if(j->prox == NULL){
				//printf("i'm sad");
				j->prox = irmao;
				return;
			}
		}
	}
}

Tree* cria_arvore(Tree* t){
	int cont = 1,thold;
	char ae, string[50];
	FILE* f = fopen("entrada.txt" , "r");
	Tree* a = (Tree*)malloc(sizeof(Tree));
	a = t;
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
		for(int b = 0; b < 21; b++){
			nome[b] = '\0';
		}
		fgets(string, 50, fp);
		tam = strlen(string);
		tipo = string[0];
		for(int j=2; j<tam; j++){
			if(string[j] == '\\'){
				char barra;
				printf("\nFoi detectada uma ocorrencia de \\ na sua entrada. Você deseja que ela seja convertida para uma barra normal? (Y = Sim, N = Nao)");
				scanf("%c",&barra);
				if(barra == 'Y'){
					string[j] == '/';
				}
			}
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
		a = arv_aloca(a, tipo, nome , narqs, data, hora, nomearquivo);
		printf("%s",string);
	}
	printf("\n");
	fclose(fp);
	return a;
}
