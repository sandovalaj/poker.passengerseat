#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct seats
{
	char letters[4];
	int lettersBool[4];	
};

struct seats x[5];

void struct_declaration()
{
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			x[a].letters[b] = 65 + b;
			x[a].lettersBool[b] = 0;
		}
	}
	
	return;
}

void print_seats()
{
	for (int a = 0; a < 5; a++)
	{
		printf("%d	", a + 1);
		for (int b = 0; b < 4; b++)
		{
			if (x[a].lettersBool[b] == 1)
			{
				printf("X	");
			}
			else
			{
				printf("%c	", x[a].letters[b]);
			}
		}
		
		printf("\n");
	}
	return;
}

void seat_input(char input[])
{
	int row = (input[0] - '0') - 1;
	int seatNum = toupper(input[1]) - 65;
	
	x[row].lettersBool[seatNum]++;
	return;
}

bool inputChecker(char input[])
{
	int row = (input[0] - '0') - 1;
	int seatNum = toupper(input[1]) - 65;
	
	if (x[row].lettersBool[seatNum] != 0)
	{
		return false;
	}
	
	return true;
}

bool allChecker()
{
	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			if (x[a].lettersBool[b] == 0)
			{
				return false;
			}
		}
	}
	
	return true;
}

int main()
{
	struct_declaration();
	
	bool taken = false;
	
	while (1)
	{
		printf("\033c");
		print_seats();
		
		if (allChecker())
		{
			printf("All seats are taken.");
			return 0;
		}
		
		char input[5];
		
		if (taken)
		{
			printf("Seat is already occupied. Please enter another: ");
		}
		else
		{
			printf("Enter seat: ");
		}
		
		scanf("%s", input);
		
		if (inputChecker(input))
		{
			taken = false;
			
			printf("\033c");
			seat_input(input);
			print_seats();
			char again[5];
			printf("Would you like to input another seat? y/n\t");
			scanf("%s", again);
			
			if (tolower(again[0]) == 'n')
			{
				return 0;
			}
		}
		else
		{
			taken = true;
		}
	}
	
	return 0;
}

