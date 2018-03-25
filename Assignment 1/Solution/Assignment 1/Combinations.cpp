/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdavadze]
 * This file is the starter project for the Combinations problem.
 * This program finds value of number in pascal triangle
 * according to position entered by user.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

//Function prototype
int pascalNumber(int n, int k);
bool checkInput(int n, int k);

//Main program
int main() {
	int n = getInteger("Enter n: ");
	int k = getInteger("Enter k: ");
	if(checkInput(n,k)){
		cout << pascalNumber(n,k) << endl;
	} else {
		cout << "Wrong Input" << endl;
	}
	return 0;
}

/* This method finds number from pascal triangle
 * according to its position by recursion
 */
int pascalNumber(int n, int k){
	if(k == 0 || n == k){
		return 1;
	}
	return pascalNumber(n - 1, k - 1) + pascalNumber(n - 1, k);
}

//This method checks if input is right(entered values by user)
bool checkInput(int n, int k){
	if(n < k || k < 0 || n < 0){
		return false;
	}
	return true;
}