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

//display customer tickets
void displayCustomerTickets(const struct Ticket* tickets, int arraySize, int accountNumber)
{
	int i, selection;
	do
	{
		//header
		puts("------ ------ ------------------------------ --------");
		printf("%-6s %-6s %-30s %-8s\n", "Ticket", "Status", "Subject", "Messages");
		puts("------ ------ ------------------------------ --------");

		//looping through ticket array for matching account numbers
		for (i = 0; i < arraySize; i++)
		{
			//condition for matching the account number
			if (tickets[i].accountNum == accountNumber)
			{
				printf("%06d %-6s %-30s %4d\n",
					tickets[i].TicketNum, tickets[i].status ? "OPEN" : "CLOSED",
					tickets[i].subject, tickets[i].messageCount);
			}
		}
		puts("------ ------ ------------------------------ --------\n");

		//prompt and display for messages
		selection = getMessages(tickets, arraySize, accountNumber, 'C');

	} while (selection);
}

//takes input of the ticket number and displays message for that ticket number
int getMessages(const struct Ticket tickets[], int arraySize, int accountNum, char accountType)
{
	int ticketNum, i, flag = 0;

	//input
	ticketNum = getTicketNumber();

	//looping through the ticket array for matching ticket number
	for (i = 0; i < arraySize && flag == 0; i++)
	{
		//condition for matching entered ticket number with the ticket number
		if (ticketNum == tickets[i].TicketNum && ticketNum != 0)
		{
			if (accountType == 'A')
			{
				displayMessages(&tickets[i], ticketNum);
				flag = 1;
			}
			//match the account number if its a customer
			else if (accountType == 'C' && accountNum == tickets->accountNum)
			{
				displayMessages(&tickets[i], ticketNum);
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

//displays messages
void displayMessages(const struct Ticket tickets[], int ticketNum)
{
	int i;

	//header
	putchar('\n');
	puts("================================================================================");
	printf("%06d (%s) Re: %s\n", ticketNum,	tickets->status ? "OPEN" : "CLOSED", tickets->subject);
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
		puts("------ ----- --------------- ------ ------------------------------ --------");
		printf("%6s %5s %-15s %6s %-30s %8s\n",
			"Ticket", "Acct#",
			"Display Name", "Status",
			"Subject", "Messages");
		puts("------ ----- --------------- ------ ------------------------------ --------");

		//looping through the ticket array for a match
		for (i = 0; i < arraySize; i++)
		{
			//option for new tickets
			if (option == 1)
			{
				//condition for new tickets
				if (tickets[i].status == 1 && tickets[i].messageCount == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n", tickets[i].TicketNum, tickets[i].accountNum, tickets[i].message->displayName, tickets[i].status == 1 ? "OPEN" : "CLOSED", tickets[i].subject, tickets[i].messageCount);
				}
			}
			//option for active tickets
			else if (option == 0)
			{
				//condition for active tickets
				if (tickets[i].status == 1)
				{
					printf("%06d %5d %-15s %-6s %-30s %5d\n", tickets[i].TicketNum, tickets[i].accountNum, tickets[i].message->displayName, "OPEN" , tickets[i].subject, tickets[i].messageCount);
				}
			}
		}

		//footer
		puts("------ ----- --------------- ------ ------------------------------ --------\n");

		//prompt and display of messages
		selection = getMessages(tickets, arraySize, 0, 'A');

	} while (selection);
}

//takes input of an integer that is greater than or equal to zero
int getTicketNumber(void)
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
