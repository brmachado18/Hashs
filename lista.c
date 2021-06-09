#include "lista.h"

//============================================================================================ INICIALIZA
void InicializarLista(TLista* lista) {
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->total = 0;	// UTILIZADO PARA SABER A QUANTIDADE DE REGISTROS QUE A LISTA POSSUI
}
 
//================================================================================================== CRUD
void InserirLista(TLista* lista, TAluno* novoAluno){	
	TNo* novo = (TNo*) malloc (sizeof(TNo));
	novo->prox = NULL;
	novo->aluno = novoAluno;
	int inserido = 0;

	if(lista->inicio == NULL){//LISTA VAZIA, ELEMENTO SERA INICIO E O FIM DA LISTA
		lista->inicio = novo;
		lista->fim = novo;
		lista->total = 1;
	}else{ //SE A LISTA POSSUIR ELEMENTOS:
		TNo* atual = NULL; 
		TNo* anterior = NULL;				
	
		atual = lista->inicio; //ATRIBUI O INICIO DA LISTA AO POTEIRO ATUAL PARA PERCORRER TODA LISTA.
		
		//PERCORRENDO A LISTA
		while(atual != NULL){
			//SE MATRICULA INSERIDA FOR MENOR OU IGUAL A ATUAL MATRICULA
			//SIGNIFICA QUE MINHA MATRICULA INSERIDA E MENOR QUE O ELEMENTO CORRENTE, LOGO INSIRO ESTE NOVO ELEMENTO ANTES DO ATUAL
			if(atual->aluno->matricula >= novo->aluno->matricula){
				//SETANDO PROXIMO NOVO PARA O ATUAL QUE E MAIOR.
				novo->prox = atual; 
				if (anterior == NULL ) lista->inicio = novo; //SE MEU ANTERIOR FOR NULLO SIGNIFICA QUE O ELEMENTO ATUAL ERA O PRIMEIRO DA LISTA, LOGO INSIRO O NOVO NO INICIO DA LISTA				
				else anterior->prox = novo; //SENAO O ANTERIOR PROXIMO RECEBE O NOVO 			
				inserido = 1; //USADO PARA INSERIR NO FINAL DA LISTA, CASO PERCORRA TODA LISTA E NAO ENTRE NO IF ESSA VARIAVEL SERA 0 
				lista->total++;
				break;
			}	
			anterior = atual; //SE A MATRICULA INSERIDA NAO FOI MENOR OU IGUAL A MATRICULA ATUAL PASSA PARA O PROXIMO ANTERIOR RECEBE O ATUAL PARA NAO PERDER REFENCIA E ATUAL RECEVE ATUAL PROXIMO 
			atual = atual->prox;
		}
		//CASO O INSERIDO SEJA 0 SEI QUE A NOVA MATRICULA É MAIOR QUE TODAS QUE POSSUO NA LISTA ATUALMENTE, LOGO INSIRO ESSA MATRICULA NO FINAL 
		if(inserido == 0){
			lista->fim->prox = novo;
			lista->fim = novo;	
			lista->total++;		
		}
	}
}

void ListarLista (TLista* lista, int indice, FILE* file){
	//LISTA VAZIA, NAO POSSUI ELEMENTOS PARA LISTAR		
	if(lista->inicio == NULL){
		printf("\n\n --== ESTRUTURA VAZIA ==-- \n\n");
	}else{	
		//SE A LISTA POSSUIR ELEMENTOS:
		//ATRIBUI O INICIO DA LISTA AO POTEIRO ATUAL PARA PERCORRER TODA LISTA.
		TNo* atual;
		atual = lista->inicio;

		if (file == NULL) 
		{
		   printf("\n\n --== ERROR AO ACESSAR ARQUIVO ==-- \n\n");
		   return;
		}
		//PERCORRENDO A LISTA E EXIBINDO VALORES	
		while(atual != NULL){	
			//printf("\n --== ALUNO ==--");
			//printf("\n MATRICULA:  %d",atual->aluno->matricula);
			//printf("\n NOME:  %s",atual->aluno->nome);
			//printf("\n NOTA:  %d",atual->aluno->nota);
			fprintf(file, "%i;", indice);
			fprintf(file, "%d;", atual->aluno->matricula);
			fprintf(file, "%s;", atual->aluno->nome);
			fprintf(file, "%d;\n", atual->aluno->nota);	

			atual = atual->prox;
		}	
	}
}

void BuscarLista(TLista* lista, int matricula){
	//LISTA VAZIA, NAO POSSUI ELEMENTOS PARA BUSCAR
	if(lista->inicio == NULL){
		printf("\n --== MATRICULA: %d NAO LOCALIZADA ==--", matricula);
	}else{	
		//SE A LISTA POSSUIR ELEMENTOS:
		//ATRIBUI O INICIO DA LISTA AO POTEIRO ATUAL PARA PERCORRER TODA LISTA.
		TNo* atual;
		atual = lista->inicio;
		//PERCORRENDO A LISTA E COMPARANDO VALORES
		while(atual != NULL){			
			if(atual->aluno->matricula == matricula){
				printf("\n\n --== ALUNO ==-- \n\n");
				printf("\n MATRICULA:  %d",atual->aluno->matricula);
				printf("\n NOME:  %s",atual->aluno->nome);
				printf("\n NOTA:  %d",atual->aluno->nota);
				printf("\n\n");
				//BREAK PARA QUEBRAR O LAÇO NAO RODAR TODA LISTA
				break;
				
			}else if(atual->aluno->matricula > matricula){
				//CASO A MATRICULA SEJA MAIOR QUE O ATUAL, PODEMOS PRESUMIR QUE NAO EXISTE ESSE REGISTRO, POIS A LISTA É ORDENADA
				printf("\n --== MATRICULA: %d NAO ENCONTRADA ==--", matricula);
				//BREAK PARA QUEBRAR O LAÇO NAO RODAR TODA LISTA
				break;
			}
			
			atual = atual->prox;							
		}
	}
	
}

void ExcluirLista(TLista* lista, int matricula){
	//LISTA VAZIA, NAO POSSUI ELEMENTOS PARA EXCLUIR
	if(lista->inicio == NULL){
		printf("\n --== MATRICULA: %d NAO LOCALIZADA PARA EXCLUSAO ==--", matricula);
	}else{	
		TNo* atual; 
		TNo* anterior;	
		//SE A LISTA POSSUIR ELEMENTOS:
		//ATRIBUI O INICIO DA LISTA AO POTEIRO ATUAL PARA PERCORRER TODA LISTA.
		atual = lista->inicio;
		anterior = NULL;
		
		//PERCORRENDO A LISTA
		while( atual != NULL){
			//SE ENCONTRAR A MATRICULA PARA EXCLUSAO
			if(atual->aluno->matricula == matricula){
				
				
				if(anterior == NULL) // SE ANTERIOR FOR NULL SIGNIFICA QUE O REGISTRO É O PRIMEIRO DA LISTA SETA O INICIO DA LISTA PARA O ATUAL PROXIMO.				
					lista->inicio = atual->prox;
				else  //SE ANTERIOR NAO FOR NULLO, SETA ANTERIOR PROXIMO PARA ATUAL PROXIMO
					anterior->prox = atual->prox;
				
				//SE ATUAL FOR O FIM DA LISTA, FIM DA LISTA RECEBE O ANTERIOR QUE PASSA SER O NOVO ULTIMO REGISTRO DA LISTA
				if(atual == lista->fim) 
					lista->fim = anterior;
				
				printf("\n\n --== ALUNO ==-- \n\n");
				printf("\n MATRICULA:  %d",atual->aluno->matricula);
				printf("\n NOME:  %s",atual->aluno->nome);
				printf("\n NOTA:  %d",atual->aluno->nota);
				printf("\n\n");
				printf("\n\n --== EXCLUIDO ==-- \n\n");
				
				//APAGA O PONTEIRO.
				free(atual);
				lista->total--;

				//BREAK PARA QUEBRAR O LAÇO NAO RODAR TODA LISTA	
				break;
			}else if(atual->aluno->matricula > matricula){
				//CASO A MATRICULA SEJA MAIOR QUE O ATUAL, PODEMOS PRESUMIR QUE NAO EXISTE ESSE REGISTRO, POIS A LISTA É ORDENADA
				printf("\n --== MATRICULA: %d NAO LOCALIZADA PARA EXCLUSAO ==-- ", matricula);
				//BREAK PARA QUEBRAR O LAÇO NAO RODAR TODA LISTA
				break;
			}
			anterior = atual;
			atual = atual->prox;
		}
	}
}

