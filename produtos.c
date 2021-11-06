#include <stdio.h>
#include "produtos.h"



//AREA DESTINA AS FUNÇÕES DE IMPRIMIR DADOS//

//---------------------------Função printaProduto: Imprime o Produto atual selecionado no menu editar
void printaProduto(Produto * produto){
    printf("-------------------------------------\n");
    printf("| Nome do Produto Atual: %s\n", produto->nome);
    printf("| Valor do Produto Atual: %.2f\n", produto->preco);
    printf("-------------------------------------\n");
}

//---------------------------Função printaListaProduto: Imprime na tela todos os itens da minha lista de Produtos
void printaListaProduto(ListaProdutos * listaProdutos){

    for(int i = 0; i < listaProdutos->tamanho; i++){
        if(! listaProdutos->lista[i].removido){
            printf("%d | %s | R$ %.2f\n", i, listaProdutos->lista[i].nome, listaProdutos->lista[i].preco);
        }
    }
}


//---------------------------Função printaListaCompras: Imprime minha lista de compras
float printaListaCompras(ListaProdutos * listaProdutos, float total){

    Produto * produto;
    total = 0;

    printf("-------------------------------------\n");
    printf("|         Lista de Compras          |\n");
    printf("-------------------------------------\n");
    printf("|ID|QTD|     DESCRICAO      | PRECO |\n");

    for(int i = 0; i < listaProdutos->tamanho; i++){
        produto = &listaProdutos->lista[i];

        if (! produto->removido){
            printf("| %d| %d | %s | %.2f \n", i,produto->quantidade, produto->nome, produto->preco * produto->quantidade);
        }
    }
    for (int j = 0; j < listaProdutos->tamanho; j++){
        produto = &listaProdutos->lista[j];
        total += produto->preco * produto->quantidade;
    }

    printf("| Total : %.2f                    \n", total);
    return total;
}

//---------------------------Função printaConsultaProdutos: Mesma coisa que ListaProduto, só que com fru fru
void printaConsultaProdutos(ListaProdutos * listaProdutos){
   float total;
   Produto * produto;
   printf("-------------------------------------\n");
   printf("         Produtos Cadastrados        \n");
   printf("                                     \n");
   printf("ID|QTD |  DESCRICAO   |  PRECO   | TOTAL \n");
    for(int i = 0; i < listaProdutos->tamanho; i++){
        if(! listaProdutos->lista[i].removido){
            printf(" %d| %d |%s  | R$ %.2f | %.2f \n", i,listaProdutos->lista[i].quantidade, listaProdutos->lista[i].nome, listaProdutos->lista[i].preco,listaProdutos->lista[i].preco * listaProdutos->lista[i].quantidade);
        }
    }
    printf("-------------------------------------\n");

        for (int j = 0; j < listaProdutos->tamanho; j++){
        produto = &listaProdutos->lista[j];
        total += produto->preco * produto->quantidade;
    }
     printf("| Total do Estoque: %.2f                    \n", total);
    system("pause");
}


//AREA DESTINA AS FUNÇÕES DE SALVAMENTO EM ARQUIVO//

//---------------------------Função salvarProdutos: Salva meus produtos cadastrados no arquivo
void salvarProdutos(ListaProdutos * listaProdutos){

    FILE * arq;
    Produto * produto;

    arq = fopen("produtos.txt", "w");

    if ( arq == NULL ) {
            printf("Erro ao abrir arquivo\n");
    }  else {
        for (int i = 0 ; i < listaProdutos->tamanho; i ++){
            produto = &listaProdutos->lista[i];
            if ( ! produto->removido ) {
                fprintf(arq, "%s; %.2f; %d \n", produto->nome, produto->preco, produto->quantidade);
            }
        }
        fclose(arq);
    }
    }

//---------------------------Função salvaListaCompras: Salva e guarda em um arquivo a lista de compras do usuario
void salvaListaCompras(ListaProdutos * listaProdutos, char nomeArquivo[]){

     FILE * arq;
    Produto * produto;

    float total = 0;
    arq = fopen(nomeArquivo, "w");
    if ( arq == NULL ) {
            printf(" ---Erro ao abrir arquivo---\n");
    }  else {
        fprintf(arq, "Qtd | Nome do Produto | Valor Total\n");
        for (int i = 0 ; i < listaProdutos->tamanho; i ++){
            produto = &listaProdutos->lista[i];
            if ( ! produto->removido ) {
                fprintf(arq, "%d | %s | R$ %.2f\n", produto->quantidade, produto->nome, produto->quantidade * produto->preco);
                total += produto->quantidade * produto->preco;
            }

        }
        fprintf(arq, "Total: R$ %.2f", total);
        fclose(arq);
    }
}


//AREA DESTINA AS FUNÇÕES DE CARREGAMENTO DE ARQUIVO//

//---------------------------Função carregarProdutos: Carrega meus itens do arquivo para o sistema
void carregarProdutos(ListaProdutos * listaProdutos){

    FILE * arq;
    Produto * produto = &listaProdutos->lista[0];

    arq = fopen("produtos.txt", "r");
    if ( arq == NULL ) {
            printf(" ---Erro ao abrir arquivo---\n");
    }  else {

        while(fscanf(arq, "%[^;]; %f\n; %d \n", produto->nome, &produto->preco, &produto->quantidade) != EOF){
            listaProdutos->tamanho++;
            produto = &listaProdutos->lista[listaProdutos->tamanho];

        }
    }
    fclose(arq);
}
