#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

	//ENSURES FIVE DRAWN CARDS WILL NOT HAVE REPEATING CARDS
bool checker(int s, int v, int a)
{
	for (int i = 0; i < a; i++)
	{
		if (cards[i].value == v)
		{
			if (cards[i].suit == s)
			{
				return false;
			}
		}
	}
	
	return true; //if no duplicate
}

/*
	//DRAWS FIVE CARDS AT A TIME
void drawCards()
{
	srand(time(NULL));
	for (int a = 0; a < 5; a++)
	{
		int n = rand() % 14;
		if (n == 9 || n == 10)
		{
			cards[a].value = 9;
		}
		else
		{
			cards[a].value = n;
		}
		
		while (1)
		{
			n = rand() % 4;
			if (checker(n, cards[a].value, a))
			{
				cards[a].suit = n;
				break;
			}
		}
	}
	
	return;
}
*/

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
		hand[i].suit = hand[i].valueInDeck % 4;
    }

}

	//SORTING OF CARDS BY SUITS AND VALUES
bool sortChecker(struct card array[], int n)
{
	for (int a = 0; a < n; a++)
	{
		if (array[a].value > array[a + 1].value)
		{
			return false;
		}
	}
	
	return true;
}

void bubble(struct card array[], int index, int n)
{	
	struct card temp;
	
	if (array[index].value > array[index + 1].value)
	{
		temp = array[index];
		array[index] = array[index + 1];
		array[index + 1] = temp;
	}
		
	if (index + 1 >= n)
	{
		return;
	}
	
	bubble(array, index + 1, n);
	
	return;
}

void sort()
{
	//SORT ACCORDING TO SUITS
	
	struct card tempRed[5];
	struct card tempBlack[5];
	
	int i = 0;
	for (int a = 0; a < 5; a++)
	{
		if (cards[a].suit % 2 == 0)
		{
			tempBlack[i] = cards[a];
			i++;
		}
	}
	
	int j = 0;
	for (int a = 0; a < 5; a++)
	{
		if (cards[a].suit % 2 != 0)
		{
			tempRed[j] = cards[a];
			j++;
		}
	}

	struct card temp;
	
	
	while (!sortChecker(tempBlack, i - 1))
	{
		bubble(tempBlack, 0, i - 1);
	}
	
	while (!sortChecker(tempRed, j - 1))
	{
		bubble(tempRed, 0, j - 1);
	}
	
	for (int a = 0; a < i; a++)
	{
		sortedSuits[a] = tempBlack[a];
	}
	
	for (int a = 0; a < j; a++)
	{
		sortedSuits[i] = tempRed[a];
		i++;
	}
	
	//SORT ACCORDING TO VALUES ONLY
	
	for (int a = 0; a < 5; a++)
	{
		sortedValues[a] = cards[a];
	}
	
	while (!sortChecker(sortedValues, 4))
	{
		bubble(sortedValues, 0, 4);
	}

	return;
}

	//PRINTS CARDS BY MATCHING INTS TO KEY (suits, values)
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

int main()
{
	struct card userHand[5];

	for (int i = 0; i < 5; i++)
		drawCards(userHand, 5);

	printCards(userHand);
	
	return 0;
}
