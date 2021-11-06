#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "produtos.h"

int menu(ListaProdutos * listaProdutos);

Produto telaCadastro();

void menuEditar(ListaProdutos * listaProdutos);

void menuRemove(ListaProdutos * listaProdutos);

void menuVenda(ListaProdutos * listaProdutos);



#endif // MENU_H_INCLUDED
