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

//all closed tickets for a removed account is archived while the active tickets are reset to safe empty state
void removeTickets(struct Ticket tickets[], int arraySize, int accountNum)
{
	int i;

	//looping over account array
	for (i = 0; i < arraySize; i++)
	{
		//matching account number and closed ticket
		if (tickets[i].accountNum == accountNum && tickets[i].status == 0)
		{
			writeArchiveTickets(&tickets[i], 1);
		}
		//matching account number and open ticket
		else if (tickets[i].accountNum == accountNum && tickets[i].status == 1)
		{
			tickets[i].TicketNum = 0;
		}
	}
}

//close or reopen tickets 
void updateTicketStatus(struct Ticket tickets[], int option, char agentName[], char accountType)
{
	char character;

	//close a ticket
	if (option == 2)
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

				//space for message
				if (tickets->messageCount < MAX_MESSAGE)
				{
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					character = getCharOption("yYnN");
					putchar('\n');

					//leave a message
					if (character == 'y' || character == 'Y')
					{
						getMessage(tickets, agentName, accountType);
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
				//active status
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

//assign the values to the ticket array from the file
int loadTickets(struct Ticket tickets[], int arraySize)
{
	int i, count = 0, fieldCount = 0;

	FILE* fp = fopen(TICKET_FILE, "r");

	if (fp != NULL)
	{
		//looping over the file
		do
		{
			//get main ticket details
			fieldCount = fscanf(fp, "%d|%d|%d|%30[^|]|%d",
				&tickets[count].TicketNum,
				&tickets[count].accountNum,
				&tickets[count].status,
				tickets[count].subject,
				&tickets[count].messageCount);

			//correctly took input from file and space available for messages
			if (fieldCount == 5 && tickets[count].messageCount > 0)
			{
				for (i = 0; i < tickets[count].messageCount; i++)
				{
					fieldCount = fscanf(fp, "|%c|%30[^|]|%150[^|]",
						&tickets[count].message[i].accountType,
						tickets[count].message[i].displayName,
						tickets[count].message[i].messageDisplay);
				}
				//count tickets
				count++;
			}
			fgetc(fp); //remove newline

		} while (!feof(fp) && count < arraySize);

		//close file
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	return count;
}

//update the tickets file
int updateTicketFile(struct Ticket tickets[], int arraySize)
{
	int i, j, count = 0;

	FILE* fp = fopen(TICKET_FILE, "w");

	if (fp != NULL)
	{
		//looping through ticket array
		for (i = 0; i < arraySize; i++)
		{
			//valid ticket
			if (tickets[i].TicketNum > 0)
			{

				fprintf(fp, "%d|%d|%d|%s|%d|",
					tickets[i].TicketNum,
					tickets[i].accountNum,
					tickets[i].status,
					tickets[i].subject,
					tickets[i].messageCount);

				//loop for messages
				for (j = 0; j < tickets[i].messageCount; j++)
				{
					fprintf(fp, "%c|%s|%s|",
						tickets[i].message[j].accountType,
						tickets[i].message[j].displayName,
						tickets[i].message[j].messageDisplay);
				}
				fputc('\n', fp);//add newline
				//count tickets
				count++;
			}
		}
		//close file
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	return count;
}

//write archive tickets to archive file
int writeArchiveTickets(struct Ticket tickets[], int arraySize)
{
	int i, j, count = 0;

	FILE* fp = fopen(TICKET_ARCHIVE_FILE, "a");

	if (fp != NULL)
	{
		for (i = 0; i < arraySize; i++)
		{
			//closed and valid tickets
			if (tickets[i].status == 0 && tickets[i].TicketNum > 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|",
					tickets[i].TicketNum,
					tickets[i].accountNum,
					tickets[i].status,
					tickets[i].subject,
					tickets[i].messageCount);

				//loop for messages
				for (j = 0; j < tickets[i].messageCount; j++)
				{
					fprintf(fp, "%c|%s|%s|",
						tickets[i].message[j].accountType,
						tickets[i].message[j].displayName,
						tickets[i].message[j].messageDisplay);
				}
				//ticket to safe empty state
				tickets[i].TicketNum = 0;
				fputc('\n', fp); //add a newline
				//count tickets
				count++;
			}
		}
		//close file
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	return count;
}

//read archived tickets from archive file
int readArchiveTickets(void)
{
	int ticketCount = 0, msgCount = 0, i, count = 0;
	struct Ticket tmp = { 0 };

	//open a ticket
	FILE* fp = fopen(TICKET_ARCHIVE_FILE, "r");

	if (fp != NULL)
	{

		do
		{
			//read tickets main info
			count = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
				&tmp.TicketNum,
				&tmp.accountNum,
				&tmp.status,
				tmp.subject,
				&tmp.messageCount);

			//count tickets and messages upon valid input from file
			if (count == 5)
			{
				ticketCount++;
				msgCount += tmp.messageCount;
			}

			//read messages when they are present
			if (tmp.messageCount > 0)
			{
				for (i = 0; i < tmp.messageCount; i++)
				{
					fscanf(fp, "%c|%30[^|]|%150[^|]|",
						&tmp.message[i].accountType,
						tmp.message[i].displayName,
						tmp.message[i].messageDisplay);
				}
			}
			fgetc(fp); //remove newline

		} while (!feof(fp)); //end of file

		//close file
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	//display tickets and message
	printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n",
		ticketCount, msgCount);

	return ticketCount;
}


