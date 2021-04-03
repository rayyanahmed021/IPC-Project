/*
	==================================================
	Assignmnent #2 (Milestone-2):
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


//display account summary header
void displayAccountSummaryHeader(void)
{
	puts("Acct# Acct.Type Birth");
	puts("----- --------- -----");
}

//display account detail header
void displayAccountDetailHeader(void)
{
	puts("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password");
	puts("----- --------- ----- ----------- ---------- --------------- ---------- --------");
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

//display the header of the tickets for agents
void displayAgentTicketsHeader(void)
{
	puts("------ ----- --------------- ------ ------------------------------ --------");
	printf("%6s %5s %-15s %6s %-30s %8s\n",
		"Ticket", "Acct#",
		"Display Name", "Status",
		"Subject", "Messages");
	puts("------ ----- --------------- ------ ------------------------------ --------");
}

//display the header of the tickets for customers
void displayCustomerTicketsHeader(void)
{
	puts("------ ------ ------------------------------ --------");
	printf("%-6s %-6s %-30s %-8s\n", "Ticket", "Status", "Subject", "Messages");
	puts("------ ------ ------------------------------ --------");
}

//display customer tickets
void displayCustomerTickets(const struct Ticket* tickets, int arraySize, int accountNumber)
{
	int i, selection;
	do
	{
		//header
		displayCustomerTicketsHeader();

		//looping through ticket array for matching account numbers
		for (i = 0; i < arraySize; i++)
		{
			//condition for matching the account number
			if (tickets[i].accountNum == accountNumber)
			{
				printf("%06d %-6s %-30s %5d\n",
					tickets[i].TicketNum, tickets[i].status ? "OPEN" : "CLOSED",
					tickets[i].subject, tickets[i].messageCount);
			}
		}
		puts("------ ------ ------------------------------ --------\n");

		//prompt and display for messages
		selection = validateTicketNum(tickets, arraySize, accountNumber, 0);

	} while (selection);
}

//displays messages
void displayDetailedMessages(const struct Ticket tickets[])
{
	int i;

	//header
	putchar('\n');
	puts("================================================================================");
	printf("%06d (%s) Re: %s\n",
		tickets->TicketNum,
		tickets->status ? "OPEN" : "CLOSED",
		tickets->subject);
	puts("================================================================================");

	//looping through all the messages
	for (i = 0; i < tickets->messageCount; i++)
	{
		printf("%s (%s):\n", tickets->message[i].accountType == 'A' ? "AGENT" : "CUSTOMER",
			tickets->message[i].displayName);
		printf("   %s\n\n", tickets->message[i].messageDisplay);
	}
	pauseExecution();
}

//displays new or active tickets for agents only
//option 1 for new tickets while option 0 for active tickets
void displayAgentTickets(const struct Ticket tickets[], int arraySize, int option)
{
	int i, selection;

	do
	{
		//header
		displayAgentTicketsHeader();

		//looping through the ticket array for a match
		for (i = 0; i < arraySize; i++)
		{
			//option for new tickets
			if (option == 1)
			{
				//condition for new tickets
				if (tickets[i].status == 1 && tickets[i].messageCount == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n",
						tickets[i].TicketNum,
						tickets[i].accountNum,
						tickets[i].message->displayName,
						tickets[i].status == 1 ? "OPEN" : "CLOSED",
						tickets[i].subject,
						tickets[i].messageCount);
				}
			}
			//option for active tickets
			else if (option == 0)
			{
				//condition for active tickets
				if (tickets[i].status == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n",
						tickets[i].TicketNum,
						tickets[i].accountNum,
						tickets[i].message->displayName,
						"OPEN",
						tickets[i].subject,
						tickets[i].messageCount);
				}
			}
		}

		//footer
		puts("------ ----- --------------- ------ ------------------------------ --------\n");

		//prompt and display of messages based on the active or new ticket option
		if (option == 0)
		{
			selection = validateTicketNum(tickets, arraySize, 0, 6);
		}
		else
		{
			selection = validateTicketNum(tickets, arraySize, 0, 7);
		}

	} while (selection);
}


//entry point of application logic
void applicationStartup(struct AccountTicketingData* accountTicket)
{
	int index;

	do
	{
		index = 1;
		index = menuLogin(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
		putchar('\n');

		//Agent/customer menu
		if (accountTicket->accounts[index].accountType == 'A')
		{
			menuAgent(accountTicket, &accountTicket->accounts[index]);
		}
		else if (accountTicket->accounts[index].accountType == 'C')
		{
			customerMainMenu(&accountTicket->accounts[index], accountTicket->tickets, accountTicket->TICKET_MAX_SIZE);
		}
	} while (index != -1);


	puts("==============================================");
	puts("Account Ticketing System - Terminated");
	puts("==============================================");
}

//log in to system and returns matched array index 
int menuLogin(const struct Account account[], int arraySize)
{
	int selection, matched_index = -1, flag = 0;
	char exit = 'x';

	do
	{
		flag = 1;
		puts("==============================================");
		puts("Account Ticketing System - Login");
		puts("==============================================");
		puts("1) Login to the system");
		puts("0) Exit application");
		puts("----------------------------------------------\n");
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
			//login process
			matched_index = loginProcess(account, arraySize);

			//condition for not matching
			if (matched_index == -1)
			{
				puts("ERROR:  Login failed!\n");
				pauseExecution();
				flag = 0;
			}
		}
		break;
		}
	} while (!flag);

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
		puts("==============================================");
		puts("Account Ticketing System - Agent Menu");
		puts("==============================================");
		puts("1) Add a new account");
		puts("2) Modify an existing account");
		puts("3) Remove an account");
		puts("4) List accounts: summary view");
		puts("5) List accounts: detailed view");
		puts("----------------------------------------------");
		puts("6) List new tickets");
		puts("7) List active tickets");
		puts("8) Manage a ticket");
		puts("9) Archive closed tickets");
		puts("----------------------------------------------");
		puts("0) Logout\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 9);

		//conditions
		switch (selection)
		{
		case 0:
		{
			putchar('\n');
			puts("### LOGGED OUT ###\n");
		}
		break;
		case 1:
		{
			//No input
			putchar('\n');
			matchIndex = findAccountIndexByAcctNum(0, accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE, 0);

			//condition for matching
			if (matchIndex != -1)
			{
				accountTicket->accounts[matchIndex].accountNumber = newAccountNum(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
				getAccount(&accountTicket->accounts[matchIndex]);
				getUserLogin(&accountTicket->accounts[matchIndex].login);
				getDemographic(&accountTicket->accounts[matchIndex].demographic);
				puts("*** New account added! ***");
			}
			else
			{
				puts("ERROR: Account listing is FULL, call ITS Support!");
			}
			putchar('\n');
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
				puts("Error: Access Denied.\n");
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
				puts("ERROR: You can't remove your own account!");
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
					puts("*** Account Removed! ***");
				}
				else
				{
					puts("*** No changes made! ***");
				}
			}
			else
			{
				puts("ERROR: Access Denied.");
			}
			putchar('\n');
			pauseExecution();
		}
		break;
		case 4:
		{
			putchar('\n');
			displayAllAccountSummaryRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			putchar('\n');
			pauseExecution();
		}
		break;
		case 5:
		{
			putchar('\n');
			displayAllAccountDisplayRecords(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE);
			putchar('\n');
			pauseExecution();
		}
		break;
		case 6:
		{
			putchar('\n');
			displayAgentTickets(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE, 1);
		}
		break;
		case 7:
		{
			putchar('\n');
			displayAgentTickets(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE, 0);
		}
		break;
		case 8:
		case 9:
		{
			putchar('\n');
			printf("Feature #%d currently unavailable!\n\n", selection);
			pauseExecution();
		}
		break;
		}
	} while (selection);
}

//Display Customer menu
void customerMainMenu(struct Account* account, struct Ticket* tickets, int ticketArraySize)
{
	int selection;
	do
	{

		printf("CUSTOMER: %s (%d)\n", account->login.accountName, account->accountNumber);
		puts("==============================================");
		puts("Customer Main Menu");
		puts("==============================================");

		puts("1) View your account detail");
		puts("2) Create a new ticket");
		puts("3) Modify an active ticket");
		puts("4) List my tickets");
		puts("----------------------------------------------");
		puts("0) Logout\n");
		printf("Selection: ");

		selection = getIntFromRange(0, 4);
		putchar('\n');

		switch (selection)
		{
		case 0:
			puts("### LOGGED OUT ###\n");
			break;
		case 1:
		{
			displayAccountDetailHeader();
			displayAccountDetailRecord(account);
			putchar('\n');
			pauseExecution();
		}
		break;
		case 4:
			displayCustomerTickets(tickets, ticketArraySize, account->accountNumber);
			break;
		case 2:
		case 3:
		{
			printf("Feature #%d currently unavailable!\n\n", selection);
			pauseExecution();
		}
		break;
		}
	} while (selection);
}

//main login process
int loginProcess(const struct Account* account, int arraySize)
{
	int i, index, accountNumber = 0, valid = 0;
	char str[1000] = { '\0' };

	for (i = 2; valid != 3 && i != -1; i--)
	{
		valid = 0;

		//account Number
		index = findAccountIndexByAcctNum(accountNumber, account, arraySize, 1);

		//matched index
		if (index != -1)
			valid++;

		//User Login
		printf("User Login    : ");
		getCString(str, 1, 999);

		//matches the login name for that index
		if (strcmp(str, account[index].login.loginName) == 0)
			valid++;

		//password
		printf("Password      : ");
		getCString(str, 1, 999);

		//matches the password for that index
		if (strcmp(str, account[index].login.password) == 0)
			valid++;

		//condition for not matching any one of the details
		if (valid != 3)
		{
			printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", i);
			index = -1;
		}
	}
	return index;
}

//takes input of the ticket number and displays message for that ticket number.
//account Number is 0 for agents and a customer account number for customers
//agent option is for new and active tickets which is 0 for customers
int validateTicketNum(const struct Ticket tickets[], int arraySize, int accountNum, int agentOption)
{
	int ticketNum, i, flag = 0;

	//input
	ticketNum = getZeroPositiveInt();

	//looping through the ticket array for matching ticket number
	for (i = 0; i < arraySize && flag == 0; i++)
	{
		//condition for matching entered ticket number with the ticket number
		if (ticketNum == tickets[i].TicketNum && ticketNum != 0)
		{
			//display new tickets for agents
			if (accountNum == 0 && agentOption == 7 && tickets[i].status == 1
				&& tickets[i].messageCount == 1)
			{
				displayDetailedMessages(&tickets[i]);
				flag = 1;
			}
			//display active tickets for agents
			else if (accountNum == 0 && agentOption == 6 && tickets[i].status == 1)
			{
				displayDetailedMessages(&tickets[i]);
				flag = 1;
			}
			//match the account number if its a customer
			else if (accountNum == tickets[i].accountNum)
			{
				displayDetailedMessages(&tickets[i]);
				flag = 1;
			}
		}
	}

	//error for not matching the ticket Number
	if (!flag && ticketNum != 0)
	{
		putchar('\n');
		puts("ERROR: Invalid ticket number.\n");
		pauseExecution();
	}

	return ticketNum;
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
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

//TICKET FUNCTIONS
//==========================================================





