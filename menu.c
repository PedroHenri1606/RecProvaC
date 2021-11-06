#include <stdio.h>
#include "produtos.h"
#include "menu.h"


//---------------------------Função menu: Cordena o código
int menu(ListaProdutos * listaProdutos){
    int opcao;

    system("cls");
    printf("-------------------------------------\n");
    printf("|     [1] - Cadastrar Produto       |\n");
    printf("|     [2] - Editar Produtos         |\n");
    printf("|     [3] - Remover Produto         |\n");
    printf("|     [4] - Venda Produto           |\n");
    printf("|     [5] - Relatorio Estoque       |\n");
    printf("|     [0] - Sair                    |\n");
    printf("-------------------------------------\n");
    scanf("%d", &opcao);

    switch(opcao){
case 1:
    listaProdutos->lista[listaProdutos->tamanho] = telaCadastro();
    listaProdutos->tamanho++;
    salvarProdutos(listaProdutos);
    break;
case 2:
    menuEditar(listaProdutos);
    salvarProdutos(listaProdutos);
    break;
case 3:
    menuRemove(listaProdutos);
    salvarProdutos(listaProdutos);
    break;
case 4:
    menuVenda(listaProdutos);
    break;
case 5:
    printaConsultaProdutos(listaProdutos);
    break;
case 0:
    return -1;
    }
    return 0;
}

//---------------------------Função menuCadastro: Cadastra Produtos;
Produto telaCadastro(){

    Produto produto;
    system("cls");
    printf("-------------------------------------\n");
    printf(" Nome do Produto: ");
    fflush(stdin);
     scanf("%[^\n]", produto.nome);

    printf(" Valor do Produto: R$ ");
    fflush(stdin);
     scanf("%f", &produto.preco);

    printf(" Quantidade no estoque: ");
    fflush(stdin);
     scanf("%d", &produto.quantidade);
     printf("-------------------------------------\n");
    return produto;
}

//---------------------------Função menuEditar: Edita os atributos de um produto da lista, selecionando por ID
void menuEditar(ListaProdutos * listaProdutos){
    int id;
    system("cls");
    printaListaProduto(listaProdutos);

    printf("-------------------------------------\n");
    printf("Escolha um Produto : ");
    fflush(stdin);
    scanf("%d", &id);

    if(id >=0 && id < listaProdutos->tamanho){
        printaProduto(&listaProdutos->lista[id]);

        int acao;

        printf("-------------------------------------\n");
        printf("| [1] - Editar Nome do Produto      |\n");
        printf("| [2] - Editar Valor do Produto     |\n");
        printf("| [0] - Voltar\n");
        fflush(stdin);
        scanf("%d", &acao);

        switch(acao){
    case 1:
        printf("-------------------------------------\n");
        printf("| Novo nome: ");
        fflush(stdin);
        scanf("%[^\n]", listaProdutos->lista[id].nome);
        printf("-------------------------------------\n");
        break;

    case 2:
        printf("-------------------------------------\n");
        printf("| Novo valor: ");
        fflush(stdin);
        scanf("%[^\n]", listaProdutos->lista[id].preco);
        printf("-------------------------------------\n");
        break;
    case 0:
        return;

    default:
        printf(" ---Opcao invalida--- \n");
        break;
        }
    } else {
        printf(" ---ID invalido ou produto não encontrado---\n");
    }
}

//---------------------------Função menuRemove: Remove um produto da lista selecionando por ID
void menuRemove(ListaProdutos * listaProdutos){
    int id;  //Certo pra ID é usar long
    system("cls");
    printaListaProduto(listaProdutos);

    printf("-------------------------------------\n");
    printf("| Id do Produto : ");
    scanf ("%d", &id);
    printf("-------------------------------------\n");

    if(id >= 0 && id < listaProdutos->tamanho){
        listaProdutos->lista[id].removido = true;
        printf(" ---Produto REMOVIDO---\n");
    } else{
        printf(" ---Produto NAO ENCONTRADO--- \n");
      }
}

//---------------------------Função menuEditar: Edita os atributos de um produto da lista, selecionando por ID
void menuVenda(ListaProdutos * listaProdutos){

    ListaProdutos compras;
    int opcao;
    int id;
    int confirma;
    int formaPagamento;
    char nomeArq[45];
    int xParcela;
    float juros;
    float total;

    compras.tamanho = 0;

    do{
        system("cls");
        printf("ID|    Descricao   | Valor\n");
        printaListaProduto(listaProdutos);
        total = printaListaCompras(&compras,total);

        printf("-------------------------------------\n");
        printf("| [1]- Adicionar Produto ao carrinho|\n");
        printf("| [2]- Remover Produto do carrinho  |\n");
        printf("| [3]- Finalizar Compra             |\n");
        printf("| [4]- cancelar                     |\n");
        scanf("%d", &opcao);

        switch(opcao){
    case 1:
        printf("-------------------------------------\n");
        printf("| Id do Item: ");
        fflush(stdin);
        scanf("%d", &id);
        compras.lista[compras.tamanho] = listaProdutos->lista[id];

        printf("| Quantidade do Item: ");
        fflush(stdin);
        scanf("%d", &compras.lista[compras.tamanho].quantidade);

        do{
            printf("-------------------------------------\n");
            printf("|              Confirma             |\n");
            printf("|  [1] - Sim              [2]- Nao  |\n");
            printf("-------------------------------------\n");
            scanf("%d", &confirma);
        }while(confirma !=1 && confirma !=2);

        if( confirma == 1){
            compras.tamanho++;
        } else {
            printf(" ---Nao Adicionado---\n");
          }
        break;

    case 2:
        menuRemove(&compras);
        break;

    case 3:

        system("cls");
        printf("-------------------------------------\n");
        printf(" Nome no Comprovante: ");
        fflush(stdin);
        scanf("%[^\n]", nomeArq);
        printf("-------------------------------------\n");
        printf("   Selecione o metodo de pagamento   \n\n");
        printf(" [1]- Cartao de Credito              \n");
        printf(" [2]- Boleto Bancario                \n");
        printf(" [3]- A vista                        \n");
        printf(" [0]- voltar                         \n");
        printf("-------------------------------------\n");

        scanf("%d", &formaPagamento);

        switch(formaPagamento){
    case 1:

        printf("-------------------------------------\n");

        printf(" Quantidade de parcelas de 1 a 12: ");
        scanf("%d", &xParcela);
          if(xParcela > 12 && xParcela == 0){
            printf(" ---Quantidade invalida---");
          } else {
            } if(xParcela > 10){
                juros= ((total *100) / (100-5)) / 12;
                printf("| Valor de cada parcela : %.2f\n", juros);
                break;

            }
    case 2:
        printf("-------------------------------------\n");
        printf(" Quantidade de parcelas de 1 a 5: ");
        scanf("%d", &xParcela);
         if(xParcela > 5 && xParcela == 0){
            printf(" ---Quantidade invalida---\n");
         } else {
              juros= (total + 5) / xParcela;
              printf("| Valor de cada parcela : %.2f\n", juros);
              break;

           }
    case 3:
        printf("-------------------------------------\n");
        printf(" Quantidade de desconto de 0 a 15: ");
        scanf("%d", &xParcela);
        if(xParcela > 15){
            printf(" ---Quantidade invalida---\n");
        } else {
            juros = (total*xParcela)/100;
            juros = total - juros;
             printf("| Valor com desconto : %.2f\n", juros);
             break;

    case 0:
        break;
          }
        }
        salvaListaCompras(&compras, nomeArq);
        printf(" ---Comprovante salvo na pasta---\n");
        printf("  --Obrigado pela  preferencia--\n");
        system("pause");
                return;

    case 4:
        break;
        }
        } while(opcao !=4);
    }


