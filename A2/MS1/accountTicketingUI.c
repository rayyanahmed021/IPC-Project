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


//display account summary header
void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

//display account detail header
void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

//display account summary record
void displayAccountSummaryRecord(const struct Account* account)
{
	printf("%05d %-9s %5d\n", account->accountNumber,
		account->accountType == 'C' ? "CUSTOMER" : "AGENT",
		account->demographic.birth_year);
}

//display account detail record
void displayAccountDetailRecord(const struct Account* account)
{
	int i;
	printf("%05d ", account->accountNumber);
	printf("%-9s ", account->accountType == 'C' ? "CUSTOMER" : "AGENT");
	printf("%5d ", account->demographic.birth_year);
	printf("$%10.2lf ", account->demographic.income);
	printf("%-10s ", account->demographic.country);
	printf("%-15s ", account->login.accountName);
	printf("%-10s ", account->login.loginName);

	for (i = 0; account->login.password[i] != '\0'; i++)
	{
		if (i % 2 == 0)
		{
			printf("%c", account->login.password[i]);
		}
		else
		{
			printf("*");
		}

	}
	putchar('\n');
}

//summary of valid accounts
void displayAllAccountSummaryRecords(const struct Account account[], int arraySize)
{
	int i;

	displayAccountSummaryHeader();

	//loop for valid accounts
	for (i = 0; i < arraySize; i++)
	{
		//condition for valid accounts
		if (account[i].accountNumber > 0)
			displayAccountSummaryRecord(&account[i]);
	}
}

//detailed view of valid accounts
void displayAllAccountDisplayRecords(const struct Account account[], int arraySize)
{
	int i;

	displayAccountDetailHeader();

	//loop for valid accounts
	for (i = 0; i < arraySize; i++)
	{
		//condition for valid accounts
		if (account[i].accountNumber > 0)
			displayAccountDetailRecord(&account[i]);

	}
}

//entry point of application logic
void applicationStartup(struct AccountTicketingData* accountTicket)
{
	int index;

	do
	{
		index = 1;
		index = menuLogin(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);

		//Agent/customer menu
		if (accountTicket->accounts[index].accountType == 'A')
		{
			menuAgent(accountTicket, &accountTicket->accounts[index]);
		}
		else if (accountTicket->accounts[index].accountType == 'C')
		{
			clientMainMenu(&accountTicket->accounts[index], accountTicket->tickets);
		}
	} while (index != -1);

	putchar('\n');
	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");
}

//log in to system and returns matched array index 
int menuLogin(const struct Account account[], int arraySize)
{
	int selection, matched_index = -1, flag = 0, accountNumber;
	char exit = 'x';

	do
	{
		flag = 1;
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 1);
		putchar('\n');

		//selections
		switch (selection)
		{
		case 0:
		{
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			exit = getCharOption("yYnN");

			//condition
			if (exit == 'n' || exit == 'N')
			{
				flag = 0;
				putchar('\n');
			}
		}
		break;
		case 1:
		{
			//input
			printf("Enter your account#: ");
			accountNumber = getPositiveInteger();
			matched_index = findAccountIndexByAcctNum(
				accountNumber, account, arraySize, 0);
			putchar('\n');

			//condition for not matching
			if (matched_index == -1)
			{
				printf("ERROR:  Access Denied.\n");
				pauseExecution();
				flag = 0;
			}
		}
		break;
		}
	} while (flag == 0);

	return matched_index;
}

//display agent menu
void menuAgent(struct AccountTicketingData* accountTicket, const struct Account* loginUser)
{
	int selection, matchIndex = 0;
	char exitOption = 'a';

	do
	{
		printf("AGENT: %s (%05d)\n", loginUser->login.accountName, loginUser->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List accounts: summary view\n");
		printf("5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("6) List new tickets\n");
		printf("7) List active tickets\n");
		printf("8) Manage a ticket\n");
		printf("9) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 9);

		//conditions
		switch (selection)
		{
		case 0:
		{
			putchar('\n');
			printf("### LOGGED OUT ###\n\n");
		}
		break;
		case 1:
		{
			//No input
			putchar('\n');
			matchIndex = findAccountIndexByAcctNum
			(0, accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, 0);

			//condition for matching
			if (matchIndex != -1)
			{
				accountTicket->accounts[matchIndex].accountNumber = newAccountNum(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
				getAccount(&accountTicket->accounts[matchIndex]);
				getUserLogin(&accountTicket->accounts[matchIndex].login);
				getDemographic(&accountTicket->accounts[matchIndex].demographic);
				printf("*** New account added! ***\n");
			}
			else
			{
				printf("ERROR: Account listing is FULL, call ITS Support!\n");
			}
			pauseExecution();
		}
		break;
		case 2:
		{
			//input
			putchar('\n');
			matchIndex = findAccountIndexByAcctNum(loginUser->accountNumber,
				accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, 1);
			putchar('\n');

			//condition for matching
			if (matchIndex != -1)
			{
				updateAccount(&accountTicket->accounts[matchIndex]);
			}
			else
			{
				printf("Error: Access Denied\n");
				pauseExecution();
			}
		}
		break;
		case 3:
		{
			//input
			putchar('\n');
			matchIndex = findAccountIndexByAcctNum(loginUser->accountNumber,
				accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, 1);

			//condition for matching own account
			if (accountTicket->accounts[matchIndex].accountNumber == loginUser->accountNumber)
			{
				putchar('\n');
				printf("ERROR: You can't remove your own account!\n");
			}
			else if (matchIndex != -1)
			{
				displayAccountDetailHeader();
				displayAccountDetailRecord(&accountTicket->accounts[matchIndex]);
				putchar('\n');

				//confirmation
				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				exitOption = getCharOption("YN");
				putchar('\n');

				//condition for removing
				if (exitOption == 'y' || exitOption == 'Y')
				{
					accountTicket->accounts[matchIndex].accountNumber = 0;
					printf("*** Account Removed! ***\n");
				}
				else
				{
					printf("*** No changes made! ***\n");
				}
			}
			else
			{
				printf("ERROR: Access Denied.\n");
			}
			pauseExecution();
		}
		break;
		case 4:
		{
			putchar('\n');
			displayAllAccountSummaryRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		break;
		case 5:
		{
			putchar('\n');
			displayAllAccountDisplayRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		break;
		case 6:
		case 7:
		case 8:
		case 9:
		{
			putchar('\n');
			printf("Feature #%d currently unavailable!\n", selection);
			pauseExecution();
		}
		break;
		}
	} while (selection);
}

//Display Customer menu
void clientMainMenu(struct Account* account, struct Ticket* tickets)
{
	int selection;
	do
	{

		printf("CUSTOMER: %s (%d)\n", account->login.accountName, account->accountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");

		printf("1) View your account detail\n");
		printf("2) List my tickets\n");
		printf("3) Create a new ticket\n");
		printf("4) Manage a ticket\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		selection = getIntFromRange(0, 4);
		putchar('\n');

		switch (selection)
		{
		case 0:
			printf("### LOGGED OUT ###\n\n");
			break;
		case 1:
		{
			displayAccountDetailHeader();
			displayAccountDetailRecord(account);
			pauseExecution();
		}
		break;
		case 2:
		case 3:
		case 4:
		{
			printf("Feature #%d currently unavailable!\n", selection);
			pauseExecution();
		}
		break;
		}



	} while (selection);


	//case 1:
	/*
	showing account details
	otherwise
	currently not avaliable
	*/

}

/*prompt for account number if selection is 0,otherwise compares the acct number with the array
and returns matched index array(-1 for no match)*/
int findAccountIndexByAcctNum
(int accountNum, const struct Account account[], int arraySize, int selection)
{
	int i, matchIndex = -1;

	//condition for taking input
	if (selection != 0)
	{
		printf("Enter the account#: ");
		accountNum = getPositiveInteger();
	}

	//loop for comparing
	for (i = 0; i < arraySize && matchIndex == -1; i++)
	{
		if (account[i].accountNumber == accountNum)
		{
			matchIndex = i;
		}
	}
	return matchIndex;
}

// Pause execution until user enters the enter key 
void pauseExecution(void)
{
	putchar('\n');
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

