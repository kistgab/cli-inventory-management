#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define BUF_LEN 30

#define MAX_QUANTITY_OF_PRODUCTS_TO_STORE 1
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
    int aux;
    char name[128];
    char description[128];
    int quantity;
    float sellPrice;
} Product;

typedef struct saleProduct
{
    int id;
    char name[128];
    int quantitySold;
} SaleProduct;

typedef struct sale
{
    int id;
    SaleProduct soldItems[64];
    int numberOfSales;
    float totalValue;
    char date[30];
} Sale;

void printOptionsMenu()
{
    printf("\n**************** MENU - BOTECO ********************\n");
    printf("* %i Inserir produto                               *\n", ADD_PRODUCT_OPTION_CODE);
    printf("* %i Remover produto                               *\n", DELETE_PRODUCT_OPTION_CODE);
    printf("* %i Consultar produto                             *\n", GET_PRODUCT_OPTION_CODE);
    printf("* %i Alterar produto                               *\n", MODIFY_PRODUCT_OPTION_CODE);
    printf("* %i Realizar venda                                *\n", SELL_OPTION_CODE);
    printf("* %i Gerar relatório - Estoque atual              *\n", INVENTORY_REPORT_OPTION_CODE);
    printf("* %i Gerar relatório - Ultimas 50 vendas          *\n", LAST_SALES_REPORT_OPTION_CODE);
    printf("* %i Gerar Relatório - Itens com pouco estoque    *\n", LOW_QUANTITY_IN_INVENTORY_REPORT_OPTION_CODE);
    printf("* %i Gerar Relatório - Itens ordenados por preço *\n", INVENTORY_REPORT_BY_PRICE_OPTION_CODE);
    printf("* %i Finalizar aplicação                       *\n", EXIT_OPTION_CODE);
    printf("***************************************************\n");
    printf("Qual opção você deseja realizar?\n");
}

void readString(char *destination, int maxLength)
{
    if (fgets(destination, maxLength, stdin))
    {
        destination[strcspn(destination, "\n")] = '\0';
    }
}

int getId(char text[])
{
    int id;
    printf("%s", text);
    scanf("%d", &id);
    return id;
}

int generateNewProductId()
{
    static int newId = 0;
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
    if (FIRST_POSSIBLE_PRODUCT_LIST_POSITION == MAX_QUANTITY_OF_PRODUCTS_TO_STORE)
    {
        return true;
    }
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

void printErrorMessage(char reason[])
{
    printf("****************ERROR**************\n");
    printf("Ocorreu um erro durante a operação\n");
    printf("Razão: %s\n", reason);
    printf("***********************************\n");
}

void insertProduct(Product inventory[], int *firstListPosition, int *lastListPosition)
{
    Product newProduct;
    if (isListFull(*firstListPosition, *lastListPosition))
    {
        printErrorMessage("Lista está cheia!");
        return;
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
    newProduct = readProductData();
    inventory[*lastListPosition] = newProduct;
    printf("Produto inserido com sucesso! ");
}

int generateNewSaleId()
{
    static int newId = 0;
    newId++;
    return newId;
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
        printErrorMessage("Não existem produtos no cadastrados no estoque! \n");
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
        printErrorMessage("Não existem produtos no cadastrados no estoque!");
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
        printErrorMessage("Nenhum produto satisfaz essa quantidade máxima!");
    }
    printf("************** FIM RELATORIO ************** \n\n\n");
}

int idDelete()
{
    int idToDelete;
    printf("\n----------- REMOVER UM PRODUTO -----------: \n");
    printf("Informe o id do item a ser removido: ");
    scanf("%d", &idToDelete);

    return idToDelete;
}

void bubbleSort(Product linearList[], int left, int right)
{
    int i, j;
    for (i = left; i < right; i++)
    {
        for (j = left; j < right; j++)
        {
            if (linearList[j].id > linearList[j + 1].id)
            {
                Product aux = linearList[j];
                linearList[j] = linearList[j + 1];
                linearList[j + 1] = aux;
            }
        }
    }
}

void deleteProduct(Product linearList[], int *firstListPosition, int *lastListPosition)
{
    int positionToDelete = -1, i, j, resultadoIdDelete;

    resultadoIdDelete = idDelete();

    for (i = *firstListPosition; i <= *lastListPosition; i++)
    {
        if (linearList[i].id == resultadoIdDelete)
        {
            if(linearList[i].quantity > 0){
                printErrorMessage("Não pode ser excluido um item que tem estoque.");
                break;
            }
            positionToDelete = i;
            break;
        }
    }

    if (positionToDelete != -1)
    {
        for (j = positionToDelete; j < *lastListPosition; j++)
        {
            linearList[j] = linearList[j + 1];
        }
        (*lastListPosition)--;
        printErrorMessage("Produto removido com sucesso");
    }
    else
    {
        printErrorMessage("Produto não encontrado");
    }
}

void printLast50Sales(Sale sales[], int end)
{
    if (end == -1)
    {
        printErrorMessage("Nenhuma venda foi cadastrada!");
        return;
    }

    printf("RELATORIO DAS VENDAS: \n");
    for (int i = 0; i <= end; i++)
    {
        for (int j = 0; j < sales[i].numberOfSales; j++)
        {
            printf("Produto: %s \n", sales[i].soldItems[j].name);
            printf("Quantidade: %d\n", sales[i].soldItems[j].quantitySold);
        }
        printf("DATA = %s \n", sales[i].date);
        printf("VALOR TOTAL DA VENDA = R$%.2f \n\n", sales[i].totalValue);
    }
}

void addNewSale(Sale sales[], Sale newSale, int *end)
{
    if (*end == NUMBER_OF_LAST_SALES_TO_STORE - 1)
    {
        for (int i = 0; i < *end; i++)
            sales[i - 1] = sales[i];
    }
    else
    {
        (*end)++;
    }
    sales[*end] = newSale;
}

int getProductPositionById(int id, Product array[], int start, int end)
{
    for (int i = start; i <= end; i++)
        if (array[i].id == id)
            return i;
    return -1;
}

void sellProduct(int start, int end, Product products[], Sale sales[], int *lastSale)
{
    Sale newSale;
    int qty = 0;
    int counter = -1;
    char buf[BUF_LEN] = {0};
    newSale.totalValue = 0;

    if (start == -1 && end == -1)
        return;
    printProductsList(products, end);

    do
    {
        time_t now = time(NULL);
        struct tm *ptm = localtime(&now);
        strftime(buf, BUF_LEN, "%d/%m-%Hh%Mm", ptm);
        strcpy(newSale.date, buf);

        int id = getId("-------Vender Produto---------\nDigite o Id (-1 para cancelar):\n");
        if (id == -1)
        {
            newSale.id = generateNewSaleId();
            addNewSale(sales, newSale, lastSale);
            break;
        }
        int productPosition = getProductPositionById(id, products, start, end);
        if (productPosition == -1)
        {
            printf("O produto informado não existe!\n");
            return;
        }
        counter++;
        if (counter > 63)
            return;
        do
        {
            printf("Quantas unidades foram vendidas?\n");
            scanf("%d", &qty);
        } while (qty < 0);

        if (products[productPosition].quantity - qty < 0)
        {
            printf("Operação Cancelada: o estoque e a quantidade vendida não correspondem\n");
            return;
        }
        products[productPosition].quantity -= qty;

        newSale.soldItems[counter].id = id;
        newSale.soldItems[counter].quantitySold = qty;
        strcpy(newSale.soldItems[counter].name, products[productPosition].name);

        newSale.totalValue += products[productPosition].sellPrice * qty;
        newSale.numberOfSales = counter + 1;
    } while (counter < 63);
}

void separateArray(int start, int end, Product array[])
{
    Product aux;
    int pivot = end;
    int i = start - 1;

    for (int j = start; j < end; j++)
    {
        if (array[j].sellPrice <= array[pivot].sellPrice)
        {
            i++;
            aux = array[j];
            array[j] = array[i];
            array[i] = aux;
        }
    }

    aux = array[pivot];
    array[pivot] = array[i + 1];
    array[i + 1] = aux;
    pivot = i + 1;
    if (pivot + 1 < end)
    {
        separateArray(pivot + 1, end, array);
    }
    if (start < pivot - 1)
    {
        separateArray(pivot - 1, i, array);
    }
}

void sortItemsByPrice(int start, int end, Product array[])
{
    if ((start == -1 && end == -1) || end == start)
    {
        return;
    }
    ///
    /// Eu faço isso pq como eu quero ordenar um vetor por preço só pra
    /// printar ele, mas não alterar a ordem do vetor original, eu tenho que
    /// passar os valores pra outro vetor e ordenar esse.
    ///
    Product duplicateArray[MAX_QUANTITY_OF_PRODUCTS_TO_STORE];
    for (int i = start; i <= end; i++)
    {
        duplicateArray[i] = array[i];
    }
    separateArray(start, end, duplicateArray);
    printProductsList(duplicateArray, end);
}

void getItemById(Product linearList[], int *firstListPosition, int *lastListPosition)
{

    int searchId;

    printf("Qual o ID do produto? ");
    scanf("%d", &searchId);

    for (int i = *firstListPosition; i <= *lastListPosition; i++)
    {
        if (linearList[i].id == searchId)
        {
            printProduct(linearList[i]);
            return;
        }
    }

    printErrorMessage("Número de ID inexistente!");
}

int main()
{
    int firstListPosition = -1, lastListPosition = -1;
    int lastSale = -1;
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
            deleteProduct(productsInventory, &firstListPosition, &lastListPosition);
            break;
        case GET_PRODUCT_OPTION_CODE:
            getItemById(productsInventory, &firstListPosition, &lastListPosition);
            break;
        case MODIFY_PRODUCT_OPTION_CODE:
            // Call methods here
            break;
        case SELL_OPTION_CODE:
            sellProduct(firstListPosition, lastListPosition, productsInventory, doneSales, &lastSale);
            break;
        case INVENTORY_REPORT_OPTION_CODE:
            printProductsList(productsInventory, lastListPosition);
            break;
        case LAST_SALES_REPORT_OPTION_CODE:
            printLast50Sales(doneSales, lastSale);
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
