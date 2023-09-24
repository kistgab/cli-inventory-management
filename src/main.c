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
#define INVENTORY_REPORT_BY_PRICE_OPTION_CODE 9
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


/// A professoravdeclara as funções em cima e escreve elas embaixo, acho melhor usar esse padrão pela organização tmb
/// EU vou declarar as minhas aqui, quem quiser deixa tmb e qualquer coisa a gente muda no final
/// Ass. Guilherme Majestoso
void sortItemsByPrice(int start, int end, Product array[]);
void separateArray(int start, int end, Product array[]);
int generateNewProductId();

void printOptionsMenu()
{
  printf("**************** MENU - BOTECO *****************\n");
  printf("* %i Inserir produto                             *\n", ADD_PRODUCT_OPTION_CODE);
  printf("* %i Remover produto                             *\n", DELETE_PRODUCT_OPTION_CODE);
  printf("* %i Consultar produto                           *\n", GET_PRODUCT_OPTION_CODE);
  printf("* %i Alterar produto                             *\n", MODIFY_PRODUCT_OPTION_CODE);
  printf("* %i Realizar venda                              *\n", SELL_OPTION_CODE);
  printf("* %i Gerar relatório - Estoque atual             *\n", INVENTORY_REPORT_OPTION_CODE);
  printf("* %i Gerar relatório - Ultimas 50 vendas         *\n", LAST_SALES_REPORT_OPTION_CODE);
  printf("* %i Gerar Relatório - Itens com pouco estoque   *\n", LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE);
  printf("* %i Gerar Relatório - Itens ordenados por preço *\n", INVENTORY_REPORT_BY_PRICE_OPTION_CODE);
  printf("* %i Finalizar aplicação                         *\n", EXIT_OPTION_CODE);
  printf("**************************************************\n");
  printf("Qual opção você deseja realizar?\n");
}

void readString(char *destination, int maxLength)
{
  if (fgets(destination, maxLength, stdin))
  {
    destination[strcspn(destination, "\n")] = '\0';
  }
}

int generateNewProductId(){
    static int newId = -1;
    newId++;
    return newId;
}

Product readProductData()
{
  Product newProduct;
  getchar();
  newProduct.id = generateNewProductId();
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

bool insertProduct(Product inventory[], int *firstListPosition, int *lastListPosition)
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
      inventory[i - 1] = inventory[i];
    }
    (*firstListPosition)--;
  }
  inventory[*lastListPosition] = newProduct;
  return true;
}

void printProduct(Product product)
{

  printf("---------- Item ---------\n");
  printf("Id: %i \n", product.id);
  printf("Nome: %s \n", product.name);
  printf("Descrição: %s \n", product.description);
  printf("Quantidade em estq.: %i \n", product.quantity);
  printf("Preço de venda: %.2f \n", product.sellPrice);
  printf("---------- ** ---------\n");
}

void printProductsList(Product inventory[], int lastListPosition)
{
  if (lastListPosition == -1)
  {
    printf("Não existem produtos no cadastrados no estoque! \n");
    return;
  }
  printf("\n****** RELATÓRIO DO ESTOQUE COMPLETO ****** \n");
  for (int i = 0; i <= lastListPosition; i++)
  {
    printProduct(inventory[i]);
  }
  printf("************** FIM RELATORIO ************** \n\n\n");
}

void printProductsListWithLowQuantity(Product inventory[], int lastListPosition)
{
  if (lastListPosition == -1)
  {
    printf("Não existem produtos no cadastrados no estoque! \n");
    return;
  }
  int maximumQuantity;
  bool foundAnyProductWithLowQuantity = false;
  printf("Listar itens que tenham esta ou menor quantidade:");
  scanf("%i", &maximumQuantity);
  printf("\n****** RELATÓRIO DO ESTOQUE COMPLETO ****** \n");
  for (int i = 0; i <= lastListPosition; i++)
  {
    if (inventory[i].quantity <= maximumQuantity)
    {
      printProduct(inventory[i]);
      foundAnyProductWithLowQuantity = true;
    }
  }
  if (!foundAnyProductWithLowQuantity)
  {
    printf("Nenhum produto satisfaz essa quantidade máxima! \n");
  }
  printf("************** FIM RELATORIO ************** \n\n\n");
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
      printProductsList(productsInventory, lastListPosition);
      break;
    case LAST_SALES_REPORT_OPTION_CODE:
      // Call methods here
      break;
    case INVENTORY_REPORT_BY_PRICE_OPTION_CODE:
        sortItemsByPrice(firstListPosition, lastListPosition, productsInventory);
        break;
    case LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE:
      printProductsListWithLowQuantity(productsInventory, lastListPosition);
      break;
    }
  }
}

void sortItemsByPrice(int start, int end, Product array[]){
    if((start==-1 && end==-1) || end==start)
        return;
    ///
    /// Eu faço isso pq como eu quero ordenar um vetor por preço só pra
    /// printar ele, mas não alterar a ordem do vetor original, eu tenho que
    /// passar os valores pra outro vetor e ordenar esse.
    ///
    Product duplicateArray[MAX_QUANTITY_OF_PRODUCTS_TO_STORE];
    for(int i = start; i<=end; i++){
        duplicateArray[i] = array[i];
    }
    separateArray(start, end, duplicateArray);
    printProductsList(duplicateArray, end);
}

void separateArray(int start, int end, Product array[]){
    Product aux;
    int pivot = end;
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j].sellPrice <= array[pivot].sellPrice) {
            i++;
            aux = array[j];
            array[j] = array[i];
            array[i] = aux;
        }
    }

    aux = array[pivot];
    array[pivot] = array[i+1];
    array[i+1] = aux;
    pivot = i+1;
    if(pivot+1<end)
        separateArray(pivot+1, end, array);

    if(start<pivot-1)
        separateArray(pivot-1, i, array);

}

