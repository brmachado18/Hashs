#include "hashFechada.h"

typedef struct conteudo{
	TAluno* aluno;
	int situacao; //0 - nunca utilizado, 1 - ocupado, 2 - excluido
	int colisoes;
}TConteudo;

typedef struct hashAberto{
	TConteudo* tabela;
	int quantidade;
	int tamanho;
	float fatorCarga;
}TAberto;

//============================================================================================== HASHCODE
int HashCodeAberta(TAluno* aluno, int tamanhoHash);
//========================================================================================== EXPANDE HASH
TAberto* expandeHash();
//============================================================================================ INICIALIZA
void InicializarHashAberta(TAberto* hash, int tamanhoInicial, float fatorCarga);
void InicializarTabela(TConteudo* tabela, int tamanhoHash);
//================================================================================================== CRUD
void InserirHashAberta(TAberto* aberta, TAluno* novoAluno);
void ListarHashAberta(TAberto* aberta);
void BuscarHashAberta(TAberto* aberta, TAluno* buscarAluno);
void ExcluirHashAberta(TAberto* aberta, TAluno* excluirAluno);
//========================================================================================== ESTATISTICAS
void EstatisticasHashAberta(TAberto* aberta);
