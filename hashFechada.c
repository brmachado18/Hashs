#include "hashFechada.h"

//============================================================================================== HASHCODE
int HashCodeFechada(TAluno* aluno, int tam){
	return aluno->matricula % tam;	
}

//============================================================================================ INICIALIZA
void InicializarHashFechada (TFechada* fechada, int tam){
	fechada->lista = (TLista*) malloc(tam * sizeof(TLista));
	fechada->tamanho = tam;
	
	int i = 0;
	for(i; i<tam; i++){
		InicializarLista( & (fechada->lista[i]) );
	}
}

//================================================================================================== CRUD
void InserirHashFechada (TFechada* fechada, TAluno* novoAluno){
	int code = HashCodeFechada(novoAluno, fechada->tamanho);	
	InserirLista( &(fechada->lista[code]), novoAluno);		
}

void ListarHashFechada (TFechada* fechada){
	int i = 0;	
	FILE* file;
	//CRIANDO OU ABRINDO ARQUIVO
	file = fopen("SaidaHashFechada.txt", "a");
	for(i; i < fechada->tamanho; i++){		
		if(fechada->lista[i].inicio != NULL){	
			ListarLista(&(fechada->lista[i]),i,file);
		}	
	}
	fclose(file);
}

void BuscarHashFechada (TFechada* fechada, TAluno* buscarAluno){		
	int code = HashCodeFechada(buscarAluno, fechada->tamanho);	
	BuscarLista( &(fechada->lista[code]), buscarAluno->matricula);
}

void ExcluirHashFechada (TFechada* fechada, TAluno* excluirAluno){
	int code = HashCodeFechada(excluirAluno, fechada->tamanho);	
	ExcluirLista( &(fechada->lista[code]), excluirAluno->matricula);		
}

//============================================================================================ ESTATITICAS
void EstatiticasHashFechada (TFechada* fechada){
	int maior = 0,menor = 0 , i = 0, indiceMenor = 0, indiceMaior = 0;
	
	//PERCORRENDO AS LISTAS DA HASH. INSERI UM CAMPO NA LISTA DE TOTAL DE ITENS QUE ELA POSSUI PARA FACILITAR O CALCULO DAS ESTATISTCAS
	for(i; i < fechada->tamanho; i++){		
		if(fechada->lista[i].inicio != NULL){
			if(menor == 0 || menor > fechada->lista[i].total){ //RECUPERO O INDICE E O TOTAL DE ITENS DA LISTA COM MENOR QUANTIDADE DE ELEMENTOS
				menor = fechada->lista[i].total;
				indiceMenor = i;
			} 
			if(maior < fechada->lista[i].total) { //RECUPERO O INDICE E O TOTAL DE ITENS DA LISTA COM MAIOR QUANTIDADE DE ELEMENTOS
				maior = fechada->lista[i].total;
				indiceMaior = i;		
			} 
		}	
	}
	
	printf("\n --== A HASH FECHADA INDICE: %d POSSUI A MAIOR QUANTIDADE DE ELEMENTOS: %d ==--",indiceMaior, maior);
	printf("\n --== A HASH FECHADA INDICE: %d POSSUI A MENOR QUANTIDADE DE ELEMENTOS: %d ==--",indiceMenor, menor);
	printf("\n --== MEDIA DE ELEMENTOS POR INDICE NA HASH FECHADA: %d ==--", (maior + menor)/2); // LISTA COM MAIOR + MENOR QUANTIDADE E ELEMENTOS DIVIDIVO POR 2 PARA GERAR A MEDIA 
	printf("\n --== PIOR CASO DE BUSCA ==--");
	// COMO TENHO O INDICE DA LISTA COM MAIOR QUANTIDADE DE ELEMENTO E GRAVO O FIM DA LISTA, BASTA ACESSAR DIRETAMENTE A LISTA POR ESSE INDICE E RECUPERRA O ALUNO PELO FIM DA LISTA
	// PIOR CASO O ULTIMO ALUNO DA MAIOR LISTA POIS TEM MAIS COMAPARAÇÕES PARA CHEGAR NELE
	printf("\n --== ALUNO ==-- \n");
	printf("\n MATRICULA:  %d",fechada->lista[indiceMaior].fim->aluno->matricula);
	printf("\n NOME:  %s",fechada->lista[indiceMaior].fim->aluno->nome);
	printf("\n NOTA:  %d",fechada->lista[indiceMaior].fim->aluno->nota);
	printf("\n\n");
}
