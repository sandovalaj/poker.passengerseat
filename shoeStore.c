#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMBER_OF_STOCK 10

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
    struct shoes shoesBySize[11];   // since sizes are ranged 3 - 14
};

// record of shoes in stock
struct stockShoes stock[10];

// reset purposes
struct stockShoes reset;

// assign records function
void assignStart(struct stockShoes stock[], int n)
{
    for (int i = 0; i <= n; i++)
    {
        stock[i].recorded = false;

        for (int j = 0; j < 11; j++)
            stock[i].shoesBySize[j].size = j + 3;
    }
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
    for (int i = 0; i < 11; i++)
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

// print function that treats its second parameter either as stock index
// or style number depending on the third boolean parameter
// if true, n is stock index
// if false, n is style number/code
void printStock(struct stockShoes stock[], int n, bool isStock)
{
    int index = n;

    if (!isStock)
        for (int i = 0; i < NUMBER_OF_STOCK; i++)
            if (stock[i].styleNo == n)
            {
               index = i;
               break;
            }
    
    printf("Shoe stock number: %2d\n", index);
    printf("Shoe style number: %2d\n", stock[index].styleNo);
}

// function that changes record on stack either through stock or style
// a collective function that changes price or number of items in stock on hand
// depending on value of boolean isPrice
// changes price if true, changes number if false
void change(bool isPrice)
{
    int userChoice;
    int stockChoice;
    do
    {
        system("cls");

        printf("Choose by...\n\n");
        printf("1 - Stock Number\n");
        printf("2 - Style Number\n");
        printf("3 - go back\n\n\n");

        printf("Enter choice: ");
        scanf(" %d", &userChoice);
    } while (userChoice < 1 || userChoice > 3);


    if (userChoice == 1)
    {
        do
        {
            system("cls");

            printf("Stock is numbered 0 to %d\n\n", NUMBER_OF_STOCK - 1);
            printf("Enter a stock number: ");
            scanf(" %d", &stockChoice);
        } while (stockChoice < 0 || stockChoice > 9);
    }
}

// function that lets user enter a record on current stock
void enterRecord()
{
    int userChoice;
    int stockToInsert = checkExistingStock(stock);
    int temp;
    float ftemp;

    bool styleFinished  = false;
    bool priceFinished  = false;
    bool sizeFinished   = false;
    bool numberFinished = false;

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
            for (int i = 0; i < 11; i++)
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
                    else if (temp2 == -1)
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
        stock[stockToInsert] = reset;
}

void displayRecord()
{

}

// menu function
void inventory()
{
    int userChoice;

    while (true)
    {
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
    }
    
}

// main program
int main()
{
    assignStart(stock, NUMBER_OF_STOCK);
    inventory();
}