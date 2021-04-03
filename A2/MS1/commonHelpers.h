/*
	==================================================
	Assignmnent #2 (Milestone-1):
	==================================================
	Name   : Rayyan Ahmed
	ID     : 140961202
	Email  : rahmed102@myseneca.ca
	Section: NCC
*/

#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_


// Test Function Prototypes
void test01_getInteger(void);
void test02_getPositiveInteger(void);
void test03_getIntFromRange(void);
void test04_getIntFromRange(void);
void test05_getDouble(void);
void test06_getPositiveDouble(void);
void test07_getCharOption(void);
void test08_getCString(void);
void test09_getCString(void);
void test10_getCString(void);

//Finding the current year
int currentYear(void);

//Clear the input buffer
void clearStandardInputBuffer(void);

//Validate the input of an integer
int getInteger(void);

//Validate the input of a positive integer
int getPositiveInteger(void);

//Validate the input of a double
double getDouble(void);

//Validate the input of a positive double
double getPositiveDouble(void);

//Validate the input of an integer within a range
int getIntFromRange(int lowerBound, int upperBound);

//Validate the input of a char from given set of characters
char getCharOption(const char validChar[]);

//Validate the input of string within a range
void getCString(char c_String[], int minChar, int maxChar);

#endif // !COMMONHELPERS_H_