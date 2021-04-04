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



//generate an account number which is the highest
int newAccountNum(const struct Account account[], int arraySize)
{
	int i, highest;

	//assign account number to highest
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
	puts("----------------------------------------");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");
	putchar('\n');
}

//get user login details
void getUserLogin(struct UserLogin* user_login)
{
	puts("User Login Data Input");
	puts("----------------------------------------");

	getNoSpaceString(user_login->loginName, "user login", MIN_SIZE, MAX_LOGIN);

	printf("Enter the display name (%d chars max): ", MAX_COUNTRY);
	getCString(user_login->accountName, MIN_SIZE, MAX_COUNTRY);

	getPassword(user_login->password);
	putchar('\n');
}

//get user password with 2 digits, uppercase, lowercase, and symbols.
void getPassword(char password[])
{
	int i, flag, digit, upper, lower, symbol;

	do
	{
		digit = flag = upper = lower = symbol = 0;

		//input
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
			else if (strchr("!@#$%^&*", password[i]))
			{
				symbol++;
			}
			else
			{
				flag = 1;
			}
			if (digit > 2 || upper > 2 || lower > 2 || symbol > 2 || flag)
			{
				puts("SECURITY: Password must contain 2 of each:");
				puts("          Digit: 0-9");
				puts("          UPPERCASE character");
				puts("          lowercase character");
				puts("          symbol character: !@#$%^&*");
			}
		}
	} while (flag);
}

//get user demographic details
void getDemographic(struct Demographic* demo)
{
	puts("Demographic Data Input");
	puts("----------------------------------------");

	printf("Enter birth year (current age must be between 18 and 110): ");
	demo->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);

	printf("Enter the household Income: $");
	demo->income = getPositiveDouble();

	capitalizeString(demo->country, "the country", MIN_SIZE, MAX_COUNTRY);
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
		puts("----------------------------------------");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		puts("2) Login");
		puts("3) Demographics");
		puts("0) Done");
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
		puts("----------------------------------------");
		printf("1) Display name (current value: %s)\n", login->accountName);
		puts("2) Password");
		puts("0) Done");
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
	int selection = 0;
	do
	{
		puts("Demographic Update Options");
		puts("----------------------------------------");
		printf("1) Household Income (current value: $%.2lf)\n", demo->income);
		printf("2) Country (current value: %s)\n", demo->country);
		puts("0) Done");
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
			capitalizeString(demo->country, "the country", MIN_SIZE, MAX_COUNTRY);
			putchar('\n');
		}
		break;
		}
	} while (selection);
}

//load accounts opens a file to read from accounts.txyt and ticketts.txt
int loadAccounts(struct Account accounts[], int arraySize)
{
	int i;

	FILE* fp = fopen(ACCOUNT_FILE, "r");

	if (fp != NULL)
	{
		//for loop
		for (i = 0; i < arraySize; i++)
		{
			fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]",
				&accounts[i].accountNumber,
				&accounts[i].accountType,
				accounts[i].login.accountName,
				accounts[i].login.loginName,
				accounts[i].login.password,
				&accounts[i].demographic.birth_year,
				&accounts[i].demographic.income,
				accounts[i].demographic.country);
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	return arraySize;
}

void writeRemovedAccounts(struct Account accounts[])
{
	FILE* fp = fopen(ARCHIVE_ACC_FILE, "a");
	if (fp != NULL)
	{
		//fprintf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]",
		fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
			accounts->accountNumber,
			accounts->accountType,
			accounts->login.accountName,
			accounts->login.loginName,
			accounts->login.password,
			accounts->demographic.birth_year,
			accounts->demographic.income,
			accounts->demographic.country);
		accounts->accountNumber = 0;
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
}

int readArchiveAccount(void)
{
	int count = 0;
	struct Account tmp = { 0 };

	FILE* fp = fopen(ARCHIVE_ACC_FILE, "r");

	if (fp != NULL)
	{
		while (fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]",
			&tmp.accountNumber,
			&tmp.accountType,
			tmp.login.accountName,
			tmp.login.loginName,
			tmp.login.password,
			&tmp.demographic.birth_year,
			&tmp.demographic.income,
			tmp.demographic.country) == 8)
		{
			count++;
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;

	}
	return count;
}

int updateAccountFile(struct Account accounts[], int arraySize)
{
	int i, count = 0;

	FILE* fp = fopen(TICKET_FILE, "w");

	if (fp != NULL)
	{
		for (i = 0; i < arraySize; i++)
		{
			if (accounts[i].accountNumber > 0)
			{

				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n",
					accounts[i].accountNumber,
					accounts[i].accountType,
					accounts[i].login.accountName,
					accounts[i].login.loginName,
					accounts[i].login.password,
					accounts[i].demographic.birth_year,
					accounts[i].demographic.income,
					accounts[i].demographic.country);

				fputc('\n', fp);//remove newline
				count++;
			}
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	return count;
}

