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

bool validSeat(char input[])
{
	if (input[0] < 49 || input[0] > 53)
		return false;
	
	if (toupper(input[1]) < 65 || toupper(input[1]) > 68)
		return false;
	
	return true;
}

bool takenSeat(char input[])
{
	int row = (input[0] - '0') - 1;
	int seatNum = toupper(input[1]) - 65;
	
	if (x[row].lettersBool[seatNum] != 0)
	{
		return false;
	}
	
	return true;
}

bool allSeatsTaken()
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
	bool invalid = false;
	
	while (1)
	{
		printf("\033c"); ////system cls-----------
		printf("Menu:\n1 - Enter seat\n2 - Exit\nUser Selection: ");
		
		int selection;
		scanf("%d", &selection);
		
		if (selection == 2)
		{
			printf("Are you sure you want to exit? y/n ");
			char sure[2];
			scanf("%s", sure);
			
			if (sure[0] == 'y')
				return 0;
		}
		else if (!(selection < 1 || selection > 2))
		{
			while (1)
			{
				printf("\033c"); ////system cls-----------
				print_seats();
		
				char input[5];
		
				if (taken)
				{
					printf("Seat is already occupied. Please enter another: ");
				}
				else if (invalid)
				{
					printf("Please enter a valid seat: ");
				}
				else
				{
					printf("Enter seat: ");
				}
		
				scanf("%s", input);
				
				if (!validSeat(input))
				{
					invalid = true;
					taken = false;
				}
				else if (takenSeat(input))
				{
					taken = false;
					invalid = false;
					
					printf("\033c");
					seat_input(input);
					print_seats();
					char again[5];
					
					if (allSeatsTaken())
					{
						printf("All seats are taken. Press 1 to back to main menu");
						
						int back;
						scanf("%d", &back);
						
						if (back == 1)
							break;
					}
				
					printf("Would you like to input another seat? y/n\t");
					scanf("%s", again);
				
					if (tolower(again[0]) == 'n')
					{
						break;
					}
				}
				else if (!takenSeat(input))
				{
					taken = true;
					invalid = false;
				}
			}
		}
	}
	
	return 0;
}

