#include "hashAberta.h"

//============================================================================================= HASH CODE
int HashCodeAberta(TAluno* aluno, int tamanhoHash){	
	// hash code resto da divisao do tamanho da hash
	return aluno->matricula % tamanhoHash;			
}

//========================================================================================== EXPANDE HASH
TAberto* expandeHash(TAberto* aberta){
	
	int i, antigoTamanho, novaQuantidade = 0, novoTamanho = aberta->tamanho * 2;

	TConteudo* novaTabela = (TConteudo*) malloc (novoTamanho * sizeof(TConteudo));
	
	TConteudo* antigaTabela;
	
	InicializarTabela(novaTabela, novoTamanho);
	
	antigaTabela = aberta->tabela;
	aberta->tabela = novaTabela;
	
	antigoTamanho = aberta->tamanho;
	aberta->tamanho = novoTamanho;
	
	aberta->quantidade = 0;
	
	for (i = 0; i < antigoTamanho; i++){
		
		if ( antigaTabela[i].situacao == 1){
			
			InserirHashAberta(aberta, antigaTabela[i].aluno);
		}
	}
	
	free(antigaTabela);
}

//============================================================================================ INICIALIZA
void InicializarHashAberta (TAberto* aberta, int tamanhoInicial, float fatorCarga){
	
	aberta->tamanho = tamanhoInicial;
	aberta->quantidade = 0;
	aberta->fatorCarga = fatorCarga;
	aberta->tabela = (TConteudo*) malloc (tamanhoInicial * sizeof(TConteudo));
	
	InicializarTabela(aberta->tabela, aberta->tamanho);
}

void InicializarTabela(TConteudo* tabela, int tamanhoHash){	
	int i = 0;
	for(i; i<tamanhoHash; i++){
		tabela[i].situacao = 0;
		tabela[i].colisoes = 0;
	}	
}

//================================================================================================== CRUD
void InserirHashAberta(TAberto* aberta, TAluno* novoAluno){
	int colisoes = 0;
	//VERIFICA A PORCENTAGEM REGISTRO NA HASH E SE FOR MAIOR OU IGUAL O LOAD_FACTORY, EXPANDE A HASH
	if( (aberta->quantidade / aberta->tamanho) >= aberta->fatorCarga){
	
		expandeHash(aberta);		
	}

	int code = HashCodeAberta(novoAluno, aberta->tamanho);
	
	// VERIFICA SE A TABELA POSSUI REGISTRO NO HASHCODE, 1 == OCUPADO. SE POSSUIR ADICIONA + 1 E RECALCULA O HASHCODE
	while (aberta->tabela[code].situacao == 1){
		code = (code + 1) % aberta->tamanho;
		colisoes++;
	}
	
	// SE A SITUACAO DO CODE FOR DIFERENTE DE 1, REALIZA A INSERCAO
	aberta->tabela[code].situacao = 1;
	aberta->tabela[code].aluno = novoAluno;
	aberta->tabela[code].colisoes = colisoes; // ARMAZENA A QUANTIDADE DE COLISOES QUE TEVE PARA INSERIR O REGISTRO
	aberta->quantidade++;

}

void ListarHashAberta(TAberto* aberta){
	int i = 0;
	//SE A QUANTIDADE FOR IGUAL A ZER O SIGNIFICA QUE AINDA NAO POSSUI REGISTROS NA HASH. LOGO NAO TEM O QUE LISTAR
	if(aberta->quantidade == 0 ){
		printf("\n\n --== ESTRUTURA VAZIA ==-- \n\n");
	}
	else{
		FILE* file;
		//CRIANDO OU ABRINDO ARQUIVO
		file = fopen("SaidaHashAberta.txt", "a");
		if (file == NULL) 
		{
		   printf("\n\n --== ERROR AO ACESSAR ARQUIVO ==-- \n\n");
		   return;
		}
		//PERCORRE TODA HASH EXIBINDO VALORES 
		for (i; i < aberta->tamanho; i++){		
			if (aberta->tabela[i].situacao == 1){
				//printf("\n --== ALUNO ==--");		
				//printf("\n MATRICULA:  %d",aberta->tabela[i].aluno->matricula);
				//printf("\n NOME:  %s",aberta->tabela[i].aluno->nome);
				//printf("\n NOTA:  %d",aberta->tabela[i].aluno->nota);
				//printf("\n COLISOES:  %d",aberta->tabela[i].colisoes);	
				fprintf(file, "%i;", i);
				fprintf(file, "%d;", aberta->tabela[i].aluno->matricula);
				fprintf(file, "%s;", aberta->tabela[i].aluno->nome);
				fprintf(file, "%d;", aberta->tabela[i].aluno->nota);
				fprintf(file, " colisoes: %d;", aberta->tabela[i].colisoes); //COMENTAR A LINHA PARA NAO IMPRIMIR INFORMAÇ~EOS DE COLISOES
				fprintf(file, " hashcode: %d;\n", aberta->tabela[i].aluno->matricula % aberta->tamanho);
			}
		}
		fclose(file);
	}
}

void BuscarHashAberta(TAberto* aberta, TAluno* buscarAluno){
	//SE A QUANTIDADE FOR IGUAL A ZERO SIGNIFICA QUE AINDA NAO POSSUI REGISTROS NA HASH. LOGO NAO TEM O QUE BUSCAR
	if(aberta->quantidade == 0 ){
		printf("\n\n --== MATRICULA: %d NAO LOCALIZADA ==-- ", buscarAluno->matricula);
		printf("\n --== ESTRUTURA VAZIA ==-- \n\n");
	}
	else{
		int code = HashCodeAberta(buscarAluno, aberta->tamanho);
		int i = 0;
		for(i; i < aberta->tamanho; i++){ 	//PERCORRE TODA HASH EXIBINDO VALORES 
			
			//SE A SITUACAO FOR IGUAL A 1 SIGNIFICA QUE POSSUI REGISTRO
			if(aberta->tabela[code].situacao == 1){
	
				//COMPARA PARA VERIFICAR SE E O REGISTRO PROCURADO
				if(aberta->tabela[code].aluno->matricula == buscarAluno->matricula ){
					printf("\n\n --== ALUNO ==-- \n\n");		
					printf("\n MATRICULA:  %d",aberta->tabela[code].aluno->matricula);
					printf("\n NOME:  %s",aberta->tabela[code].aluno->nome);
					printf("\n NOTA:  %d",aberta->tabela[code].aluno->nota);
					printf("\n COLISOES:  %d",aberta->tabela[code].colisoes);
					printf("\n");				
					break;
				}else{
					//SE NAO FOR, ADIOCA 1 NO CODE E RECALCULA O HASHCODDE
					code = (code + 1) % aberta->tamanho;
				}
			//SE A SITUACAO FOR IGUAL A 0 SIGNIFICA QUE NUNCA EXISTIU O REGISTRO 
			}else if (aberta->tabela[code].situacao == 0){
				printf("\n\n --== MATRICULA: %d NAO LOCALIZADA ==-- \n\n", buscarAluno->matricula);
				break;
			//SE A SITUACAO FOR DIFERENTE DE 1 E 0 SIGNIFICA QUE E IGUAL A 2 QUE JA POSSUIU REGISTRO POREM FOI APAGADO, ENTAO PULA PARA O PROXIMO REGISTRO.
			}else{
				code = (code + 1) % aberta->tamanho;
			}
			
		}
	}
}

void ExcluirHashAberta(TAberto* aberta, TAluno* excluirAluno){
	//SE A QUANTIDADE FOR IGUAL A ZERO SIGNIFICA QUE AINDA NAO POSSUI REGISTROS NA HASH. LOGO NAO TEM O QUE EXCLUIR
	if(aberta->quantidade == 0 ){
		printf("\n\n --== MATRICULA: %d NAO LOCALIZADA ==-- ", excluirAluno->matricula);
		printf("\n --== ESTRUTURA VAZIA ==-- \n\n");
	}
	else{
		int code = HashCodeAberta(excluirAluno, aberta->tamanho);			
		int i = 0;
		for(i; i < aberta->tamanho; i++){ 	//PERCORRE TODA HASH EXIBINDO VALORES 
			
			//SE A SITUACAO FOR IGUAL A 1 SIGNIFICA QUE POSSUI REGISTRO
			if(aberta->tabela[code].situacao == 1){
	
				//COMPARA PARA VERIFICAR SE E O REGISTRO PROCURADO
				if(aberta->tabela[code].aluno->matricula == excluirAluno->matricula ){
					printf("\n\n --== ALUNO ==-- \n\n");		
					printf("\n MATRICULA:  %d",aberta->tabela[code].aluno->matricula);
					printf("\n NOME:  %s",aberta->tabela[code].aluno->nome);
					printf("\n NOTA:  %d",aberta->tabela[code].aluno->nota);
					printf("\n COLISOES:  %d",aberta->tabela[code].colisoes);
					printf("\n");
					
					//REDEFINE A SITAUCAO COMO 2, JA TEVE REGISTRO POREM FOI EXCLUIDO
					aberta->tabela[code].situacao = 2;
					free(aberta->tabela[code].aluno); // APAGA O REGISTRO
					aberta->quantidade--; //DECREMENTEA A QUANTIDADE DE REGISTROS NA HASH
					
					printf("\n\n --== EXCLUIDO ==-- \n\n");			
					break;
				}else{
					//SE NAO FOR, ADIOCA 1 NO CODE E RECALCULA O HASHCODDE
					code = (code + 1) % aberta->tamanho;
				}
			//SE A SITUACAO FOR IGUAL A 0 SIGNIFICA QUE NUNCA EXISTIU O REGISTRO 
			}else if (aberta->tabela[code].situacao == 0){
				printf("\n\n --== MATRICULA: %d NAO LOCALIZADA ==-- \n\n", excluirAluno->matricula);			
				break;
			//SE A SITUACAO FOR DIFERENTE DE 1 E 0 SIGNIFICA QUE E IGUAL A 2 QUE JA POSSUIU REGISTRO POREM FOI APAGADO, ENTAO PULA PARA O PROXIMO REGISTRO.
			}else{
				code = (code + 1) % aberta->tamanho;
			}
			
		}
	}
}

//========================================================================================== ESTATISTICAS
void EstatisticasHashAberta(TAberto* aberta){
	int piorCasoBusca = 0, i = 0;
	
	//VARIAVEI USADAS PARA CONTAGEM DA SEQUENCIA
	int sequencia = 0; // usadi para guardar a sequencia atual
	int maiorSequencia = 0; // guarda o valor da maior sequencia 
	int indiceInicial = 0; // guarda o indice inicial da maior sequencia
	int indiceInicialContagem = 0; // usado para sempre guarda o indice do inicio da sequencia
	int indiceFinal = 0; // guarda o indice final da maior sequencia
	
	//PERCORRE TODA HASH
	for (i; i < aberta->tamanho; i++){		
		if(sequencia == 0 ) indiceInicialContagem = i; 
		
		if (aberta->tabela[i].situacao == 1){						
			if (aberta->tabela[i].colisoes > piorCasoBusca){
				// GUARDEI AS COLISOES NO MOMENTO DA INSERCAO, ASSIM BASTA PECORRER A LISTA TODO E RECUPERA O INDICE QUE POSSUI A MAIOR QUANTIDADE DE COLISOES
				// PARA OBTER O PIOR CASO DE BUSCA
				piorCasoBusca = i;
			}	
			sequencia++;
		}else{
			//SE CAIR NESSE IF SIGNIFICA QUE A POSICAO NAO E OCUPADA, QUEBRANDO ASSIM A SEQUENCIA
			//SE A SEQUENCIA ATUAL FOR MAIOR QUE A MAIOR SEQUENCIA ATE O MOMENTO EU SUBSTITUO O VALOR E GUARDO A NOVA MAIOR SEQUENCIA POSICOES OCUPADAS
			if(sequencia > maiorSequencia){	
				maiorSequencia = sequencia;
				indiceInicial = indiceInicialContagem;
				indiceFinal = i;
			}
			//ZERANDO A SEQUENCIA 
			sequencia = 0;
		}

	}
	
	printf("\n --== QUANTIDADE DE INDICE ATUAL NA HASH ABERTA: %d ==--", aberta->quantidade);
	printf("\n --== TAMANHO ATUAL NA HASH ABERTA: %d ==--", aberta->tamanho);
	printf("\n --== MAIOR SEQUENCIA DE POSICOES OCUPADAS: %d ==--\n INDICE INICIAL: %d \n INDICE FINAL: %d ", maiorSequencia, indiceInicial, indiceFinal);

	printf("\n --== PIOR CASO DE BUSCA ==--");
	printf("\n --== ALUNO ==-- \n");
	printf("\n MATRICULA:  %d", aberta->tabela[piorCasoBusca].aluno->matricula);
	printf("\n NOME:  %s", aberta->tabela[piorCasoBusca].aluno->nome);
	printf("\n NOTA:  %d", aberta->tabela[piorCasoBusca].aluno->nota);
	printf("\n COLISOES:  %d", aberta->tabela[piorCasoBusca].colisoes);
	printf("\n\n");
}





