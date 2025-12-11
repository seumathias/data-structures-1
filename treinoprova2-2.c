#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
typedef struct{
	char nome[100];
	int id;
	}Aluno;
typedef struct{
	int id;
	int periodo;
	int idAlunos[100];
	char nome[100];
	int qtde;
	}Disciplina;

int interface(){
	int opt;
	printf("\n==Sistema Acadêmico==\n\n");
	printf("1- Cadastrar Aluno\n");
	printf("2- Cadastrar Disciplina\n");
	printf("3- Matricular Aluno\n");
	printf("4- Cancelar Matrícula\n");
	printf("5- Imprimir chamda\n");
	printf("6- Histórico do Aluno\n");
	printf("0- Sair");
	scanf(" %d", &opt);
	return opt;
	}
Aluno cadastrarAluno(int id){
	Aluno novo;
	novo.id = id;
	printf("Qual o nome do aluno? ");
	scanf(" %[^\n]s", novo.nome);
	return novo;
	}	
Disciplina cadastrarDisciplina(int id){
	Disciplina novo;
	novo.id = id;
	novo.qtde = 0;
	printf("QUal a disciplina? ");
	scanf(" %[^\n]s", novo.nome);
	printf("Qual o período? ");
	scanf(" %d", &novo.periodo);
	return novo;
	}
int buscarAluno(Aluno alunos[], char busca[], int cont){
	for(int i = 0; i < cont; i++)
		if(!strcmp(busca,alunos[i].nome))
			return i;
	return -1;		
	}	
int buscarDisciplina(Disciplina disciplinas[], char busca[], int cont){
	for(int i = 0; i < cont; i++)
		if(!strcmp(busca,disciplinas[i].nome))
			return i;
	return -1;		
	}	

int conferir( Disciplina disciplinas[], int alunoAlvo, int discAlvo){
	for(int i = 0; i < disciplinas[discAlvo].qtde; i++)
		if(disciplinas[discAlvo].idAlunos[i] == alunoAlvo)
			return 0;
	return 1;		
}

void matricularAluno(Aluno alunos[], Disciplina disciplinas[], int aluno, int disc){
	printf("Qual o nome do aluno? ");
	char busca[100];
	int alunoAlvo, discAlvo;
	do{
		scanf(" %[^\n]s", busca);
		alunoAlvo = buscarAluno(alunos, busca, aluno);
		if(alunoAlvo < 0){
			printf("Aluno não localizado\n");
			return;
		}
			else if(alunoAlvo >= 0)
				break;
		}while(1);
	printf("Qual a disciplina que deseja matricular o aluno(a)? ");
	do{
		scanf(" %[^\n]s", busca);
		discAlvo = buscarDisciplina(disciplinas, busca, disc);
		if(discAlvo < 0){
			printf("Disciplina não localizada\n");
			return;
			}
			else if(discAlvo >=0)
				break;
		}while(1);
	int conferencia = conferir(disciplinas, alunos[alunoAlvo].id, discAlvo);
	if(!conferencia)
		printf("O aluno já está matriculado nesta disciplina");
		else if(conferencia){
			disciplinas[discAlvo].idAlunos[disciplinas[discAlvo].qtde] = alunos[alunoAlvo].id;
			disciplinas[discAlvo].qtde++;
			printf("Aluno %s matriculado com sucesso em -> %s", alunos[alunoAlvo].nome, disciplinas[discAlvo].nome);
			}
	}
void deletarMatricula(int alvo, Disciplina* disciplinas){
	for(int i = 0; i < disciplinas->qtde; i++)
		if(alvo == disciplinas->idAlunos[i])
			for(int j = i; j < disciplinas->qtde-1; j++)
				disciplinas->idAlunos[j] = disciplinas->idAlunos[j+1];
	printf("Aluno desmatriculado com sucesso\n");
	disciplinas->qtde--;	
	}
	
void cancelarMatricula(Aluno alunos[], Disciplina disciplinas[], int aluno, int disc){
	printf("Qual o nome do aluno? ");
	char busca[100];
	int alunoAlvo, discAlvo;
	do{
		scanf(" %[^\n]s", busca);
		alunoAlvo = buscarAluno(alunos, busca, aluno);
		if(alunoAlvo < 0){
			printf("Aluno não localizado\n");
			return;
		}
			else if(alunoAlvo >= 0)
				break;
		}while(1);
	printf("Qual a disciplina que deseja cancelar da matrícula do aluno(a)? ");
	do{
		scanf(" %[^\n]s", busca);
		discAlvo = buscarDisciplina(disciplinas, busca, disc);
		if(discAlvo < 0){
			printf("Disciplina não localizada\n");
			return;
			}
			else if(discAlvo >=0)
				break;
		}while(1);
	int conferencia = conferir(disciplinas, alunos[alunoAlvo].id, discAlvo);
	if(!conferencia)
		printf("O aluno não está matriculado nesta disciplina");
		else if(conferencia)
			deletarMatricula(alunos[alunoAlvo].id, &disciplinas[discAlvo]);
	}
void ordenarNomes(char lista[][100], int cont){
	char temp[100];
	for(int i = 0; i < cont; i++){
		for(int j = i; j <cont-i-1; j++){
			if(strcmp(lista[j],lista[j+1])>0){
			strcpy(temp, lista[j]);
			strcpy(lista[j], lista[j+1]);
			strcpy(lista[j+1], temp);
				}
			}
		}
	}
void listaChamada(Aluno alunos[], Disciplina disciplinas[], int aluno, int disc){
	printf("De qual disciplina você deseja fazer a lista de chamada? ");
	char busca[100];
	int discAlvo;
	do{
		scanf(" %[^\n]s", busca);
		discAlvo = buscarDisciplina(disciplinas, busca, disc);
		if(discAlvo < 0){
			printf("Aluno não localizado\n");
			return;
		}
			else if(discAlvo >= 0)
				break;
		}while(1);
	char listaNomes[50][100];
	int matriculados = disciplinas[discAlvo].qtde;
	
	for(int i = 0; i < matriculados; i++){
		int id = disciplinas[discAlvo].idAlunos[i];
			for(int j = 0; j < 	aluno; j++){
				if(id == alunos[j].id)
				strcpy(listaNomes[i], alunos[j].nome);
			}
	}
	ordenarNomes(listaNomes, matriculados);
	
	for(int i = 0; i < matriculados; i++){
		printf("Lista de Chamada:\n");
		printf("%d - %s", i+1, listaNomes[i]);
		}
}
void historicoAluno(Aluno alunos[], Disciplina disciplinas[], int aluno, int disc){
	printf("Qual o nome do aluno? ");
	char busca[100];
	int alunoAlvo;
	do{
		scanf(" %[^\n]s", busca);
		alunoAlvo = buscarAluno(alunos, busca, aluno);
		if(alunoAlvo < 0){
			printf("Aluno não localizado\n");
			break;
		}
			else if(alunoAlvo >= 0)
				break;
		}while(1);
	int listaDisc[50];
	int qtde = 0;
	for(int i = 0; i < disc; i++){
		if(conferir(disciplinas, alunos[alunoAlvo].id, i)){
			listaDisc[qtde] = i;
			qtde++;
		}
	for(int i = 0; i < qtde; i++){
		for(int j = 0; j < qtde-i-1; j++){
			if(disciplinas[listaDisc[j]].periodo > disciplinas[listaDisc[j+1]].periodo){
				int temp = listaDisc[j];
				listaDisc[j] = lSistaDisc[j+1];
				listaDisc[j+1] = temp;
				}
			}
		}
	}
	printf("Histórico do aluno %s\n", alunos[alunoAlvo].nome);
	for(int i = 0; i < qtde; i++){
		int index = listaDisc[i];
		printf("Período: %d - %s\n", disciplinas[listaDisc[i]].periodo, disciplinas[index].nome);
	}
}
int main(){
	Aluno alunos[100];
	Disciplina disciplinas[100];
	int contAluno = 0, contDisc = 0;
	do{
		switch(interface()){
			case 1: alunos[contAluno] = cadastrarAluno(contAluno+1);
			contAluno++;
			break;
			case 2: disciplinas[contDisc] = cadastrarDisciplina(contDisc+1);
			contDisc++;
			break;
			case 3: matricularAluno(alunos, disciplinas, contAluno, contDisc);
			break;
			case 4: cancelarMatricula(alunos, disciplinas, contAluno, contDisc);
			break;
			case 5: listaChamada(alunos, disciplinas, contAluno, contDisc);
			break;
			case 6: historicoAluno(alunos, disciplinas, contAluno, contDisc);
			break;
			default:
			printf("Programa encerrado");
			return 0;
			}
		}while(1);
	return 0;
}

