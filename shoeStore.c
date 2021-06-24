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
    struct shoes shoesBySize[11];   // since sizes are ranged 3 - 14
    float price;
};

// record of shoes in stock
struct stockShoes stock[10];

// assign records function
void assignStart(struct stockShoes stock[], int n)
{
    for (int i = 0; i <= n; i++)
    {
        do
            stock[i].styleNo = rand() % 51;
        while (checkExistingStyle(stock, stock[i].styleNo));

        for (int j = 0; j < 11; j++)
            stock[i].shoesBySize[j].size = j + 3;
    }
}

// function that checks if there is already existing style number
// returns true if there is, false if there is not
bool checkExistingStyle(struct stockShoes stock[], int styleNumber)
{
    for (int i = 0; i < NUMBER_OF_STOCK; i++)
        if (stock[i].styleNo == styleNumber)
            return true;
    
    return false;
}

// function that lets user enter a record on current stock
void enterRecord()
{
    int userChoice;
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