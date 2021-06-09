#include "lista.h"

typedef struct hashFechada{
	TLista* lista;
	int tamanho;
	//int index; //0 - codigo, 1 - nome
}TFechada;

//============================================================================================== HASHCODE
int HashCodeFechada(TAluno* aluno, int tam);
//============================================================================================ INICIALIZA
void InicializarHashFechada (TFechada* fechada, int tam);
//================================================================================================== CRUD
void InserirHashFechada (TFechada* fechada, TAluno* novoAluno);
void ListarHashFechada (TFechada* fechada);
void BuscarHashFechada (TFechada* fechada, TAluno* buscarAluno);
void ExcluirHashFechada (TFechada* fechada, TAluno* excluirAluno);
//============================================================================================ ESTATITICAS
void EstatiticasHashFechada (TFechada* fechada);



