/*
 * File: ConsecutiveHeads.cpp
 * ----------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdavadze]
 * This program calculates number of steps, 
 * which is requried to get a specific number of Heads.
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

//Constants
const double CHANCE = 0.5;	//Probability of coming either head or tail
const int NUM_HEADS = 3;	//Number of Heads to come together

//Function prototype
int tossCoin();

//Main program
int main() {
    cout << "It took " << tossCoin() << " flips to get " <<  NUM_HEADS  << " consecutive heads" << endl;
    return 0;
}

/*
 * Method which finds how many steps did it take to get a specific number of head part of coin.
 * In each step this method gives boolean value either true or false.
 * In our case let true mean head and false mean the tail.
 * Method returns int value - number of steps.
 */
int tossCoin(){
	int counter = 0;	//Count how many is left to reach NUM_HEADS
	int steps = 0; //Count steps
	
	while(counter < NUM_HEADS){
		if(randomChance(CHANCE)){
			counter++;
			cout << "heads" << endl;
		} else {
			counter = 0;
			cout << "tails" << endl;
		}
		steps++;
	}
	return steps;
}