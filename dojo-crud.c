#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

FILE* fileOpen(char nome[]){
    FILE* f = fopen(nome, "rb+");
    if(!f)
        f = fopen(nome, "wb+");
    return f;
}

typedef struct{
    int id;
    char tipo;
    int dia;
    float valor;
    char descricao[100];
    int status;
    
}Lancamento;

enum {RECEITA, DESPESA};

int menu(){
    int opt;
    printf(">>>>MENU>>>>\n");
    printf("(1) - Cadastrar Receita\n");
    printf("(2) - Cadastrar Despesa\n");
    printf("(3) - Pagar Despesa\n");
    printf("(4) - Extrato Mensal\n");
    printf("(0) - SAIR");
    printf("Escolha:\n");
    scanf(" %d", &opt);
    return opt;
}

int size(FILE *f){
    fseek(f, 0, SEEK_END);
    return ftell(f) / sizeof(Lancamento);
}

void cadastrarLancamento(FILE* f, int tipo){
    Lancamento lan;
    int tamanho = size(f);
    lan.id = tamanho + 1;
    if(tipo == RECEITA){
        lan.tipo = 'R';
        lan.status = 1;
        }
        else{
            lan.tipo = 'D';
            lan.status = 0;
            }
    printf("Cadastrar %s \n", tipo == RECEITA ? "Receita" : "Despesa");    
    printf("Descreva o lançamento: ");
    scanf(" %s[^\n]", lan.descricao);
    printf("Qual o valor? ");
    scanf(" %f", &lan.valor);
    printf("Qual o dia? ");
    scanf(" %d", &lan.dia);
    
    fseek(f,0,SEEK_END);
    fwrite(&lan, sizeof(Lancamento), 1, f);
    fflush(f);
    
    printf("Lançamento cadastrado com sucesso! ID: %d", tamanho+1);
    while(getchar() != '\n');
    getchar();
    
}
float calcularSaldo(FILE* f){
    float saldo;
    Lancamento lan;
    fseek(f, 0, SEEK_SET);
    int tamanho = size(f);
    for(int i = 0; i < tamanho; i++){
        fread(&lan, sizeof(Lancamento), 1, f);
        if(lan.tipo == 'R')
            saldo += lan.valor;
        if(lan.tipo == 'D' && lan.status == 1)
            saldo -= lan.valor;
        }
    return saldo;    
}


void pagarDespesa(FILE* f){
    Lancamento lan;
    int tamanho = size(f);
    printf("ESCOLHA SUA DESPESA\n");
    printf("ID\t DIA\t TIPO\t DESCRIÇÃO\t VALOR\t STATUS\t");
    for (int i = 0; i < tamanho; i++){
        fread(&lan, sizeof(Lancamento), 1, f);
            if(lan.tipo == 'D' && lan.status == 0)
            printf("%d\t %d\t %c\t %s\t %.2f\t %d\t", lan.id, lan.dia, lan.tipo, lan.descricao, lan.valor, lan.status);
        }
    printf("Escolha pelo o ID");
    int opt;
    scanf(" %d", &opt);
    
    if(opt <= 0) return;
    
    for (int i = 0; i < tamanho; i++){
        fread(&lan, sizeof(Lancamento), 1, f);
            if(lan.id == opt && lan.tipo == 'D'){
                if(lan.valor < calcularSaldo(f)){
                    lan.status = 1;
                    fseek(f, i * sizeof(Lancamento), SEEK_SET);
                    fwrite(&lan, sizeof(Lancamento), 1, f);
                    printf("Despesa paga!");
                    }
                    else
                        printf("Saldo insuficiente");
                } return;
        }
    printf("ID não encontrado");
}

void imprimirExtrato(FILE* f){

    int tamanho = size(f);
    Lancamento lista[tamanho];
    fseek(f,0,SEEK_SET);
    fread(&lista, sizeof(Lancamento), tamanho, f);
    printf("===========EXTRATO MENSAL===========");
    printf("ID\t DIA\t TIPO\t DESCRIÇÃO\t VALOR\t STATUS\t\n");
    
    for(int i = 0; i < tamanho - 1; i++){
        for(int j = 0; j < tamanho - i - 1; j++){
            if(lista[j].dia < lista[j+1].dia){
                Lancamento temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
                }
            }
        }
        for(int i = 0; i < tamanho; i++){
        if(lista[i].tipo == 'R')
            printf("%d\t %d\t %c\t %s\t %.2f\t %d\t\n", lista[i].id,lista[i].dia,lista[i].tipo,lista[i].descricao,lista[i].valor,lista[i].status);
        }
        for(int i = 0; i < tamanho; i++){
        if(lista[i].tipo == 'D')
            printf("%d\t %d\t %c\t %s\t %.2f\t %d\t\n", lista[i].id,lista[i].dia,lista[i].tipo,lista[i].descricao,lista[i].valor,lista[i].status);
        }
        
        printf("\n===============Saldo Total: R$ %.2f", calcularSaldo(f));
}

int main(){
    int opcao;
    FILE* storage = fileOpen("projeto.bin");
    while((opcao = menu()) != 0){
        switch(opcao){
            case 1: cadastrarLancamento(storage, RECEITA);
            break;
            case 2: cadastrarLancamento(storage, DESPESA);
            break;
            case 3: pagarDespesa(storage);
            break;
            case 4: imprimirExtrato(storage);
            break;
            default: printf("Inválido\n");
        }
    }
    fclose(storage);
    return 0;
}

Fiz aqui, tá funcionando?
