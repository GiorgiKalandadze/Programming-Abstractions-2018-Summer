/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Baghdavadze]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	
	system("pause");
    return 0;
}

bool isSubsequence(string text, string subsequence){
	/* Empty string is subsequence for all strings
	 * Even for empty string by itself
	 * So if subsequence equals to an empty string return true;
	 */
	if(subsequence == ""){
		return true;
	}
	/* Empty string has only one subsequence,
	 * empty string by itself,
	 * So if text equals empty string we should return false.
	 * First case is done in first if statement
	 */
	if(text == ""){
		return false;
	}
	/* If subsequence's first letter equals text's first letter,
	 * Remove first element for both
	 * and call method for substracted strings
	 */
	if(text[0] == subsequence[0]){
		string leftText = text.substr(1,text.length() - 1);
		string leftSubsequence = subsequence.substr(1,subsequence.length() - 1);
		return isSubsequence(leftText,leftSubsequence);
	} 

	// Else remove first element only for text
	return isSubsequence(text.substr(1,text.length() - 1), subsequence); 
}