/*
	==================================================
	Assignmnent #2 (Milestone-4):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#define MAX_COUNTRY 30
#define MAX_PASSWORD 8
#define MAX_LOGIN 10
#define MIN_SIZE 2
#define ACCOUNT_FILE "accounts.txt"
#define ARCHIVE_ACC_FILE "accounts_arc.txt"

struct Demographic
{
	int birth_year;
	double income;
	char country[MAX_COUNTRY + 1];
};
struct UserLogin
{
	char accountName[MAX_COUNTRY + 1];
	char loginName[MAX_LOGIN + 1];
	char password[MAX_PASSWORD + 1];
};
struct Account
{
	int accountNumber;
	char accountType;
	struct UserLogin login;
	struct Demographic demographic;
};



//prototypes
//============================




//generate an account number which is the highest
int newAccountNum(const struct Account account[], int arraySize);

//Get user account details
void getAccount(struct Account* account);

//get user login details
void getUserLogin(struct UserLogin* user_login);

//get user password with 2 digits, uppercase, lowercase, and symbols.
void getPassword(char password[]);

//get user demographic details
void getDemographic(struct Demographic* demo);

//display update menu options for account and returns the updated values via pointer
void updateAccount(struct Account* account);

//display update menu options for user login and returns the updated values via pointer
void updateUserLogin(struct UserLogin* login);

//display update menu options for demographic and returns the updated values via pointer
void updateDemographic(struct Demographic* demo);

//reads the file and assigns the values to the account array
int loadAccounts(struct Account accounts[], int arraySize);

//read archive accounts from the file
int readArchiveAccount(void);

//write accounts to the file
int writeAccounts(struct Account accounts[], int arraySize);
#endif // !ACCOUNT_H_



