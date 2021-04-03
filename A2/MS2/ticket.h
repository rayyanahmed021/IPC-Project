/*
	==================================================
	Assignmnent #2 (Milestone-2):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/

#ifndef TICKET_H_
#define TICKET_H_

//macros
#define MAX_NAME 30
#define MAX_MESSAGE_CHAR 150
#define MAX_MESSAGE 20

struct Message
{
	char accountType;
	char displayName[MAX_NAME + 1];
	char messageDisplay[MAX_MESSAGE_CHAR + 1];
};
struct Ticket
{
	int TicketNum;
	int accountNum;
	int status;
	char subject[MAX_NAME + 1];
	int messageCount;
	struct Message message[MAX_MESSAGE];
};


//FUNCTIONS
//======================================================


#endif // !TICKET_H_