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

// card strings
char cards[13][10] = {
	{"Ace\0"},
	{"Two\0"},
	{"Three\0"},
	{"Four\0"},
	{"Five\0"},
	{"Six\0"},
	{"Seven\0"},
	{"Eight\0"},
	{"Nine\0"},
	{"Ten\0"},
	{"Jack\0"},
	{"Queen\0"},
	{"King\0"}
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

int cardMatrix[7][56];

int MATRIX[28][11] = //0, 1, 2, 3 = clu, dia, spa, hea
{
	{32, 95, 95, 95, 95, 95, 95, 95, 95, 32, 9},
	{124, 32, 32, 32, 32, 32, 32, 65, 65, 124, 9},
	{124, 32 ,32, 32, 32, 95, 32, 32, 32, 124, 9},
	{124, 32, 32, 32, 40, 42, 41, 32, 32, 124, 9},
	{124, 32, 32, 40, 95, 42, 95, 41, 32, 124, 9},
	{124, 65, 65, 32, 32, 124, 32, 32, 32, 124, 9},
	{124, 95, 95, 95, 95, 95, 95, 95, 95, 124, 9},
	{32, 95, 95, 95, 95, 95, 95, 95, 95, 32, 9},
	{124, 32, 32, 32, 32, 32, 32, 65, 65, 124, 9},
	{124, 32, 32, 32, 47, 92, 32, 32, 32, 124, 9},
	{124, 32, 32, 47, 42, 42, 92, 32, 32, 124, 9},
	{124, 32, 32, 92, 42, 42, 47, 32, 32, 124, 9},
	{124, 65, 65, 32, 92, 47, 32, 32, 32, 124, 9},
	{124, 95, 95, 95, 95, 95, 95, 95, 95, 124, 9},
	{32, 95, 95, 95, 95, 95, 95, 95, 95, 32, 9},
	{124, 32, 32, 32, 32, 32, 32, 65, 65, 124, 9},
	{124, 32, 32, 32, 32, 88, 32, 32, 32, 124, 9},
	{124, 32, 32, 32, 47, 42, 92, 32, 32, 124, 9},
	{124, 32, 32, 40, 95, 42, 95, 41, 32, 124, 9},
	{124, 65, 65, 32, 32, 124, 32, 32, 32, 124, 9},
	{124, 95, 95, 95, 95, 95, 95, 95, 95, 124, 9},
	{32, 95, 95, 95, 95, 95, 95, 95, 95, 32, 9},
	{124, 32, 32, 32, 32, 32, 32, 65, 65, 124, 9},
	{124, 32, 47, 32, 86, 32, 92, 32, 32, 124, 9},
	{124, 32, 92, 42, 42, 42, 47, 32, 32, 124, 9},
	{124, 32, 32, 92, 42, 47, 32, 32, 32, 124, 9},
	{124, 65, 65, 32, 88, 32, 32, 32, 32, 124, 9},
	{124, 95, 95, 95, 95, 95, 95, 95, 95, 124, 9}
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
        } while (cardAlreadyDrawn(valueInDeck, pickedCards));

        // provide numbered card value (Ace to King)
        hand[i].value = valueInDeck % 13;
        
        // provide numbered suit value (clubs to hearts)
		hand[i].suit = valueInDeck / 13;
    }
}

// bool function that draws single card chosen out of whole deck
bool drawChoiceCard(struct card hand[], int n)
{
	int currentCard = 0;
	int suitChoice  = 0;
	int cardChoice  = 0;

	while (currentCard < 5 && suitChoice != 5)
	{
		do
		{
			system("cls");

			if (currentCard > 0)
				printf("Previous card was: %s of %s\n", cards[hand[currentCard - 1].value], suits[hand[currentCard - 1].suit]);
			
			printf("This is your card %d\n\n", currentCard + 1);
			printf("Pick a suit!\n");
			printf("1 - Clubs\n");
			printf("2 - Diamonds\n");
			printf("3 - Spades\n");
			printf("4 - Hearts\n");
			printf("5 - to go back\n\n");

			printf("Enter choice: ");
			scanf(" %d", &suitChoice);
		} while (suitChoice > 5 || suitChoice < 1);

		if (suitChoice != 5)
		{
			do
			{
				do
				{
					system("cls");

					printf("Here are the available cards in suit...\n\n");
					for (int i = 13 * (suitChoice - 1); i < 13 * (suitChoice); i++)
						if (pickedCards[i] == 0)
							printf("%2d - %s of %s\n", (i % 13) + 1, cards[i % 13], suits[suitChoice - 1]);
						else
							printf("%2d - Already Taken.\n", (i % 13) + 1);

					printf("\n\nEnter choice: ");
					scanf(" %d", &cardChoice);
				} while (cardChoice < 1 || cardChoice > 13);
		
			} while (cardAlreadyDrawn(13 * (suitChoice - 1) + (cardChoice - 1), pickedCards));
		
			hand[currentCard].value = cardChoice - 1;
			hand[currentCard].suit = suitChoice - 1;

			currentCard++;
		}
	}

	if (suitChoice != 5)
		return true;
	
	return false;
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

void valueAssign(int value)
{
	//CHANGE VALUE SLOTS IN MATRICES TO CORRESPONDING VALUE
	int v[2] = {32, 32};
	
	if (value == 9)
	{
		v[0] = '1';
		v[1] = '0';
	}
	else if (value == 10)
		v[0] = 'J';
	else if (value == 11)
		v[0] = 'Q';	
	else if (value == 12)
		v[0] = 'K';
	else if (value == 0)
		v[0] = 'A';
	else
		v[0] = value + '1';
		
	if (value != 9)
	{
		for (int a = 0; a < 2; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				MATRIX[1 + (7 * b)][7 + a] = v[0 + a];
				MATRIX[5 + (7 * b)][1 + a] = v[1 - a];
			}
		}
	}
	else
	{
		for (int a = 0; a < 2; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				MATRIX[1 + (7 * b)][7 + a] = v[0 + a];
				MATRIX[5 + (7 * b)][1 + a] = v[0 + a];
			}
		}
	}

	return;
}

void cardMatrixUpdate(int indexMATRIX, int indexCM)
{
	int temp = 0;
	
	for (int a = 0; a < 7; a++)
	{
		for (int b = 0; b < 11; b++)
		{
			cardMatrix[a][indexCM + b] = MATRIX[indexMATRIX + a][b];
			temp = indexCM + b;
		}
	}
	
	for (int a = 0; a < 7; a++)
	{
		//cardMatrix[a][53] = 32;
		cardMatrix[a][55] = '\n';
	}
	
	return;	
}	//int n, int suit, int value
		//nth card //suit //value
		
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
	
	for (int a = 0; a < 5; a++)
	{
		valueAssign(hand[a].value);
		cardMatrixUpdate(hand[a].suit * 7, (a * 10) + a);
	}
	
	for (int a = 0; a < 7; a++)
	{
		for (int b = 0; b < 56; b++)
		{
			printf("%c", cardMatrix[a][b]);
		}
	}
	
	return;
}

//CATEGORY FUNCTIONS START HERE--------------------------------------------------------------------------------
/*
	valueCat -> returns 0, 1, 2, 3, 6, 7 where
	0 = nothing
	1 = one pair
	2 = two pairs
	3 = three of a kind
	6 = full house
	7 = four of a kind
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
			ret += 1;
		else if (valueBool[a] == 3)
			ret += 3;
		else if (valueBool[a] == 4)
			ret += 7;
	}

	if (ret == 4)
		ret += 2;

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
	bool straight = straightCat(userHand);			//consec values
	bool flush = flushCat(userHand);				//same suit all
	bool royalflush = royalFlushCat(userHand);		//royal
	
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
	else if (valueCat(userHand) == 7)
	{
		printf("\nFour of a kind\n");
		return 7;
	}
	else if (valueCat(userHand) == 6)
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
	else if (valueCat(userHand) == 3)
	{
		printf("\nThree of a kind\n");
		return 3;
	}
	else if (valueCat(userHand) == 2)
	{
		printf("\nTwo pairs\n");
		return 2;
	}
	else if (valueCat(userHand) == 1)
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

// function that draws random cards for player
void optionOne(struct card userHand[])
{
	char answer;
	do
	{
		for (int i = 0; i < 52; i++)
			pickedCards[i] = 0;

		system("cls");

		drawCards(userHand, 5);

		sort(userHand, 5);

		printf("Your cards...\n");
		printCards(userHand);
		int userScore = category(userHand);

		printf("\n\n");

		printf("\nWould you like to try again? (y/n)\n");
		scanf(" %c", &answer);
	} while (tolower(answer) == 'y');
}

// function that lets the player choose their card
void optionTwo(struct card userHand[])
{
	char answer;
	do
	{
		for (int i = 0; i < 52; i++)
			pickedCards[i] = 0;

		if (!drawChoiceCard(userHand, 5))
			break;

		sort(userHand, 5);

		system("cls");

		printf("Your cards...\n");
		printCards(userHand);
		int userScore = category(userHand);

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
		} while (userChoice > 3 || userChoice < 1);

		if (userChoice == 3)
		{
			printf("\n\nGoodbye!");
			break;
		}
		else if (userChoice == 1)
		{
			int userChoice1;
			do
			{
				system("cls");

				printf("Please choose an option: \n");
				printf("1 for random cards\n");
				printf("2 for draw cards of choice\n");
				printf("3 to go back\n\n");

				printf("Enter choice: ");
				scanf(" %d", &userChoice1);
			} while (userChoice1 > 4 || userChoice1 < 1);

			if (userChoice1 == 2)
				optionTwo(hand1);
			else if (userChoice1 == 1)
				optionOne(hand1);
			
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
