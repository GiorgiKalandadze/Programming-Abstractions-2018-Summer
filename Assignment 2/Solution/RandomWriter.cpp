/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Baghdavadze]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include <string>
#include <stack>
#include "set.h"
#include "vector.h"
using namespace std;

int const charNumber = 2000;

//Function prototype
//gets markov number between 1 and 10
int getInt();
/* 
 *	Read file and saves all informarion in map , key is string and 
 *	value is vector of chars
 */
void makeStatistics(int k , Map<string,Vector<char>> &statistics);
// generates new random text with markov algorithm 
void randomText(Map<string,Vector<char>> &statistics);


int main() {
	Map<string,Vector<char>> statistics;
	int k = getInt();
	makeStatistics( k , statistics );
	randomText(statistics);
	cout<<endl;
    return 0;
}

int getInt() {
	while(true){
		cout << "Please, specify order: ";
		int result;
		result = getInteger();
		if(result >= 1 && result <= 10 ) {
			return result;
		}		
	}
	
}

void makeStatistics(int k , Map<string,Vector<char>> &statistics) {
	ifstream fileReader;
	string fileName;
	cout << "Please, enter filename: ";
	fileName = getLine();
	fileReader.open(fileName.c_str());
	while(fileReader.fail()) {
		fileReader.clear();
		cout << "Invalid file." << endl << "Please, enter another filename: ";
		fileName = getLine();
		fileReader.open(fileName.c_str());
	}
	string str = "";
	char ch;
	while(fileReader.get(ch)){
		if(str.length() < k ){
			str += ch;
		}else{
			Vector<char> vector;
			if(statistics.containsKey(str)){
				vector = statistics.get(str);
			}
			vector.add(ch);
			statistics.put(str , vector);
			str = str.substr(1) + ch;
		}
	}
	if(!statistics.containsKey(str)){
		Vector<char> vector;
		statistics.put(str , vector);
	}
}

void randomText(Map<string,Vector<char>> &statistics){
	string popular;
	int max = 0 ;
	foreach(string str in statistics){
		if(statistics[str].size() >= max ){
			popular = str ;
			max = statistics[str].size();	
		}
	}
	cout<<popular;
	string str = popular;
	char ch;
	for(int i = 0 ; i < charNumber ; i++){
		Vector<char> vector = statistics[str];
		if(vector.size() == 0 ){
			break;
		}
		int number = randomInteger(0 , vector.size()-1);
		ch = vector[number];
		cout<<ch;
		str = str.substr(1) + ch;
	}
}
