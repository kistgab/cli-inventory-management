#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define ADD_PRODUCT_OPTION_CODE 1
#define DELETE_PRODUCT_OPTION_CODE 2
#define GET_PRODUCT_OPTION_CODE 3
#define MODIFY_PRODUCT_OPTION_CODE 4
#define SELL_OPTION_CODE 5
#define INVENTORY_REPORT_OPTION_CODE 6
#define LAST_SALES_REPORT_OPTION_CODE 7
#define LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE 8
#define EXIT_OPTION_CODE 999

typedef struct product
{
  int id;
  char name[128];
  char description[128];
  int quantity;
  float sellPrice;
} Product;

typedef struct sale
{
  int id;
  SaleProduct soldItems[64];
  float totalValue;
} Sale;

typedef struct saleProduct
{
  int id;
  int quantitySold;
} SaleProduct;

void printOptionsMenu()
{
  printf("**************** MENU - BOTECO *****************\n");
  printf("* %i Inserir produto                           *\n", ADD_PRODUCT_OPTION_CODE);
  printf("* %i Remover produto                           *\n", DELETE_PRODUCT_OPTION_CODE);
  printf("* %i Consultar produto                         *\n", GET_PRODUCT_OPTION_CODE);
  printf("* %i Alterar produto                           *\n", MODIFY_PRODUCT_OPTION_CODE);
  printf("* %i Realizar venda                            *\n", SELL_OPTION_CODE);
  printf("* %i Gerar relatório - Estoque atual           *\n", INVENTORY_REPORT_OPTION_CODE);
  printf("* %i Gerar relatório - Ultimas 50 vendas       *\n", LAST_SALES_REPORT_OPTION_CODE);
  printf("* %i Gerar Relatório - Itens com pouco estoque *\n", LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE);
  printf("* %i Finalizar aplicação                       *\n", EXIT_OPTION_CODE);
  printf("************************************************\n");
}

void readString(char *destination, int maxLength)
{
  if (fgets(destination, maxLength, stdin))
  {
    destination[strcspn(destination, "\n")] = '\0';
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
}