#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct aluno {
	int matricula;
	char nome[31];
	int nota;
}TAluno;

typedef struct no {
	struct no* prox;	
	struct aluno* aluno;
}TNo;

typedef struct Lista {
	struct no* inicio;	
	struct no* fim;
	int total; 	// UTILIZADO PARA SABER A QUANTIDADE DE REGISTROS QUE A LISTA POSSUI
}TLista;

//============================================================================================ INICIALIZA
void InicializarLista(TLista* lista);
//================================================================================================== CRUD
void InserirLista(TLista* lista, TAluno* novoAluno);
void ListarLista(TLista* lista, int indice, FILE* file);
void BuscarLista(TLista* lista, int matricula);
void ExcluirLista(TLista* lista, int matricula);

