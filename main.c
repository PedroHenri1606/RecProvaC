#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


int main()
{
   ListaProdutos listaProdutos;
   listaProdutos.tamanho = 0;

   carregarProdutos(&listaProdutos);

   while( menu(&listaProdutos) != -1);
    return 0;
}
