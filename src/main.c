#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_QUANTITY_OF_PRODUCTS_TO_STORE 256
#define NUMBER_OF_LAST_SALES_TO_STORE 50

#define FIRST_POSSIBLE_PRODUCT_LIST_POSITION 0
#define LAST_POSSIBLE_PRODUCT_LIST_POSITION (MAX_QUANTITY_OF_PRODUCTS_TO_STORE - 1)

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

typedef struct saleProduct
{
  int id;
  int quantitySold;
} SaleProduct;

typedef struct sale
{
  int id;
  SaleProduct soldItems[64];
  float totalValue;
} Sale;

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
  printf("Qual opção você deseja realizar?\n");
}

void readString(char *destination, int maxLength)
{
  if (fgets(destination, maxLength, stdin))
  {
    destination[strcspn(destination, "\n")] = '\0';
  }
}

Product readProductData()
{
  Product newProduct;
  getchar();

  printf("----------- INSERIR UM NOVO PRODUTO -----------: \n");
  printf("Informe o nome: \n");
  readString(newProduct.name, sizeof(newProduct.name));
  printf("Informe a descrição: \n");
  readString(newProduct.description, sizeof(newProduct.description));
  printf("Informe a quantidade inicial para adicionar ao estoque: \n");
  scanf("%i", &newProduct.quantity);
  printf("Informe a o preço de venda: \n");
  scanf("%f", &newProduct.sellPrice);
  return newProduct;
}

bool isListFull(int firstListPosition, int lastFilledListPosition)
{
  bool isFirstPositionOcupied = FIRST_POSSIBLE_PRODUCT_LIST_POSITION == firstListPosition;
  bool isLastPositionOcupied = LAST_POSSIBLE_PRODUCT_LIST_POSITION == lastFilledListPosition;
  bool isListFull = isFirstPositionOcupied && isLastPositionOcupied;
  return isListFull;
}

bool isListEmpty(int firstListPosition)
{
  return firstListPosition == -1;
}

bool hasSpaceInTheEndOfTheList(int lastListPosition)
{
  return lastListPosition < LAST_POSSIBLE_PRODUCT_LIST_POSITION;
}

bool insertProduct(Product linearList[], int *firstListPosition, int *lastListPosition)
{
  Product newProduct;
  newProduct = readProductData();
  if (isListFull(*firstListPosition, *lastListPosition))
  {
    return false;
  }
  else if (isListEmpty(*firstListPosition))
  {
    *firstListPosition = 0;
    *lastListPosition = 0;
  }
  else if (hasSpaceInTheEndOfTheList(*lastListPosition))
  {
    (*lastListPosition)++;
  }
  else
  {
    for (int i = *firstListPosition; i <= *lastListPosition; i++)
    {
      linearList[i - 1] = linearList[i];
    }
    (*firstListPosition)--;
  }
  linearList[*lastListPosition] = newProduct;
  return true;
}

int main()
{
  int firstListPosition = -1, lastListPosition = -1;
  int selectedMenuOptionCode;
  Sale doneSales[NUMBER_OF_LAST_SALES_TO_STORE];
  Product productsInventory[MAX_QUANTITY_OF_PRODUCTS_TO_STORE];

  setlocale(LC_ALL, "Portuguese");
  while (selectedMenuOptionCode != EXIT_OPTION_CODE)
  {
    printOptionsMenu();
    scanf("%i", &selectedMenuOptionCode);

    printf("Posicao final da lista atual: %i", lastListPosition);
    switch (selectedMenuOptionCode)
    {
    case ADD_PRODUCT_OPTION_CODE:
      insertProduct(productsInventory, &firstListPosition, &lastListPosition);
      break;
    case DELETE_PRODUCT_OPTION_CODE:
      // Call methods here
      break;
    case GET_PRODUCT_OPTION_CODE:
      // Call methods here
      break;
    case MODIFY_PRODUCT_OPTION_CODE:
      // Call methods here
      break;
    case SELL_OPTION_CODE:
      // Call methods here
      break;
    case INVENTORY_REPORT_OPTION_CODE:
      // Call methods here
      break;
    case LAST_SALES_REPORT_OPTION_CODE:
      // Call methods here
      break;
    case LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE:
      // Call methods here
      break;
    }
  }
}