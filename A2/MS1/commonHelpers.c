/*
	==================================================
	Assignmnent #2 (Milestone-1):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system 
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}
}

//Garuntee the input of an integer
int getInteger(void)
{
	int value, valid = 1;
	char newLine;
	do
	{
		valid = 1;
		newLine = 'x';
		scanf("%d%c", &value, &newLine);

		//condition
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
			valid = 0;
		}
	} while (!valid); // !(0) == 1	
	return value;
}

//Garuntee the input of a positive integer
int getPositiveInteger(void)
{
	int value, valid;
	do
	{
		valid = 1;
		value = getInteger();

		//condition for correct data type but incorrect value
		if (value <= 0)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
			valid = 0;
		}
	} while (!valid); // !(0) == 1	
	return value;
}

//Garuntee the input of a double
double getDouble(void)
{
	double value;
	int valid;
	char newLine;

	do
	{
		valid = 1;
		newLine = 'x';
		scanf("%lf%c", &value, &newLine);

		//condition
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
			valid = 0;
		}
	} while (!valid); // !(0) == 1	
	return value;
}

//Garuntee the input of a positive double
double getPositiveDouble(void)
{
	double value;
	int valid;
	do
	{
		valid = 1;
		value = getDouble();

		//condition for correct data type but incorrect value
		if (value <= 0)
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
			valid = 0;
		}
	} while (!valid); // !(0) == 1	
	return value;
}

//Garuntee the input of an integer within a range
int getIntFromRange(int lowerBound, int upperBound)
{
	int valid, value;
	do
	{
		valid = 1;
		value = getInteger();

		//condition for correct data type but incorrect value
		if (value < lowerBound || value > upperBound)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);
			valid = 0;
		}
	} while (!valid); // !(0) == 1	
	return value;
}

//Garuntee the input of a char from given set of characters
char getCharOption(const char validChar[])
{
	char character, newLine = 'x';
	int i, matched = 0;
	do
	{
		scanf("%c%c", &character, &newLine);

		//condition for correct data type
		if (newLine == '\n')
		{
			for (i = 0; validChar[i] != '\0' && matched == 0; i++)
			{
				if (character == validChar[i])
				{
					matched = 1;
				}
			}
			//condition for not matching
			if (matched == 0)
			{
				printf("ERROR: Character must be one of [%s]: ", validChar);
			}
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", validChar);
			matched = 0;
		}
	} while (!matched);
	return character;
}

//Garuntee the input of string within a range
void getCString(char c_String[], int minChar, int maxChar)
{
	int i, valid, size;
	char characters[1000] = { "\0" };
	do
	{
		//input
		valid = 1;
		scanf("%999[^\n]", characters);
		clearStandardInputBuffer();

		//size of array
		for (i = 0; characters[i] != '\0'; i++)
		{
		}
		size = i;

		//conditions for errors
		if (size != maxChar && maxChar == minChar)
		{
			printf("ERROR: String length must be exactly %d chars: ", minChar);
			valid = 0;
		}
		else if (size > maxChar)
		{
			printf("ERROR: String length must be no more than %d chars: ", maxChar);
			valid = 0;
		}
		else if (size < minChar)
		{
			printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
			valid = 0;
		}

	} while (!valid);

	//copy each value
	for (i = 0; characters[i] != '\0'; i++)
	{
		c_String[i] = characters[i];
	}
	c_String[i] = '\0';
}