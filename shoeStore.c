#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMBER_OF_STOCK 10
#define NUMBER_OF_SIZES 12

struct shoes
{
    int size;
    int noOfPairs;
};

struct stockShoes
{
    int styleNo;
    float price;
    bool recorded;
    struct shoes shoesBySize[12];   // since sizes are ranged 3 - 14
};

// record of shoes in stock
struct stockShoes stock[10];

// ------------------------------- UTILITY FUNCTIONS -------------------------------------------//

// assign records function
void resetStock(int index)
{
    stock[index].styleNo = 0;
    stock[index].price = 0.0;
    stock[index].recorded = false;

    for (int j = 0; j < NUMBER_OF_SIZES; j++)
    {
        stock[index].shoesBySize[j].size = j + 3;
        stock[index].shoesBySize[j].noOfPairs = 0;
    }
}

// function that finds stock by style number
// returns -1 if non-existent
int findByStyle(struct stockShoes stock[], int style)
{
    for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
        if (style == stock[i].styleNo)
            return i;
    
    return -1;
}

// function that checks if there is already existing style number
// returns true if there is, false if there is not
bool checkExistingStyle(struct stockShoes stock[], int styleNumber)
{
    if (styleNumber < 0 || styleNumber > 50)
        return true;
    else
        for (int i = 0; i < NUMBER_OF_STOCK; i++)
            if (stock[i].styleNo == styleNumber)
                return true;
    
    return false;
}

// function that checks if there is already pairs in the stock's
// different shoe sizes
bool checkExistingPairs(struct stockShoes stock)
{
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
        if (stock.shoesBySize[i].noOfPairs != 0)
            return true;
    
    return false;
}

// function that checks last recorded stock and returns stock
// number after it, otherwise, returns -1 if all stocks are occupied
int checkExistingStock(struct stockShoes stock[])
{
    for (int i = 0; i < NUMBER_OF_STOCK; i++)
        if (!stock[i].recorded)
            return i;
    
    return -1;
}

// function that prints given stock parameter
void printRecord(struct stockShoes stockToPrint)
{
    printf("Price        : %.2f\n", stockToPrint.price);
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
    {
        struct shoes temp = stockToPrint.shoesBySize[i];

        if (temp.noOfPairs != 0)
            printf("Size %2d in stock: %3d\n", temp.size, temp.noOfPairs);
    }
}

// function that prints given stock parameter
void printPairs(struct shoes sizesToPrint[])
{
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
    {
        if (sizesToPrint[i].noOfPairs != 0)
            printf("Size %2d in stock: %3d\n", sizesToPrint[i].size, sizesToPrint[i].noOfPairs);
    }
}

// function that changes price or item on hand
void change(bool isPrice, int userChoice, int itemStock)
{
    float priceToChange;
    int sizeToChange;
    int newPairs;

    system("cls");

    if (isPrice)
    {
        if (userChoice == 1)
            printf("Stock %d\nPrice: %.2f\n", itemStock, stock[itemStock].price);
        else
            printf("Style %d\nPrice: %.2f\n", itemStock, stock[findByStyle(stock, itemStock)].price);
    }
    else
    {
        if (userChoice == 1)
            printPairs(stock[itemStock].shoesBySize);
        else
            printPairs(stock[findByStyle(stock, itemStock)].shoesBySize);
    }

    printf("\nEnter -1 to go back to main menu.\n");

    if (isPrice)
    {
        printf("\n\nEnter new price: ");
        scanf(" %f", &priceToChange);

        int temp2 = (int) priceToChange;

        if (temp2 == -1)
            return;
        else if (priceToChange < 0)
            change(isPrice, userChoice, itemStock);
        else
        {
            if (userChoice == 1)
                stock[itemStock].price = priceToChange;
            else
                stock[findByStyle(stock, itemStock)].price = priceToChange;
        }
    }
    else
    {

        printf("\n\nEnter size to change pairs: ");
        scanf(" %d", &sizeToChange);

        system("cls");

        if (userChoice == 1)
            printPairs(stock[itemStock].shoesBySize);
        else
            printPairs(stock[findByStyle(stock, itemStock)].shoesBySize);

        printf("\nEnter -1 to go back to main menu.\n");
        printf("Enter -2 to go back.\n");

        printf("\nSize to change: %d\n", sizeToChange);

        if (sizeToChange == -1)
            return;
        else if (sizeToChange < 3 || sizeToChange > 14)
            change(isPrice, userChoice, itemStock);
        else
        {
            printf("Enter new number of pairs: ");
            scanf(" %d", &newPairs);

            if (newPairs == -1)
                return;
            else if (newPairs < 0 || newPairs == -2)
                change(isPrice, userChoice, itemStock);
            else
            {
                if (userChoice == 1)
                    stock[itemStock].shoesBySize[sizeToChange - 3].noOfPairs = newPairs;
                else
                    stock[findByStyle(stock, itemStock)].shoesBySize[sizeToChange - 3].noOfPairs = newPairs;
                
                change(isPrice, userChoice, itemStock);
            }
        }
    }
}

// ----------------------------- END OF UTILITY FUNCTIONS --------------------------------------//


// function that lets user enter a record on current stock
void enterRecord()
{
    int userChoice, temp, stockToInsert = checkExistingStock(stock);
    float ftemp;

    bool styleFinished  = false;
    bool priceFinished  = false;
    bool sizeFinished   = false;

    while (true)
    {
        system("cls");

        printf("This is stock number %d\n\n", stockToInsert);
        printf("Enter -1 to go back to main menu.\n");
        if (styleFinished)
            printf("Enter -2 to go back.\n");

        // print if already supplied
        if (styleFinished)
            printf("\nShoe's current style: %d\n", stock[stockToInsert].styleNo);
        if (priceFinished)
            printf("Shoe's current price: %.2f\n", stock[stockToInsert].price);
        if (sizeFinished || checkExistingPairs(stock[stockToInsert]))
            for (int i = 0; i < NUMBER_OF_SIZES; i++)
                if (stock[stockToInsert].shoesBySize[i].noOfPairs != 0)
                    printf("Shoe size %2d's pairs: %d\n", i + 3, stock[stockToInsert].shoesBySize[i].noOfPairs);
        
        // supplying process
        if (!styleFinished)
        {
            printf("\n\n\n\n\n\nStyle number is within range 0 to 50 inclusive.\n");
            printf("Enter style number: ");
            scanf(" %d", &temp);

            if (!checkExistingStyle(stock, temp))
            {
                stock[stockToInsert].styleNo = temp;
                styleFinished = true;
            }
            else if (temp == -1)
                break;
        }

        else if (!priceFinished)
        {
            printf("\n\n\nPrice should be above 0.\n");
            printf("Enter price: ");
            scanf(" %f", &ftemp);

            temp = (int) ftemp;

            if (ftemp > 0)
            {
                stock[stockToInsert].price = ftemp;
                priceFinished = true;
            }
            else if (temp == -1)
                break;
            else if (temp == -2)
            {
                stock[stockToInsert].styleNo = 0;
                styleFinished = false;
            }
        }

        else if (!sizeFinished)
        {
            printf("\n\nSizes are within range of 3 to 14 inclusive.\n");
            printf("Enter size to add: ");
            scanf(" %d", &temp);

            if (temp >= 3 && temp <= 14)
            {
                int temp2;
                struct shoes *tempshoes = &stock[stockToInsert].shoesBySize[temp - 3];

                printf("Enter number of pairs in shoe size %d: ", tempshoes->size);
                scanf(" %d", &temp2);

                if (temp2 > 0)
                {
                    tempshoes->noOfPairs = temp2;

                    do
                    {
                        system("cls");

                        printf("Would you like to add more pairs in other sizes?\n");
                        printf("1 - for yes\n");
                        printf("2 - for no\n\n");

                        printf("Enter choice: ");
                        scanf(" %d", &temp2);
                    } while (temp2 < -2 || temp2 > 2 || temp2 == 0);


                    if (temp2 == 2)
                    {
                        sizeFinished = true;
                        stock[stockToInsert].recorded = true;
                        break;
                    }
                    else if (temp2 == -1)
                        break;
                    else if (temp2 == -2)
                        priceFinished = false;
                }
                else if (temp2 == -1)
                    break;
                else if (temp2 == -2)
                    priceFinished = false;
            }
            else if (temp == -1)
                break;
            else if (temp == -2)
                priceFinished = false;
        }
    }

    if (!stock[stockToInsert].recorded)
        resetStock(stockToInsert);
}

// print function that treats its second parameter either as stock index
// or style number depending on boolean parameter
void displayRecord(bool isStock, bool isAll)
{
    system("cls");
    int temp, temp2;

    if (isAll)
    {
        for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
        {
            printf("Stock Number : %2d\n", i);
            printf("Style Number : %2d\n", stock[i].styleNo);
            printRecord(stock[i]);
            printf("\n\n");
        }

        printf("Enter 1 to go back to main menu.\n");
        scanf(" %d", &temp);

        if (temp != 1)
            displayRecord(isStock, isAll);
    }
    else if (isStock)
    {
        printf("Enter -1 to go back to main menu\n");
        printf("These are current occupied stocks...\n\n");

        for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
            printf("Stock %d\n", i);
        
        printf("\n\n\n");
        printf("Enter stock to print: ");
        scanf(" %d", &temp);
        
        if (temp == -1)
            return;
        else if (temp < 0 || temp > 10 || !stock[temp].recorded)
            displayRecord(isStock, isAll);
        else
        {
            do
            {
                system("cls");
                printRecord(stock[temp]);

                printf("\n\nEnter 1 to go back to main menu.\n");
                scanf(" %d", &temp2);

            } while (temp2 != 1);
        }
    }
    else
    {
        printf("Enter -1 to go back to main menu.\n");
        printf("These are current occupied styles...\n\n");

        for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
            printf("Style %d\n", stock[i].styleNo);
        
        printf("\n\n\n");
        printf("Enter style to print: ");
        scanf(" %d", &temp);
        
        if (temp == -1)
            return;
        else if (temp < 0 || temp > 50 || !checkExistingStyle(stock, temp))
            displayRecord(isStock, isAll);
        else
        {
            do
            {
                system("cls");
                printRecord(stock[findByStyle(stock, temp)]);

                printf("\n\nEnter 1 to go back to main menu.\n");
                scanf(" %d", &temp2);

            } while (temp2 != 1);
        }
    }
}

// function that changes record on stack either through stock or style
void changeByChoice(bool isPrice, int userChoice)
{
    int temp;
    float temp2;

    system("cls");

    if (userChoice == 1)
    {
        printf("Enter -1 to go back to main menu.\n");
        printf("These are current occupied stocks...\n\n");

        for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
            printf("Stock %d\n", i);
        
        printf("\n\n\n");
        printf("Enter stock to change: ");
        scanf(" %d", &temp);

        if (temp == -1)
            return;
        else if (temp < 0 || temp > 10 || !stock[temp].recorded)
            changeByChoice(isPrice, userChoice);
        else
            change(isPrice, userChoice, temp);
    }

    else if (userChoice == 2)
    {
        printf("Enter -1 to go back to main menu.\n");
        printf("These are current occupied styles...\n\n");

        for (int i = 0; i < NUMBER_OF_STOCK && stock[i].recorded; i++)
            printf("Style %d\n", stock[i].styleNo);
        
        printf("\n\n\n");
        printf("Enter style to change: ");
        scanf(" %d", &temp);

        if (temp == -1)
            return;
        if (temp < 0 || temp > 50 || !checkExistingStyle(stock, temp))
            changeByChoice(isPrice, userChoice);
        else
            change(isPrice, userChoice, temp);
    }
}

// menu function
void inventory()
{
    int userChoice;
    int userChoice2;
    bool isPrice = false;

    while (true)
    {
        isPrice = false;

        do
        {
            system("cls");

            printf("INVENTORY\n\n");
            printf("What do you want to do today?\n");
            printf("1 - Enter a new record\n");
            printf("2 - Display record(s)\n");
            printf("3 - Change price of stock item\n");
            printf("4 - Change number of items on hand\n");
            printf("5 - To exit\n\n\n");

            printf("Enter a choice: ");
            scanf(" %d", &userChoice);
        } while (userChoice < 1 || userChoice > 5);

        if (userChoice == 5)
        {
            printf("\n\nHave a nice day!\n");
            break;
        }
        else if (userChoice == 1)
            enterRecord();
        else if (userChoice == 2)
        {
            do
            {
                system("cls");

                printf("Do you wish to display by stock number or by style number?\n");
                printf("1 - to display by stock number\n");
                printf("2 - to display by style number\n");
                printf("3 - to display all\n");
                printf("4 - to go back to main menu.\n\n");

                printf("Enter a choice: ");
                scanf(" %d", &userChoice);
            } while (userChoice < 1 || userChoice > 4);

            if (userChoice == 1)
                displayRecord(true, false);
            else if (userChoice == 2)
                displayRecord(false, false);
            else if (userChoice == 3)
                displayRecord(false, true);
        }
        else if (userChoice == 3 || userChoice == 4)
        {
            do
            {
                system("cls");

                printf("Do you wish to change by stock number or by style number?\n");
                printf("1 - to change by stock number\n");
                printf("2 - to change by style number\n");
                printf("3 - to go back to main menu.\n\n");

                printf("Enter a choice: ");
                scanf(" %d", &userChoice2);
            } while (userChoice2 < 1 || userChoice2 > 3);

            if (userChoice2 == 3)
                continue; 
            if (userChoice == 3)
                isPrice = true;
            
            changeByChoice(isPrice, userChoice2);
        }
    }
    
}

// main program
int main()
{
    for (int i = 0; i < NUMBER_OF_STOCK; i++)
        resetStock(i);

    inventory();
}