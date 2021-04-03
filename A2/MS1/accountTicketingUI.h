/*
	==================================================
	Assignmnent #2 (Milestone-1):
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
//===============================================

//entry point of application logic
void applicationStartup(struct AccountTicketingData* accountTicket);

//log in to system and returns matched array index 
int menuLogin(const struct Account account[], int arraySize);

//display agent menu
void menuAgent(struct AccountTicketingData* accountTicket, const struct Account* loginUser);

//Display Customer menu
void clientMainMenu(struct Account* account, struct Ticket* tickets);


//prompt for account number if selection is 0,otherwise compares the acct number with the array and returns matched index array(-1 for no match)
int findAccountIndexByAcctNum(int accountNum, const struct Account account[], int arraySize, int selection);

// Pause execution until user enters the enter key
void pauseExecution(void);



#endif // !ACCOUNTTICKETINGUI_H_