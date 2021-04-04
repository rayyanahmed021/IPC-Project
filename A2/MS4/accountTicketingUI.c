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
					tickets[i].TicketNum, tickets[i].status ? "ACTIVE" : "CLOSED",
					tickets[i].subject, tickets[i].messageCount);
			}
		}
		puts("------ ------ ------------------------------ --------\n");

		//prompt and display for messages
		selection = validTicketNumMsg(tickets, arraySize, accountNumber, 0);

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
		tickets->status ? "ACTIVE" : "CLOSED",
		tickets->subject);
	puts("================================================================================");

	//looping through all the messages
	for (i = 0; i < tickets->messageCount; i++)
	{
		printf("%s (%s):\n", tickets->message[i].accountType == 'A' ? "AGENT" : "CUSTOMER",
			tickets->message[i].displayName);
		printf("   %s\n\n", tickets->message[i].messageDisplay);

		//pause after every 5 messages
		if ((i + 1) % 5 == 0)
		{
			pauseExecution();
		}
	}
	//pause at the end of the conversation
	if (i % 5)
	{
		pauseExecution();
	}
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
			if (option == 1 && tickets[i].TicketNum > 0)
			{
				//condition for new tickets
				if (tickets[i].status == 1 && tickets[i].messageCount == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n",
						tickets[i].TicketNum,
						tickets[i].accountNum,
						tickets[i].message->displayName,
						"ACTIVE",
						tickets[i].subject,
						tickets[i].messageCount);
				}
			}
			//option for active tickets
			else if (option == 0 && tickets[i].TicketNum > 0)
			{
				//condition for active tickets
				if (tickets[i].status == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n",
						tickets[i].TicketNum,
						tickets[i].accountNum,
						tickets[i].message->displayName,
						"ACTIVE",
						tickets[i].subject,
						tickets[i].messageCount);
				}
			}
			//option for closed tickets
			else if (option == 2 && tickets[i].TicketNum > 0)
			{
				if (tickets[i].status == 0)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n",
						tickets[i].TicketNum,
						tickets[i].accountNum,
						tickets[i].message->displayName,
						"CLOSED",
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
			selection = validTicketNumMsg(tickets, arraySize, 0, 6);
		}
		else if (option == 1)
		{
			selection = validTicketNumMsg(tickets, arraySize, 0, 7);
		}
		else
		{
			selection = validTicketNumMsg(tickets, arraySize, 0, 8);
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
			menuCustomer(&accountTicket->accounts[index], accountTicket->tickets, accountTicket->TICKET_MAX_SIZE);
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
	char name[31] = { "\0" };
	strcpy(name, loginUser->login.accountName);


	do
	{
		printf("AGENT: %s (%05d)\n", loginUser->login.accountName, loginUser->accountNumber);
		puts("==============================================");
		puts("Account Ticketing System - Agent Menu");
		puts("==============================================");
		puts(" 1) Add a new account");
		puts(" 2) Modify an existing account");
		puts(" 3) Remove an account");
		puts(" 4) List accounts: summary view");
		puts(" 5) List accounts: detailed view");
		puts("----------------------------------------------");
		puts(" 6) List new tickets");
		puts(" 7) List active tickets");
		puts(" 8) List closed tickets");
		puts(" 9) Manage a ticket");
		puts("10) Archive closed tickets");
		puts("----------------------------------------------");
		puts("11) View archived account statistics");
		puts("12) View archived tickets statistics");
		puts("----------------------------------------------");
		puts("0) Logout\n");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 12);

		//conditions
		switch (selection)
		{
		case 0:
		{
			putchar('\n');
			puts("Saving session modifications...");
			printf("   %d account saved.\n", 
				updateAccountFile(accountTicket->accounts, accountTicket->ACCOUNT_MAX_SIZE));
			printf("   %d tickets saved.\n", 
				updateTicketFile(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE));			
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
				accountTicket->accounts[matchIndex].accountNumber = newAccountNum(accountTicket->accounts,
					accountTicket->ACCOUNT_MAX_SIZE);
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
					updateTicketStatus(accountTicket->tickets,
						accountTicket->accounts[matchIndex].accountNumber,
						accountTicket->TICKET_MAX_SIZE, 0,
						name, 'A');

					writeRemovedAccounts(&accountTicket->accounts[matchIndex]);

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
			displayAllAccountSummaryRecords(accountTicket->accounts,
				accountTicket->ACCOUNT_MAX_SIZE);
			putchar('\n');
			pauseExecution();
		}
		break;
		case 5:
		{
			putchar('\n');
			displayAllAccountDisplayRecords(accountTicket->accounts,
				accountTicket->ACCOUNT_MAX_SIZE);
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
		{
			putchar('\n');
			displayAgentTickets(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE, 2);
		}
		break;
		case 9:
		{
			putchar('\n');
			matchIndex = findTicketIndexByTickNum(0, "ticket number",
				accountTicket->tickets,
				accountTicket->TICKET_MAX_SIZE, 1);

			if (matchIndex != -1)
			{
				menuUpdateTcktAgent(&accountTicket->tickets[matchIndex], name,
					accountTicket->TICKET_MAX_SIZE);
			}
			else
			{
				puts("ERROR: Invalid ticket number");
			}
		}
		break;
		case 10:
		{
			putchar('\n');
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			exitOption = getCharOption("yYnN");
			putchar('\n');
			if (exitOption == 'y' || exitOption == 'Y')
			{
				printf("*** %d tickets archived ***\n\n", writeArchiveTickets(accountTicket->tickets, accountTicket->TICKET_MAX_SIZE));
			}
			pauseExecution();
		}
		break;
		case 11:
		{
			putchar('\n');
			printf("There are %d account(s) currently archived.\n\n", readArchiveAccount());
			pauseExecution();
		}
		break;
		case 12:
		{
			putchar('\n');
			readArchiveTickets();
			pauseExecution();
		}
		break;
		}
	} while (selection);
}

//display menu for agents for updating tickets
void menuUpdateTcktAgent(struct Ticket tickets[], char agentName[], int arraySize)
{
	int selection;
	do
	{
		//header
		puts("----------------------------------------");
		printf("Ticket %06d - Update Options\n", tickets->TicketNum);
		puts("----------------------------------------");
		printf("Status  : %s\n", tickets->status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tickets->subject);
		printf("Acct#   : %d\n", tickets->accountNum);
		printf("Customer: %s\n", tickets->message->displayName);
		puts("----------------------------------------");
		puts("1) Add a message");
		puts("2) Close ticket");
		puts("3) Re-open ticket");
		puts("0) Done");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 3);
		putchar('\n');

		switch (selection)
		{
		case 1:
			//checking for an open ticket
			if (tickets->status == 1)
			{
				getMessage(tickets, agentName, 'A');
			}
			else
			{
				puts("ERROR: Ticket is closed - new messages are not permitted.\n");
			}
			break;
		case 2:
			updateTicketStatus(tickets, 0, arraySize, 2, agentName, 'A');
			break;
		case 3:
			updateTicketStatus(tickets, 0, arraySize, 3, agentName, 'A');
			break;
		default:
			break;
		}
	} while (selection);
}

//Display Customer menu
void menuCustomer(struct Account* account, struct Ticket* tickets, int ticketArraySize)
{
	int selection, index;
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
		{
			puts("Saving session modifications...");
			printf("   %d tickets saved.\n", updateTicketFile(tickets, ticketArraySize));
			puts("### LOGGED OUT ###\n");
		}
		break;
		case 1:
		{
			displayAccountDetailHeader();
			displayAccountDetailRecord(account);
			putchar('\n');
			pauseExecution();
		}
		break;
		case 2:
		{
			index = findTicketIndexByTickNum(0, "", tickets, ticketArraySize, 0);

			//checking for available space for new tickets
			if (index != -1 && index < ticketArraySize)
			{
				tickets[index].TicketNum = newTicketNum(tickets, ticketArraySize);
				getNewTicket(&tickets[index], account->accountNumber, account->login.accountName);
			}
			else
			{
				puts("ERROR: Ticket listing is FULL, call ITS Support!\n");
			}
			pauseExecution();
		}
		break;
		case 3:
		{
			//input for ticket number
			index = findTicketIndexByTickNum(0, "ticket number", tickets, ticketArraySize, 1);

			//checking for open and account related tickets
			if (tickets[index].status == 1 && tickets[index].accountNum == account->accountNumber)
			{
				menuCustomerUpdateTckt(&tickets[index], account->login.accountName);
			}
			else if (tickets[index].accountNum != account->accountNumber)
			{
				puts("ERROR: Invalid ticket number - you may only modify your own ticket.\n");
			}
			else if (tickets[index].status == 0)
			{
				puts("ERROR: Ticket is closed - changes are not permitted.\n");
			}
			pauseExecution();
		}
		break;
		case 4:
			displayCustomerTickets(tickets, ticketArraySize, account->accountNumber);
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

//update ticket menu for customers
void menuCustomerUpdateTckt(struct Ticket tickets[], char accountName[])
{
	int selection;

	do
	{
		//header
		puts("----------------------------------------");
		printf("Ticket %06d - Update Options\n", tickets->TicketNum);
		puts("----------------------------------------");
		printf("Status  : %s\n", tickets->status ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tickets->subject);
		puts("----------------------------------------");
		puts("1) Modify the subject");
		puts("2) Add a message");
		puts("3) Close ticket");
		puts("0) Done");
		printf("Selection: ");

		//input
		selection = getIntFromRange(0, 3);
		putchar('\n');

		switch (selection)
		{
		case 0:
			break;
		case 1:
		{
			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", MAX_SUBJECT);
			getCString(tickets->subject, MIN_SIZE, MAX_SUBJECT);
			putchar('\n');
		}
		break;
		case 2:
		{
			getMessage(tickets, accountName, 'C');
		}
		break;
		case 3:
		{
			updateTicketStatus(tickets, 0, 0, 2, accountName, 'C');
		}
		break;
		default:
			break;
		}
	} while (selection != 0 && selection != 3);
}


//takes input of the ticket number and displays message for that ticket number.
//account Number is 0 for agents and a customer account number for customers
//agent option is for new and active tickets which is 0 for customers
int validTicketNumMsg(const struct Ticket tickets[], int arraySize, int accountNum, int agentOption)
{
	int ticketNum, flag = 0, index;

	//input
	ticketNum = getZeroPositiveInt();

	if (ticketNum != 0)
	{
		index = findTicketIndexByTickNum(ticketNum, "", tickets, arraySize, 0);

		//display tickets only for agents
		if (index != -1 && accountNum == 0)
		{
			//display active tickets
			if (agentOption == 6 && tickets[index].status == 1)
			{
				displayDetailedMessages(&tickets[index]);
				flag = 1;
			}
			//display new tickets 
			else if (agentOption == 7 && tickets[index].status == 1
				&& tickets[index].messageCount == 1)
			{
				displayDetailedMessages(&tickets[index]);
				flag = 1;
			}
			//display closed tickets
			else if (agentOption == 8 && tickets[index].status == 0)
			{
				displayDetailedMessages(&tickets[index]);
				flag = 1;
			}
		}
		//tickets for customers
		else if (index != -1 && accountNum == tickets[index].accountNum)
		{
			displayDetailedMessages(&tickets[index]);
			flag = 1;
		}

		//error message
		if (!flag)
		{
			putchar('\n');
			puts("ERROR: Invalid ticket number - you may only access your own tickets.\n");
			pauseExecution();
		}
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

//find ticket index in the ticket array and return the index
int findTicketIndexByTickNum
(int ticketNum, char prompt[], const struct Ticket tickets[], int arraySize, int selection)
{
	int i, matchIndex = -1;

	//condition for taking input
	if (selection != 0)
	{
		printf("Enter %s: ", prompt);
		ticketNum = getPositiveInteger();
		putchar('\n');
	}

	//loop for comparing
	for (i = 0; i < arraySize && matchIndex == -1; i++)
	{
		if (tickets[i].TicketNum == ticketNum)
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







