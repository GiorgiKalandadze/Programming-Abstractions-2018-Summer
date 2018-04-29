/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

//My Constants
const int PAUSE = 1000;
const int STANDART_ROW = 4;
const int STANDART_COLUMN = 4;
const int BIG_ROW = 5;
const int BIG_COLUMN = 5;
const int NUMBER_OF_STANDART_CUBES = 16;
const int NUMBER_OF_BIG_CUBES = 25;
const int MINIMUM_SIZE_OF_WORD = 4;
const int NUMBER_OF_LETTERS_ON_CUBE = 6;
/* Function prototypes */

void welcome();
void giveInstructions();

//My Function prototypes
void gameProcess(GWindow gw);
void highlight(Grid<bool> & color);
void drawCubeCombinations(string & usersWish);
void drawLetters(Vector<char> & letters, Grid<char> & grid);
void computerRecursion(Grid<char> & grid, int row, int col, string &word, Lexicon & lx, Set<string> & computerLx, Grid<bool>  &useful, Lexicon & baseLx);
bool usersDecision();
bool userWantsSetUp();
bool userWantsBigBoggle();
bool userNeedInstruction();
bool canMakeWord(string word, Grid<char> & grid,Grid<bool> &color);
bool canFinishWord(string word, Grid<char> & grid, int index,  int row, int col, Grid<bool> &color);
bool isEnteredWordUseful(string &word, Lexicon & englishLx, Lexicon & baseLx, Grid<char> & grid, Grid<bool> &color);
Vector<string> userSetsUp(Grid<char> & grid);
Vector<char> cubeCombinationsByUser(Vector<string> & userCombs);
Vector<char> cubeCombinationsByRandom(const string cube[], int size);
Grid<bool> createColorGrid(int row, int col);
Set<string> computerMakesWords(Grid<char> & grid, Lexicon & lx, Lexicon & baseLx);


/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	welcome();
	//Ask user whether he wants instruction or not
	if(userNeedInstruction()){
		giveInstructions();
	}
	gameProcess(gw);
	
	return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* This method checks whether use needs instruction or not
 *
 */
bool userNeedInstruction(){
	while(true){
		string wish = getLine("Do you need instructions? ");
		toLowerCase(wish);
		if(wish == "yes"){
			return true;
		} else if(wish == "no"){
			return false;
		} else {
			cout << "Please Answer yes or no." << endl;
		}
	}
}
/* 
 * GAME PROCESS
 */
void gameProcess(GWindow gw){
	Grid<char> grid(STANDART_ROW, STANDART_COLUMN);
	Lexicon  baseLx; //Save users entered words(usefuls)
	Lexicon computerLx; //Save words found by computer
	Lexicon englishLx("EnglishWords.dat"); //English words Lexicon
	bool userWantsToPlay = true; //Boolean to find out users wish whether he wants to play or not
	Grid<bool> color; 
	bool userWantBigBoggle = userWantsBigBoggle();
	
	//Each Hand Process
	while(userWantsToPlay){
		if(userWantBigBoggle){
			grid.resize(BIG_ROW, BIG_COLUMN);
			drawBoard(BIG_ROW,BIG_COLUMN);
		} else {
			drawBoard(STANDART_ROW,STANDART_COLUMN); //Draw only board
		}
		color = createColorGrid(grid.numRows(), grid.numCols()); //Coor grid to highlight letters
		//Ask user whether he wants to set up the board or not 
		if(userWantsSetUp()){
			Vector<string> usersCombs = userSetsUp(grid);
			Vector<char> letters = cubeCombinationsByUser(usersCombs); //Choose letters from users configuration	
			drawLetters(letters, grid); //Draw letters acording to users configuration
		} else {
			Vector<char>  v;
			if(userWantBigBoggle){
				v = cubeCombinationsByRandom(BIG_BOGGLE_CUBES, NUMBER_OF_BIG_CUBES);
			} else {
				v = cubeCombinationsByRandom(STANDARD_CUBES, NUMBER_OF_STANDART_CUBES);
			}
			drawLetters(v, grid); //Draw letters by random
		}
		cout << "Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line." << endl;
		while(true){
			string word = getLine("Enter Word: ");
			if(word == ""){ //End of the Game
				computerMakesWords(grid, englishLx, baseLx);
				userWantsToPlay = usersDecision(); //Ask user if he want to play more
				gw.clear();
				break;
			}
			word = toUpperCase(word);
			cout << grid.numCols() << endl;
			if(isEnteredWordUseful(word, englishLx, baseLx, grid, color)){ //If word is useful
				baseLx.add(word); //Add it in used words
				recordWordForPlayer(word, HUMAN);
			}
		}
	}
}
/* This method creates grid to save letters which should be highlited
 */
Grid<bool> createColorGrid(int row, int col){
	Grid<bool> grid(row,col);
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			grid[r][c] = false;
		}
	}
	return grid;
}
/* This method copys string from constant.
 * Mixes strings in vector.
 * Randomly chooses letter from string and keeps it in vector.
 */
Vector<char> cubeCombinationsByRandom(const string cube[], int size){
	Vector<string> v; //Copy strings
	Vector<char> letters; //Save random letters
	//Copy
	for(int i = 0; i < size; i++){
		v.add(cube[i]);
	}
	//Mix strings
	for(int i = 0; i < v.size(); i++){
		int x = randomInteger(i, v.size() - 1);
		string keepX = v[x];
		string keepI = v[i];
		v[x] = keepI;	
		v[i] = keepX;
	}
	//Randomly choose letter
	for(int i = 0; i < v.size(); i++){
		string combination = v[i];
		int numberOfChar = randomInteger(0, combination.length() - 1);
		char c = combination[numberOfChar];
		letters.add(c);
	}
	return letters;
}

/* This method copys string from user's configuration.
 * Mixes strings in vector.
 * Randomly chooses letter from string and keeps it in vector.
 */
Vector<char> cubeCombinationsByUser(Vector<string> & userCombs){
	Vector<string> v; //Copy strings
	Vector<char> letters; //Save random letters
	//Copy
	for(int i = 0; i < userCombs.size(); i++){
		v.add(userCombs[i]);
	}
	//Mix strings
	for(int i = 0; i < v.size(); i++){
		int x = randomInteger(i, v.size() - 1);
		string keepX = v[x];
		string keepI = v[i];
		v[x] = keepI;	
		v[i] = keepX;
	}
	//Randomly choose letter
	for(int i = 0; i < v.size(); i++){
		string combination = v[i];
		int numberOfChar = randomInteger(0, combination.length() - 1);
		char c = combination[numberOfChar];
		letters.add(c);
	}
	return letters;
}



/* This method draws letter on grid
 * It gets letters from vector. Draws from last to first. (Easy to draw)
 * So first it draws last element from vector on grid.Row and grid.Col position
 */
void drawLetters(Vector<char> & letters, Grid<char> & grid){
	for(int r = grid.numRows() - 1; r >= 0; r--){
		for(int c = grid.numCols() - 1; c >= 0; c--){
			char letter = letters[letters.size() - 1];
			letter = toupper(letter);
			grid[r][c] = letter;
			labelCube(r, c, letter);
			letters.remove(letters.size() - 1);	
		}
	}
}
/* This method checks wether entered word by user is valid or not.
 * If its length is less than 4, or its not and english word, or its already used
 * or it can be created by letters from grid, than it isn't suitable.
 */
bool isEnteredWordUseful(string  &word, Lexicon & englishLx, Lexicon & baseLx, Grid<char> & grid, Grid<bool> &color){
	if(word.length() < MINIMUM_SIZE_OF_WORD){
		cout << "I'm sorry, but we have our standards." << endl;
		cout << "That word doesn't meet the minimum word length." << endl;
		return false;
	} else if(!englishLx.contains(word)){
		cout << "That's not a word!" << endl;
		return false;
	} else if(baseLx.contains(word)){
		cout << "You've already guessed that!" << endl;
		return false;
	} else if(!canMakeWord(word, grid, color)){
		cout << "You can't make that word!" << endl;
		return false;
	}
	return true;
}
/* This method checks whether it is possible to make word with letters from grid (Wrapper)
 */
bool canMakeWord(string word, Grid<char> & grid, Grid<bool> &color){
	for(int r = 0; r < grid.numRows(); r++){
		for(int c = 0; c < grid.numCols(); c++){
			if(grid[r][c] == word[0]){
				color[r][c] = true;
				if(canFinishWord(word, grid, 1, r, c, color)){
					highlight(color);
					return true;
				}
				//Back track
				color[r][c] = false;
			}
		}
	}
	return false;
}
/* This method checks whether it is possible to make word with letters from grid.
 *
 */
bool canFinishWord(string word, Grid<char> & grid, int index, int row, int col, Grid<bool> &color){
	if(index == word.length()){
		return true;
	}
	//Check surrounding
	for(int r = row - 1; r <= row + 1; r++){
		for(int c = col - 1; c <= col + 1; c++){
			//If it is given letter
			if(r == row && c == col){
				continue;
			}
			//If grid has such point
			if(grid.inBounds(r,c)){
				if(grid[r][c] == word[index]){
					if(canFinishWord(word, grid, index + 1, r, c,color)){
						color[r][c] = true;
						return true;
					}
				}
			}	
		}
	}
	return false;
}



/* This method checks whether user wants to set configuration or not
 *
 */
bool userWantsSetUp(){
	cout << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working." << endl;
	cout << "Do you want to force the board configuration?" << endl;
	while(true){
		string choice = getLine();
		toLowerCase(choice);
		if(choice == "yes"){
			return true;
		} else if(choice == "no"){
			return false;
		} else {
			cout << "Please answer yes or no." << endl;
		}
	}
}
/* This method asks user to enter his configuration
 * It returns vector of strings.
 * Each string coresponds to a specific combination of letters
 */
Vector<string> userSetsUp(Grid<char> & grid){
	Vector<string> v;
	string combination = "";
	int numberOfCubes = grid.numRows() * grid.numCols();
	for(int i = 1; i <= numberOfCubes; i++){
		while(true){
			combination = getLine("Enter the string: ");
			if(combination.length() == NUMBER_OF_LETTERS_ON_CUBE){
				break;
			}
			cout << "String should include " << NUMBER_OF_LETTERS_ON_CUBE << " letters!" << endl;
		}
		v.add(combination);
	}
	return v;
}

/* This method finds all combinations of words from board exept words found by user already.
 */
Set<string> computerMakesWords(Grid<char> & grid, Lexicon & lx, Lexicon & baseLx){
	Set<string> computerWords; //Save words found by computer
	//Grid for find out which letters are used. First all is useful so true
	Grid<bool> useful(grid.numRows(), grid.numCols());
	for(int r = 0; r < useful.numRows(); r++){
		for(int c = 0; c < useful.numCols(); c++){
			useful[r][c] = true;
		}
	}
	//Find combinations started with each letter from board
	for(int r = 0; r < grid.numRows(); r++){
		for(int c = 0; c < grid.numCols(); c++){
			string word = string() + grid[r][c];
			useful[r][c] = false;
			computerRecursion(grid, r, c, word, lx, computerWords, useful, baseLx);
			useful[r][c] = true;
		}
	}
	return computerWords;
}
/* Computer Recursion
 */
void computerRecursion(Grid<char> & grid, int row, int col, string &word, Lexicon & lx, Set<string> & computerWords, Grid<bool> & useful, Lexicon & baseLx){
	/* If word is real(English word) and its length is more than minimum size of word according to game rules
	 * and computer hasn't found this word yet and also user, then add it to words found by computer
	 */
	if(lx.contains(word) && (word.length() >= MINIMUM_SIZE_OF_WORD) && (!computerWords.contains(word)) && (!baseLx.contains(word))){
		computerWords.add(word);
		recordWordForPlayer(word, COMPUTER);			
	}
	//Check surroundings
	for(int r = row - 1; r <= row + 1; r++){
		for(int c = col - 1; c <= col + 1; c++){
			/* If it is same letter or coodinates are out of bounds or this letter is already used
			 * we don't/can't use this letter
			 */
			if(!(r == row && c == col) && grid.inBounds(r,c) && useful[r][c]){
				useful[r][c] = false; //Make this letter used
				word += grid[r][c]; //Add this letter to final word
				//Check if there is any word started on this prefix or if word is already found
				if(lx.containsPrefix(word)){
					computerRecursion(grid,r,c,word,lx,computerWords, useful, baseLx);
				}								
				//Back track
				word = word.substr(0, word.length() - 1);
				useful[r][c] = true;
			}
		}
	}
}
/* This method finds users decision whether he wants to play another hand or not
 */
bool usersDecision(){
		while(true){
			string choice = getLine("Would you like to play again? ");
			toLowerCase(choice);
			if(choice == "yes"){
				return true;
			} else if(choice == "no"){
				return false;
			} else {
				cout << "Please answer yes or no." << endl;
			}
		}
}
/* This method higlights according letters on board and then after some time unhiglights
 */
void highlight(Grid<bool> & color){
	for(int r = 0; r < color.numRows(); r++){
		for(int c = 0; c < color.numCols(); c++){
			if(color[r][c]){
				highlightCube(r, c, true);
			}
		}
	}
	pause(PAUSE);
	for(int r = 0; r < color.numRows(); r++){
		for(int c = 0; c < color.numCols(); c++){
			if(color[r][c]){	
				highlightCube(r,c, false);
			}
		}
	}
	color = createColorGrid(color.numRows(), color.numCols()); //Make color grid full false. For new words
}
/* This method asks user whether he wants to play big boggle or not
 */
bool userWantsBigBoggle(){
	cout << "You can choose standard Boggle (4x4 grid)" << endl;
	cout << "or Big Boggle (5x5)." << endl;
	while(true){
		string choice = getLine("Would you like Big Boggle? ");
		toLowerCase(choice);
		if(choice == "yes"){
			return true;
		} else if(choice == "no"){
			return false;
		} else {
			cout << "Please answer yes or no." << endl;
		}
	}
}