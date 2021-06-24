#include <stdio.h>
#include <stdlib.h>

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
struct stockShoes stock[51];

// assign records function
void assignStart(struct stockShoes stock[])
{
    for (int i = 0; i <= 50; i++)
    {
        stock[i].styleNo = i;

        for (int j = 0; j < 11; j++)
            stock[i].shoesBySize[j].size = j + 3;
    }
}

// menu function
void inventory()
{
    int userChoice;

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

        printf("Enter a choice: \n");
        scanf(" %d", &userChoice);
    } while (userChoice < 1 || userChoice > 5);
    
}

// main program
int main()
{
    inventory();
}