#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include <stdbool.h>


//---------------------------Struct Produto: Define os atributos de um Produto;
struct Produto{
   char nome[50];
   float preco;
   int quantidade;
   bool removido;
}typedef Produto;

//---------------------------Struct Produtos: Define limite de cadastros de produto;
struct ListaProdutos{
   Produto lista[1000];
   int tamanho;
}typedef ListaProdutos;

// FUNÇÕES DE IMPRIMIR DADOS
float printaListaCompras(ListaProdutos * listaProdutos,float total);
void printaListaProduto(ListaProdutos * listaProdutos);
void printaProduto(Produto * produto);
void printaConsultaProdutos(ListaProdutos * listaProdutos);

// FUNÇÕES DE SALVAR DADOS EM ARQUIVO
void salvarProdutos(ListaProdutos * listaProdutos);
void salvaListaCompras(ListaProdutos * ListaProdutos,char nomeArquivo[]);

// FUNÇÕES DE CARREGAR DADOS DO ARQUIVO
void carregarProdutos(ListaProdutos * listaProdutos);

#endif // PRODUTOS_H_INCLUDED
