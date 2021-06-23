#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

// suit strings
char suits[4][20] = {
	{"Clubs\0"},
	{"Diamonds\0"},
	{"Spades\0"},
	{"Hearts\0"}
};

// royal flush cards
int royal[5] = {12, 11, 10, 9, 0};

// array of already drawn cards
// no card is set default to 0, 
// while drawn card is set to 1.
int pickedCards[52] = {0};
	
struct card
{
	// Ace = 0, 2 = 1, 3 = 2, ... King = 12
	int value;

	// clubs = 0, diamonds = 1, spades = 2, hearts = 3
	int suit;
};

// boolean function that checks if card passed has already been drawn
// takes in value of card with respect to whole deck and checks if it is
// already in pickedCards array,
bool cardAlreadyDrawn(int valueInDeck, int pickedCards[])
{
    if (pickedCards[valueInDeck] == 1)
        return true;
    else
        pickedCards[valueInDeck] = 1;
        return false;
}

// void function that draws cards for indicated hand
// takes in 2 parameters: the card array and the number of cards in the hand
void drawCards(struct card hand[], int n)
{
	srand(time(NULL));

	int valueInDeck;

    for (int i = 0; i < n; i++)
    {
        // first pick a random number from 0 to 51
        do
        {
            valueInDeck = rand() % 52;
        }
        while (cardAlreadyDrawn(valueInDeck, pickedCards));

        // provide numbered card value (Ace to King)
        hand[i].value = valueInDeck % 13;
        
        // provide numbered suit value (clubs to hearts)
		hand[i].suit = valueInDeck / 13;
    }

}

// sort cards in indicated hand in descending order
void sort(struct card hand[], int n)
{	
	struct card temp;

	for (int i = 0; i < n; i++)
	{
		int max = hand[i].value;
		int location;
		bool found = false;

		for (int j = i + 1; j < n; j++)
		{
			if (hand[j].value > max)
			{
				max = hand[j].value;
				location = j;
				found = true;
			}
		}

		if (found)
		{
			temp = hand[location];
			hand[location] = hand[i];
			hand[i] = temp;
		}
	}
}

// void function that loops through card hand and prints
// cards according to their value and suit
void printCards(struct card hand[])
{
	for (int a = 0; a < 5; a++)
	{
		if (hand[a].value == 10)
			printf("J ");
		else if (hand[a].value == 11)
			printf("Q ");
		else if (hand[a].value == 12)
			printf("K ");
		else if (hand[a].value == 0)
			printf("A ");
		else
			printf("%d ", hand[a].value + 1);
		
		printf("%s\n", suits[hand[a].suit]);
	}
	return;
}

//CATEGORY FUNCTIONS START HERE--------------------------------------------------------------------------------
/*
	valueCat -> returns 0 - 5 where
	0 = nothing
	1 = four of a kind
	2 = one pair
	3 = three of a kind
	4 = two pairs
	5 = full house
*/
int valueCat(struct card userHand[])
{
	int valueBool[14] = {0};
	
	for (int a = 0; a < 5; a++)
	{
		valueBool[userHand[a].value]++;
	}
	
	int ret = 0;
	for (int a = 0; a < 14; a++)
	{
		if (valueBool[a] == 2)
			ret += 2;
		else if (valueBool[a] == 3)
			ret += 3;
		else if (valueBool[a] == 4)
			ret += 1;
	}

	return ret;
}

bool straightCat(struct card userHand[])
{
	int temp;
	for (int a = 0; a < 4; a++)
	{
		temp = userHand[a].value;
		if (temp - 1 != userHand[a + 1].value)
			return false;
	}
	
	return true;
}

bool flushCat(struct card userHand[])
{
	int temp = userHand[0].suit;
	for (int a = 1; a < 5; a++)
	{
		if (temp != userHand[a].suit)
			return false;
	}
	
	return true;
}

bool royalFlushCat(struct card hand[])
{
	if (flushCat)
	{
		for (int i = 0; i < 5; i++)
			if (hand[i].value != royal[i])
				return false;
		
		return true;
	}

	return false;
}

	//SORTS CARDS BY CATEGORY
int category(struct card userHand[])
{	
	bool pair1 = false;								//two values
	bool pair2 = false;								//two values, two values
	bool three = false;								//three values
	bool four = false;								//four values
	bool straight = straightCat(userHand);			//consec values
	bool flush = flushCat(userHand);				//same suit all
	bool royalflush = royalFlushCat(userHand);		//royal
	bool full = false;								//three and pair1 or pair2
	
	switch (valueCat(userHand)) 
	{
		case 1:
			four = true;
			break;
		case 2:
			pair1 = true;
			break;
		case 3:
			three = true;
			break;
		case 4:
			pair2 = true;
			break;
		case 5:
			full = true;
			break;
	}
	
	if (royalflush)
	{
		printf("\nRoyal Flush\n");
		return 9;
	}
	else if (flush && straight)
	{
		printf("\nStraight Flush\n");
		return 8;
	}
	else if (four)
	{
		printf("\nFour of a kind\n");
		return 7;
	}
	else if (full)
	{
		printf("\nFull House\n");
		return 6;
	}
	else if (flush)
	{
		printf("\nFlush\n");
		return 5;
	}
	else if (straight)
	{
		printf("\nStraight\n");
		return 4;
	}
	else if (three)
	{
		printf("\nThree of a kind\n");
		return 3;
	}
	else if (pair2)
	{
		printf("\nTwo pairs\n");
		return 2;
	}
	else if (pair1)
	{
		printf("\nOne pair\n");
		return 1;
	}
	else
	{
		printf("\nNothing\n");
		return 0;
	}
}
//CATEGORY FUNCTIONS END HERE--------------------------------------------------------------------------------

// version 2 of assignment where user is pit against computer
void versionTwo(struct card userHand[], struct card compHand[])
{
	char answer;
	do
	{
		for (int i = 0; i < 52; i++)
			pickedCards[i] = 0;

		system("cls");

		drawCards(userHand, 5);
		drawCards(compHand, 5);

		sort(userHand, 5);
		sort(compHand, 5);

		printf("Your cards...\n");
		printCards(userHand);
		int userScore = category(userHand);

		printf("\n");

		printf("Opponent's cards...\n");
		printCards(compHand);
		int compScore = category(compHand);

		printf("\n\n");

		if (userScore > compScore)
			printf("You win!!\n");
		else if (userScore < compScore)
			printf("You lose!!\n");
		else
			printf("It's a tie!\n");

		printf("\nWould you like to try again? (y/n)\n");
		scanf(" %c", &answer);
	} while (tolower(answer) == 'y');
}

// function that returns user choice regarding which version to play
int showMenu(struct card hand1[], struct card hand2[])
{
	int userChoice;

	while (true)
	{
		do
		{
			system("cls");

			printf("Welcome to Poker! (not really)\n\n");
			printf("What version would you like to play?\n");
			printf("1 for Version 1 (Draw random cards or draw of your own choice)\n");
			printf("2 for Version 2 (Game against computer's cards)\n");
			printf("3 to exit.\n\n");

			printf("Enter choice: ");
			scanf(" %d", &userChoice);
		} 
		while (userChoice > 3 || userChoice < 1);

		if (userChoice == 3)
		{
			printf("\n\nGoodbye!");
			break;
		}
		else if (userChoice == 2)
			versionTwo(hand1, hand2);
	}
}


int main()
{
	struct card userHand[5];
	struct card compHand[5];

	showMenu(userHand, compHand);
	
	return 0;
}