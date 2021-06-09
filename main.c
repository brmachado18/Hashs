#include "hashAberta.h"
#define TAM_ABERTA 100000
#define LOAD_FACTORY 0.9
#define TAM_FECHADA 997

void lerArquivo(TFechada* fechada, TAberto* aberta);

int main(int argc, char *argv[]) {
	int opcaoMenu = -1;
	char nome[31];
	int matricula = 0;	
	int nota = 0;
	
	// CRIANDO E INICILIALIZANDO HASH FECHADA				
	TFechada* fechada = (TFechada*) malloc (sizeof(TFechada));
	InicializarHashFechada(fechada, TAM_FECHADA);

	// CRIANDO E INICILIALIZANDO HASH ABERTA
	TAberto* aberta = (TAberto*) malloc (sizeof(TAberto));
	InicializarHashAberta(aberta, TAM_ABERTA, LOAD_FACTORY);
	
	//LENDO ARQUIVO E PREENCHENDO HASHS
	clock_t iniciot, fimt; 
	double totalt = 0;
	double segundos = 0;
	
	iniciot = clock();					
	
	lerArquivo(fechada, aberta);						
	
	fimt = clock();
	totalt = (fimt - iniciot) / CLOCKS_PER_SEC;
	segundos = totalt/60;	
	
	while(opcaoMenu != 0){
		system("cls");
		printf("\n TEMPO CRIACAO TOTAL: %f",totalt);
		printf("\n TEMPO CRIACAO MINUTOS: %f",segundos);
		printf("\n-----------HASHs---------------");	
		printf("\n 1 - ESTATISTICAS");
		printf("\n 2 - EFETUAR INSERCAO");
		printf("\n 3 - EFETUAR BUSCA");
		printf("\n 4 - EFETUAR EXCLUSAO");
		printf("\n 0 - SAIR");
		printf("\n-------------------------------");
		
		printf("\n\n Opcao desejada: ");
		scanf("%d",&opcaoMenu);
		
		switch (opcaoMenu) {
			case 0:
				system("cls");
				printf("\n-----------HASHs---------------");
				printf("\n\n --== FINALIZANDO SISTEMA ==-- \n\n");
				printf("\n\n --== GRAVANDO ARQUIVOS ==-- \n\n");
				
				ListarHashFechada(fechada);
				ListarHashAberta(aberta);
				
				printf("\n\n --== ARQUIVOS GRAVADOS ==-- \n\n");
				break;
			
			case 1:
				system("cls"); 	
				printf("\n-----------HASHs---------------");
				printf("\n\n --== ESTATISTICAS ==-- \n\n");											
				printf("\n-----------HASH FECHADA---------------");
				printf("\n\n --== DADOS ESTATISTICOS ==-- \n\n");
				
				EstatiticasHashFechada(fechada);
				
				printf("\n-----------HASH ABERTA---------------");
				printf("\n\n --== DADOS ESTATISTICOS ==-- \n\n");
				
				EstatisticasHashAberta(aberta);
	
				printf("\n\n");	
				system("pause");
				break;
				
			case 2: 
				system("cls");
				printf("\n-----------HASHs---------------");
				printf("\n\n --== INSERIR ALUNO ==-- \n\n");
						
				printf("\n Digite o nome do aluno para insercao: ");				
				scanf("%s", &nome);	
				
				printf("\n Digite a matricula do aluno para insercao: ");				
				scanf("%d",&matricula);
				
				printf("\n Digite a nota do aluno para insercao: ");				
				scanf("%d",&nota);
							
				TAluno* novoAluno = (TAluno*) malloc (sizeof(TAluno));
				strcpy(novoAluno->nome, nome);
				novoAluno->matricula = matricula;
				novoAluno->nota = nota;

				InserirHashFechada(fechada, novoAluno);
				InserirHashAberta(aberta, novoAluno);
			
				printf ("\n\n --== INSERIDO ==-- \n\n");	
				
				printf("\n\n");
				system("pause");
				break;
											
			case 3: 
				system("cls");
				printf("\n-----------HASHs---------------");
				printf("\n\n --== BUSCAR ALUNO ==-- \n\n");
			
				printf("\n\n Digite matricula do aluno para busca:\n\n");				
				scanf("%d",&matricula);
				
				TAluno* busca = (TAluno*) malloc (sizeof(TAluno));				
				busca->	matricula = matricula;
				
				printf("\n\n --== BUSCAR ALUNO FECHADA==--");
				BuscarHashFechada(fechada, busca );
				
				printf("\n\n --== BUSCAR ALUNO ABERTA==--");
				BuscarHashAberta(aberta, busca);
				
				printf("\n\n");
				system("pause");		
				break;
				
			case 4: 
				system("cls");
				printf("\n-----------HASHs---------------");
				printf("\n\n --== EXCLUSAO ALUNO ==-- \n\n");
			
				printf("\n\n !!! Digite a matricula do aluno para exclusao:\n\n");				
				scanf("%d",&matricula);
				
				TAluno* excluir = (TAluno*) malloc (sizeof(TAluno));				
				excluir->matricula = matricula;
				
				printf("\n\n --== EXCLUSAO ALUNO FECHADA ==--");
				ExcluirHashFechada(fechada, excluir);
				
				printf("\n\n --== EXCLUSAO ALUNO ABERTA ==--");
				ExcluirHashAberta(aberta, excluir);
						
				printf("\n\n");
				system("pause");
				system("cls");
				break;
		}	
	}		
	system("pause");
	return 0;
}

void lerArquivo(TFechada* fechada, TAberto* aberta){

	FILE *file;
	char linha[50];
	char *result;
	char *subString;
	
	file = fopen("forcado700000.txt", "rt");
	
	if(file == NULL){
		printf("\n\n --== ARQUIVO NAO LOCALIZADO ==--  \n\n");
		system("pause");
	}else{

		result = fgets(linha,50,file);
		while(!feof(file)){
			result = fgets(linha,50,file);			
			if(result != NULL){
				TAluno* aluno = (TAluno*) malloc (sizeof(TAluno));				 		
				
				subString = strtok(linha, ";");
				aluno->matricula = atoi(subString);
										
				subString = strtok(NULL, ";");
				strcpy(aluno->nome, subString);
				
				subString = strtok(NULL, ";");
				aluno->nota = atoi(subString);	
				//insere hashs
				InserirHashFechada(fechada, aluno);
				InserirHashAberta(aberta, aluno);
			}
				
		}	
	}
	fclose(file);
}
