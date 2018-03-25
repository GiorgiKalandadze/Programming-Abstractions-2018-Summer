/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [Giorgi Kalandadze]
 * Section: [Giorgi Bagdavadze]
 * This file is the starter project for the Flesch-Kincaid problem.
 * This  program counts Grade Level of a text according to
 * words, syllables and sentences. 
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "fstream"
#include "vector.h"
#include "filelib.h"
#include "tokenscanner.h"
#include <fstream>
#include <cctype>

using namespace std;

//Constants
const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

//Function Prototype
string enterFileName();
void daatokene(string file);
bool isWord(string token);
bool isVowel(char c);
int syllable(string token);
double findGrade();
double calculateGrade(double numWords, double numSentences, double numSyllables);

//Main
int main() {
	cout << "Grade Level: " << findGrade() << endl;
	return 0;
}

/*
 This method reads specific file and with TokenScanner finds:
 Number of Words, Number of Sentences and Number of Syllables  
 And returns Grade
*/
double findGrade(){
	//Variables
	int numWords = 0;
	int numSentences = 0;
	int numSyllables = 0;
	
	
	ifstream inputFile; //Create ifstream file
	while (true){
		string fileName = getLine("Enter file name: ");
		inputFile.open(fileName.c_str()); //requires file name
		if(!inputFile.fail()){
			break;
		}
		cout << "Wrong Input" << endl;
		inputFile.clear();
	}

	TokenScanner scanner(inputFile); //Create scanner and give it file name
	scanner.ignoreWhitespace();	//Ignore white spaces by itself. Avoid handling
	scanner.addWordCharacters("'");

	while(scanner.hasMoreTokens()){ 
		string token = scanner.nextToken();
		if(isWord(token)){
			numWords++;
			numSyllables += syllable(token);
		} else if(token[0] == '.' || token[0] == '?' || token[0] == '!'){
			numSentences++;
		}
	}
	//Make both 1
	if(numWords == 0 && numSentences == 0){
		numWords = 1;
		numSentences = 1;
	}
	inputFile.close();
	cout << "Words: " << numWords << endl;
	cout << "Syllablee: " << numSyllables << endl;
	cout << "Sentences: " << numSentences << endl;
	return calculateGrade(numWords,numSentences,numSyllables);
}
//This method checks whether specific token is word or not.
bool isWord(string token){
	//if first symboll of token isn't letter, than it isn't word
	if(!isalpha(token[0])){
		return false;
	}
	return true;
}
/*
 This method finds number of syllables in each token(word)
*/
int syllable(string token){
	int syllables = 0;

	//Check all letters except last	
	for(int i = 0; i < token.length() - 1; i++){
		//If letter is owel and next letter is consonant, than increase number of syllables
		if(isVowel(token[i]) && !isVowel(token[i + 1])){
			syllables++;
		} 
	}	
	char lastLetter = token[token.length() - 1];
	lastLetter = tolower(lastLetter);
	
	//Check last letter. If it is owel and it is not 'e', than increase number of syllables
	if(isVowel(lastLetter) && lastLetter != 'e'){
		syllables++;
	}
	//Complicated case. When last letter is 'e' and before it ther is vowel.
	if(token.length() > 1 && lastLetter == 'e' && isVowel(token[token.length() - 2])){
		syllables++;
	}
	
	//According to conditions of problem if there is no owel let syllable be one
	if(syllables == 0){
		syllables = 1;
	}
	return syllables;
}

/* 
 This method checks whether character is vowel or not
 If it is, it return true, if not - return false;
*/
bool isVowel(char c){
	c = tolower(c);
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' && isalpha(c)){
		return true;
	}
	return false;
}

/*
 This method calcualtes grade score according to formula
 It gets values for - Number of Words, Number of Sentences and Number of Syllables in text;
 Returns double value.
*/
double calculateGrade(double numWords, double numSentences, double numSyllables){
	double grade =	C0 + C1 * (numWords /  numSentences )	+ C2 * (numSyllables / numWords );
	return grade;
}