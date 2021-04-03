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
#include <ctype.h>

#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

//generate an account number which is the highest
int newAccountNum(struct Account account[], int arraySize)
{
	int i, highest;

	//assign account number to account->accountNumber
	highest = account[0].accountNumber;
	for (i = 0; i < arraySize; i++)
	{
		if (account[i].accountNumber > highest)
		{
			highest = account[i].accountNumber;
		}
	}
	highest++;
	return highest;
}

//Get user account details
void getAccount(struct Account* account)
{
	printf("New Account Data (Account#:%05d)\n", account->accountNumber);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");
	putchar('\n');
}

//get user login details
void getUserLogin(struct UserLogin* user_login)
{

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	getLoginName(user_login->loginName);

	printf("Enter the display name (%d chars max): ", MAX_COUNTRY);
	getCString(user_login->accountName, MIN_SIZE, MAX_COUNTRY);

	getPassword(user_login->password);
	putchar('\n');
}

//get login name and validate with no spaces
void getLoginName(char name[])
{
	int i, flag = 0;
	do
	{
		flag = 0;

		printf("Enter user login (%d chars max): ", MAX_LOGIN);
		getCString(name, MIN_SIZE, MAX_LOGIN);

		for (i = 0; name[i] != '\0' && flag == 0; i++)
		{
			if (isblank(name[i]))
			{
				flag = 1;
			}
		}

		//condition for space
		if (flag)
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}
	} while (flag);
}

//get user password with 2 digits, uppercase, lowercase, and symbols.
void getPassword(char password[])
{
	int i, flag, digit, upper, lower, symbol;
	

	do
	{
		digit = flag = upper = lower = symbol = 0;

		printf("Enter the password (must be %d chars in length): ", MAX_PASSWORD);
		getCString(password, MAX_PASSWORD, MAX_PASSWORD);

		for (i = 0; password[i] != '\0' && flag == 0; i++)
		{
			if (isdigit(password[i]))
			{
				digit++;
			}
			else if (isupper(password[i]))
			{
				upper++;
			}
			else if (islower(password[i]))
			{
				lower++;
			}
			else
			{
				symbol++;
			}
			if (digit > 2 || upper > 2 || lower > 2 || symbol > 2)
			{
				flag = 1;
			}
		}
		if (digit != 2 || upper != 2 || lower != 2 || symbol != 2)
		{
			flag = 1;
		}
		if (flag)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}
	} while (flag);
}

//get user demographic details
void getDemographic(struct Demographic* demo)
{
	int i;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");

	printf("Enter birth year (current age must be between 18 and 110): ");
	demo->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);

	printf("Enter the household Income: $");
	demo->income = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", MAX_COUNTRY);
	getCString(demo->country, MIN_SIZE, MAX_COUNTRY);

	//uppercase
	for (i = 0; demo->country[i] != '\0'; i++)
	{
		demo->country[i] = toupper(demo->country[i]);
	}
	
	putchar('\n');
}

//display update menu options for account and returns the updated values via pointer
void updateAccount(struct Account* account)
{
	int selection;

	do
	{
		selection = 0;

		printf("Account: %05d - Update Options\n", account->accountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 3);
		putchar('\n');

		//condition
		switch (selection)
		{
		case 1:
		{
			printf("Enter the account type (A=Agent | C=Customer): ");
			account->accountType = getCharOption("AC");
			putchar('\n');
		}
		break;
		case 2:
			updateUserLogin(&account->login);
			break;
		case 3:
			updateDemographic(&account->demographic);
			break;
		}
	} while (selection);
}

//display update menu options for user login and returns the updated values via pointer
void updateUserLogin(struct UserLogin* login)
{
	int selection = 0;
	do
	{
		printf("User Login: %s - Update Options\n", login->loginName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", login->accountName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 2);
		putchar('\n');

		//selection
		switch (selection)
		{
		case 1:
		{
			printf("Enter the display name (%d chars max): ", MAX_COUNTRY);
			getCString(login->accountName, MIN_SIZE, MAX_COUNTRY);
			putchar('\n');
		}
		break;
		case 2:
		{
			getPassword(login->password);
			putchar('\n');
		}
		break;
		}
	} while (selection);
}

//display update menu options for demographic and returns the updated values via pointer
void updateDemographic(struct Demographic* demo)
{
	int selection = 0,i;
	do
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->income);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 2);
		putchar('\n');

		//selection
		switch (selection)
		{
		case 1:
		{
			printf("Enter the household Income: $");
			demo->income = getPositiveDouble();
			putchar('\n');
		}
		break;
		case 2:
		{
			printf("Enter the country (%d chars max.): ", MAX_COUNTRY);
			getCString(demo->country, MIN_SIZE, MAX_COUNTRY);
			for (i = 0; demo->country[i] != '\0'; i++)
			{
				demo->country[i] = toupper(demo->country[i]);
			}
			putchar('\n');
		}
		break;
		}
	} while (selection);
}