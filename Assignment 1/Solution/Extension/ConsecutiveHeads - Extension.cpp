/*
 * File: ConsecutiveHeads.cpp
 * ----------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdavadze]
 * This program calculates number of steps, 
 * which is requried to get a specific number of Sequence.
 */
#include <iostream>
#include "vector.h"
#include "console.h"
#include "random.h"
#include "simpio.h"
using namespace std;

//Probability of coming either head or tail
const double CHANCE = 0.5;

/* Method which finds how many steps did it take to get 3 head part of coin.
   In each step this method gives boolean value either true or false.
   In our case let true mean head and false mean the tail.
   Method returns int value - number of steps.
	
*/
int tossCoin(Vector<bool> v);
/*	
	This method asks user to enter sequence 
*/
Vector<bool> enterSequence();
/*
	This method checks seuence entered by user
*/
bool checkSequence(string text);
//Main
int main() {
	
	Vector<bool> v = enterSequence();
	cout << tossCoin(v) << endl;

    return 0;
}


int tossCoin(Vector<bool> list){
	int steps = 0;
	//Count steps to reach seuence
	for(int i = 0; i < list.size(); i++){
		bool side = list[i];
		while(randomChance(CHANCE) != side){
			if(side){
				cout << 'T' << endl;
			} else {
				cout << 'H' << endl;
			}
			steps++;
		}
		if(side){
				cout << 'T' << endl;
			} else {
				cout << 'H' << endl;
			}
		steps++;
	}
	return steps;
}


Vector<bool> enterSequence(){
	Vector<bool> list;
	string text = getLine("Enter Sequence: ");
	if(checkSequence(text)){
		
		for(int i = 0; i < text.length(); i++){
			if(text[i] == 'H'){
				
				list.add(true);
			} else {
				list.add(false);
			}
		}
	} else {
		cout << "Wrong Input" << endl;
	}
	return list;
}

bool checkSequence(string text){
	for(int i = 0; i < text.length(); i++){
		if(text[i] != 'H' && text[i] != 'T'){
			return false;
		}
	}
	return true;
}
