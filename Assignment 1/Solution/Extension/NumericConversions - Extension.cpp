/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdavadze]
 * This file is the starter project for the Numeric Conversions problem.
 * This method converts number from 16 base to 10 base.
 */
#include <iostream>
#include <cctype>
#include "console.h"
#include "simpio.h"
using namespace std;

//Constants
const int A = 10; //Value for character A in 16 base

//Function prototype
int converter(string s);
bool checkSequence(string text);

//Main program 
int main(){
	cout << converter("25A4F") << endl;
	return 0;
}

/*
 * This method converts integer number from hexadecimal(16 base) to 10 base
 * It takes value(number) in string, from 16 base system
 * and return integer(number) in 10 base
 */
int converter(string s){
	if(s[0] == '-'){
		return (-1) * converter(s.substr(1));
	}
	//Base case for digit
	if(s.length() == 1 && isdigit(s[0])){ 
		return s[0] - '0';
	} else if (s.length() == 1){ //Base case for letter
 		return s[0] - 'A' + A;
	}
	
	string left = s.substr(0, s.length() - 1);
	string lastSymboll = s.substr(s.length() - 1, 1);
	
	return converter(left) * 16 + converter(lastSymboll); 
}

/*
 * This method checks wether entered sequence is right
 * in other words, if it coresponds 16 base
 */
bool checkSequence(string text){
	for(int i = 0; i < text.length(); i++){
		if(i == 0 && text[0] == '-'){
			//Skip if first symboll is minus('-')
		}
		else if(!isdigit(text[i])){ //If it is not digit, we have to check if it is from A to F. Because we are in 16 base
				//Conditions
				bool c2 = (text[i] == 'A');
				bool c3 = (text[i] == 'B');
				bool c4 = (text[i] == 'C');
				bool c5 = (text[i] == 'D');
				bool c6 = (text[i] == 'E');
				bool c7 = (text[i] == 'F');
					if(!c2 && !c3 && !c4 && !c5 && !c6 && !c7 ){
						return false;
					}
		}	
	}
	return true;
}


