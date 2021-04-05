/*
	==================================================
	Assignmnent #2 (Milestone-4):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/


//PROTOTYPES
//=============
#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_

//libraries
#include "account.h"
#include "ticket.h"
#include "commonHelpers.h"


//structure
struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

//DISPLAY FUNCTIONS
//========================================

//display account summary header
void displayAccountSummaryHeader(void);

//display account detail header
void displayAccountDetailHeader(void);

//display account summary record
void displayAccountSummaryRecord(const struct Account* account);

//display account detail record
void displayAccountDetailRecord(const struct Account* account);

//summary of valid accounts
void displayAllAccountSummaryRecords(const struct Account account[], int arraySize);

//detailed view of valid accounts
void displayAllAccountDisplayRecords(const struct Account account[], int arraySize);

//display the header of the tickets for agents
void displayAgentTicketsHeader(void);

//display the header of the tickets for customers
void displayCustomerTicketsHeader(void);

//display customer tickets
void displayCustomerTickets(const struct Ticket* tickets, int arraySize, int accountNumber);

//displays messages
void displayDetailedMessages(const struct Ticket tickets[]);

//displays new or active tickets for agents only
//option 1 for new tickets while option 0 for active tickets
void displayAgentTickets(const struct Ticket tickets[], int arraySize, int option);
//===============================================

//entry point of application logic
void applicationStartup(struct AccountTicketingData* accountTicket);

//log in to system and returns matched array index 
int menuLogin(const struct Account account[], int arraySize);

//display agent menu
void menuAgent(struct AccountTicketingData* accountTicket, const struct Account* loginUser);

//display menu for agents for updating tickets
void menuUpdateTcktAgent(struct Ticket tickets[],  char agentName[]);

//Display Customer menu
void menuCustomer(struct Account* account, struct Ticket* tickets, int ticketArraySize);

//main login process
int loginProcess(const struct Account* account, int arraySize);

//update ticket menu for customers
void menuCustomerUpdateTckt(struct Ticket tickets[], char accountName[]);

//takes input of the ticket number and displays message for that ticket number.
//account Number is 0 for agents and a customer account number for customers
//agent option is for new and active tickets which is 0 for customers
int validTicketNumMsg(const struct Ticket tickets[], int arraySize, int accountNum, int agentOption);

//prompt for account number if selection is 0,otherwise compares the acct number with the array and returns matched index array(-1 for no match)
int findAccountIndexByAcctNum(int accountNum, const struct Account account[], int arraySize, int selection);

//find ticket index in the ticket array and return the index
int findTicketIndexByTickNum
(int ticketNum, char prompt[], const struct Ticket tickets[], int arraySize, int selection);

// Pause execution until user enters the enter key
void pauseExecution(void);



#endif // !ACCOUNTTICKETINGUI_H_