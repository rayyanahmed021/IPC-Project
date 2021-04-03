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


//generate an ticket number which is the highest
int newTicketNum(struct Ticket tickets[], int arraySize)
{
	int i, highest;// count = 0;

	//assign account number to highest
	highest = tickets[0].TicketNum;
	for (i = 0; i < arraySize; i++)
	{
		if (tickets[i].TicketNum > highest)
		{
			highest = tickets[i].TicketNum;
		}
	}
	highest++;
	return highest;
}

//create a new ticket along with a message
void getNewTicket(struct Ticket tickets[], int accountNum, char displayName[])
{
	//header
	printf("New Ticket (Ticket#:%06d)\n", tickets->TicketNum);
	puts("----------------------------------------");

	//subject
	printf("Enter the ticket SUBJECT (%d chars. maximum): ", MAX_SUBJECT);
	getCString(tickets->subject, MIN_SIZE, MAX_SUBJECT);
	putchar('\n');

	//message
	getMessage(tickets, displayName, 'C');

	puts("*** New ticket created! ***\n");

	//update the details for tickets
	tickets->accountNum = accountNum;
	tickets->status = 1;
}



//take input of message and update the details
void getMessage(struct Ticket tickets[], char accountName[], char accountType)
{
	int* j = &tickets->messageCount;

	//if space is available for a message
	if (tickets->messageCount < MAX_MESSAGE)
	{
		//input
		printf("Enter the ticket message details (%d chars. maximum). ", MAX_MESSAGE_CHAR);
		puts("Press the ENTER key to submit:");
		getCString(tickets->message[(*j)].messageDisplay, MIN_SIZE, MAX_MESSAGE_CHAR);

		//update the details
		tickets->message[(*j)].accountType = accountType;
		strcpy(tickets->message[(*j)].displayName, accountName);
		(*j)++;
		putchar('\n');
	}
	else
	{
		puts("ERROR: Message limit has been reached, call ITS Support!\n");
	}
}

//close or reopen tickets 
void updateTicketStatus(struct Ticket tickets[], int accountNum, int arraySize,
	int option, char agentName[], char accountType)
{
	int i;
	char character;

	//removal of tickets related to a removed account
	if (option == 0)
	{
		for (i = 0; i < arraySize; i++)
		{
			if (tickets[i].accountNum == accountNum && tickets[i].status == 1)
			{
				tickets[i].TicketNum = 0;
			}
		}
	}
	//close a ticket
	else if (option == 2)
	{

		if (tickets->status == 0)
		{
			puts("ERROR: Ticket is already closed!\n");
		}
		else
		{
			//input
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			character = getCharOption("yYnN");
			putchar('\n');

			//if the agent wants to close the ticket
			if (character == 'y' || character == 'Y')
			{
				//update the details
				tickets->status = 0;

				//input
				if (tickets->messageCount < MAX_MESSAGE)
				{
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					character = getCharOption("yYnN");
					putchar('\n');

					//leave a message
					if (character == 'y' || character == 'Y')
					{
						if (accountType == 'A')
						{
							getMessage(tickets, agentName, accountType);
						}
						else
						{
							getMessage(tickets, agentName, accountType);
						}
					}
				}
				puts("*** Ticket closed! ***\n");
			}
		}
	}
	//open a ticket
	else if (option == 3)
	{
		if (tickets->status == 0)
		{
			//input
			printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
			character = getCharOption("yYnN");
			putchar('\n');

			//open the ticket
			if (character == 'y' || character == 'Y')
			{
				tickets->status = 1;
				puts("*** Ticket re-opened! ***\n");
			}
		}
		else
		{
			puts("ERROR: Ticket is already active!\n");
		}
	}
}

int loadTickets(struct Ticket tickets[], int arraySize)
{
	return 1;
}
