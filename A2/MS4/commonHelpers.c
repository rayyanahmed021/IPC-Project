/*
	==================================================
	Assignmnent #2 (Milestone-4):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

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

//Garuntee the input of an integer that is greater or equals to 0
int getZeroPositiveInt(void)
{
	int number = 0, flag = 0;

	//prompt
	puts("Enter the ticket number to view the messages or");
	printf("0 to return to previous menu: ");

	do
	{
		flag = 0;

		//input
		number = getInteger();

		//condition
		if (number < 0)
		{
			printf("ERROR: Value must be positive or zero: ");
			flag = 1;
		}
		else if (number == 0)
		{
			putchar('\n');
			flag = 0;
		}
	} while (flag);

	return number;
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
	int matched = 1;
	do
	{
		matched = 1;
		scanf("%c%c", &character, &newLine);

		//condition for correct data type
		if (newLine == '\n')
		{
			//condition for not matching
			if (strchr(validChar, character) == NULL)
			{
				printf("ERROR: Character must be one of [%s]: ", validChar);
				matched = 0;
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
	int valid, size;
	char characters[1000] = { "\0" };
	do
	{
		//input
		valid = 1;
		scanf("%999[^\n]", characters);
		clearStandardInputBuffer();

		//size of array
		size = strlen(characters);

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
	strcpy(c_String, characters);
}

//get string and validate it has no spaces
void getNoSpaceString(char c_string[], char prompt[], int minChar, int maxChar)
{
	int i, flag;

	do
	{
		flag = 0;
		//input
		printf("Enter %s (%d chars max): ", prompt, maxChar);
		getCString(c_string, minChar, maxChar);

		//searching for space
		for (i = 0; c_string[i] != '\0' && !flag; i++)
		{
			if (isspace(c_string[i]))
			{
				flag = 1;
				puts("ERROR:  The user login must NOT contain whitespace characters.");
			}
		}
	} while (flag);
}

//get string and capitalize it
void capitalizeString(char c_string[], char prompt[], int minChar, int maxChar)
{
	int i, flag = 0;

	//input
	printf("Enter %s (%d chars max.): ", prompt, maxChar);
	getCString(c_string, minChar, maxChar);

	//searching for space
	for (i = 0; c_string[i] != '\0' && !flag; i++)
	{
		c_string[i] = toupper(c_string[i]);
	}

}
