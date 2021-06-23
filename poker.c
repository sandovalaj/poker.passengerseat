#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// suit strings
char suits[4][20] = {
	{"Clubs\0"},
	{"Diamonds\0"},
	{"Spades\0"},
	{"Hearts\0"}
};

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

    int valueInDeck; // 0 - 51
};

struct card cards[5];
struct card sortedSuits[5];
struct card sortedValues[5];

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

    for (int i = 0; i < n; i++)
    {
        // first pick a random number from 0 to 51
        do
        {
            hand[i].valueInDeck = rand() % 52;
        }
        while (cardAlreadyDrawn(hand[i].valueInDeck, pickedCards));

        // provide numbered card value (Ace to King)
        hand[i].value = hand[i].valueInDeck % 13;
        
        // provide numbered suit value (clubs to hearts)
		hand[i].suit = hand[i].valueInDeck / 13;
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

/*
// function that returns int of 2 - 6 based on how many cards
// of the same rank is in the hand passed.
// returns 0 if found none, 5 if there are two pairs, 6 if there is a full house
int sameRanks(struct card hand[], int n)
{
	// stores number of cards with the same rank
	// 0 - 1st card, 1 - 2nd card, ...
	int cardNo[n];

	for (int i = 0; i < n; i++)
	{
		// to count appearance of card in hand
		int timesAppeared = 0;

		for (int j = 0; j < n; j++)
		{
			if (hand[i].value == hand[j].value)
				timesAppeared++;
		}

		cardNo[i] = timesAppeared;
	}

	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (cardNo[i] > max)
			max = cardNo[i];
	}

	// check for full house
	// 3 cards that have 3 occurrences and 2 cards that have 2 occurences
	// if max is 3, there's definitely already 3 cards that have 3 occurrences,
	// so the only thing left to do is to check if there are 2 cards that have
	// 2 occurences
	if (max == 3)
	{
		int noOfPairs = 0;

		for (int i = 0; i < n; i++)
		{
			if (cardNo[i] == 2)
				noOfPairs++;
		}

		if (noOfPairs == 2)
			return 6;
	}

	// check if there are 4 cards that have 2 occurences
	else if (max == 2)
	{
		int noOfPairs = 0;
		for (int i = 0; i < n; i++)
		{
			if (cardNo[i] == 2)
				noOfPairs++;
		}

		if (noOfPairs == 4)
			return 5;
	}

	// return max value if all else fails
	if (max != 0)
		return max;
	
	// return 0 for no occurences
	return 0;
}

*/


/*
int catValue(int i, int j, int pair, int pThree)
{
	int n = 0;
	int temp; 
	for (int a = i; a < 5; a++)
	{
		temp = sortedValues[a].value;
		n++;
		
		for (int b = j; b < 5; b++)
		{
			if (a != b && temp == sortedValues[b].value)
			{
				n++;
			}
		}
		
		if (n == 2)
		{
			if (pair == 2)
			{
				return 1;
			}
			
			if (pThree == 1)
			{
				return 2;
			}
			
			pair++;
			return catValue(a + 1, a + 2, pair, pThree) + 1;
		}
		else if (n == 3)
		{
			if (pair == 1)
			{
				return 3;
			}
			
			pThree++;
			return catValue(a + 1, a + 3, pair, pThree) + 3;
		}
		else if (n == 4)
		{
			return 4;
		}
		
		n = 0;
	}
	
	return 0;
}

bool straightCat()
{
	int temp;
	for (int a = 0; a < 4; a++)
	{
		temp = sortedValues[a].value;
		if (temp + 1 != sortedValues[a + 1].value)
		{
			//printf("%d != %d", temp, sortedSuits[a].suit);
			return false;
		}
	}
	
	return true;
}

bool flushCat()
{
	int temp = sortedSuits[0].suit;
	for (int a = 1; a < 5; a++)
	{
		if (temp != sortedSuits[a].suit)
		{
			//printf("%d != %d", temp, sortedSuits[a].suit);
			return false;
		}
	}
	
	return true;
}

	//SORTS CARDS BY CATEGORY
void category()
{	
	bool pair1 = false;				//two values
	bool pair2 = false;				//two values, two values
	bool three = false;				//three values
	bool four = false;				//four values
	bool straight = straightCat();	//consec values
	bool flush = flushCat();		//same suit all
	bool full = false;				//three and pair1 or pair2
	
	int v = catValue(0, 0, 0, 0);
	switch (v) 
	{
		case 1:
			pair1 = true;
			break;
		case 2:
			pair2 = true;
			break;
		case 3:
			three = true;
			break;
		case 4:
			four = true;
			break;
		case 5:
			full = true;
			break;
	}
	
	
	if (flush && straight)
		printf("Straight and Flush\n");
	else if (full)
		printf("Full\n");
	else if (flush)
		printf("Flush\n");
	else if (straight)
		printf("Straight\n");
	else if (four)
		printf("Four of a kind\n");
	else if (three)
		printf("Three of a kind\n");
	else if (pair2)
		printf("Two pairs\n");
	else if (pair1)
		printf("One pair\n");
	else
		printf("Nothing\n");
	
	//printf(" %d\n", v);
	
	return;
}
*/

int main()
{
	system("cls");

	struct card userHand[5];

	drawCards(userHand, 5);

	sort(userHand, 5);

	printCards(userHand);
		
	return 0;
}
