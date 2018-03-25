/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdavadze]
 * This file is the starter project for the Numeric Conversions problem.
 * This method is implementaition of two functions
 * 1. integerToString
 * 2. stringToInteger
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */
string intToString(int n);
int stringToInt(string str);

/* Main program */
int main() {
	return 0;
}

/*
 * This method converts integer to string
 * by recursion
 */
string intToString(int n){
	//Base case - Only one symboll
	if(n < 10){
		return string("") + char(n + '0');
	}
	return intToString(n / 10) + intToString(n % 10);
}
/*
 * This method converts string to integer
 * by recursion
 */
int stringToInt(string str){
	if(str[0] == '-'){
		string positive = str.substr(1); //Without minus ('-')
		return stringToInt(positive) * (-1);
	}
	//Base case - Only one symboll
	if(str.length() == 1){
		return str[0] - '0'; 
	}
	string leftString = str.substr(0, str.length() - 1); //String without last symboll. (Substringed)
	string lastSymboll = str.substr(str.length() - 1, 1);	//last symboll of string
	
	return stringToInt(leftString) * 10 + stringToInt(lastSymboll);
}


