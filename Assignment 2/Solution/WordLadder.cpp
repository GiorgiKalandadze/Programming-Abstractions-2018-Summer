/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: Giorgi Kalandadze]
 * Section: [TODO: Giorgi Bagdhavadze]
 * This file is the starter project for the Word Ladder problem.
 * 
 */

#include <iostream>
#include "simpio.h"
#include "lexicon.h"
#include "console.h"
#include "queue.h"
#include "vector.h"
using namespace std;

//Function Prototypes
/*
 * This method finds way which is necessary,
 * to get to the last word from the first word
 */
void findWay(Lexicon &lex, string firstWord, string lastWord);
//Breadth-first search. This method returns words from the ladder(way)
Vector<string> bfs(Queue<Vector<string>> &q, Set<string> &useds, string lastWord, Lexicon &lex, string firstWord);
//This method finds words which are different with only one letter from entered word
Set <string> getDifferStrings(string lastWord, Lexicon &lex);

//Main 
int main() {
	while (true) {
		string firstWord = getLine("Enter first word(or nothing to quit): "); //Ask user to enter first Word
		if(firstWord == ""){
			break;
		}
		string lastWord = getLine("Enter last word: ");	//Ask user to enter last word
		Lexicon lex("EnglishWords.dat"); //Create lexicon according to title
		//If first and last word have different length or they aren't in lexicon...
		if((firstWord.length() != lastWord.length()) && (!lex.contains(firstWord) || !lex.contains(lastWord))){
			cout << "No ladder found " << endl;
		} else {
			findWay(lex,firstWord,lastWord);
		}
		cout << endl;
	}
	cout << "Goodbye!" << endl;
	
	system("PAUSE");
	return 0;
}

void findWay(Lexicon &lex, string firstWord, string lastWord){
	Queue<Vector<string>> q; //Create queue to save ways
	Set<string> useds;	//Create set to save used Words
	Vector<string> v1;	
	v1.add(firstWord);
	q.enqueue(v1);
	useds.add(firstWord);

	Vector <string> ladder = bfs(q, useds, lastWord, lex, firstWord);

	for (int i = 0; i < ladder.size(); i++) {
		cout << ladder[i];
		if (!(i == ladder.size() - 1)) {
			cout << "--> ";
		}
	}
	cout << endl;

}

Vector<string> bfs(Queue<Vector<string>> &q, Set<string> &useds, string lastWord, Lexicon &lex, string firstWord){
	while (!q.isEmpty()) {
		Vector<string> v = q.dequeue();
		if (v.get(v.size() - 1) == lastWord) {
			return v;
		}
		Set <string> differWords = getDifferStrings(v.get(v.size() - 1), lex);
		foreach (string word in differWords) {
			if (!useds.contains(word) && !(word == firstWord)) {
				Vector <string> newW = v;
				newW.add(word);
				q.enqueue(newW);
			}
		}
		useds += differWords;
	}
}

Set <string> getDifferStrings(string lastWord, Lexicon &lex) {
	Set <string> result;
	for (int i = 0; i < lastWord.length(); i++) {
		string temp = lastWord;
		for (char ch = 'a'; ch <= 'z'; ch++) {	
			temp[i] = ch;
			if (lex.contains(temp)) {
				result.add(temp);
			}
		}
	}
	return result;
}