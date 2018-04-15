/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include "cmath"
using namespace std;

//Constants
//Theta for horizontal line
const double HORIZONTAL_THETA = 0;
//Theta for 60 degree line
const double SIXTY_DEGREE_THETA = 60;

//Function Prototype
/* This method draws Sierpinski Triangle 
 * according to its row and length.
 * It gets values for triangle's row, length and coordiantes
 */
void drawTree(GWindow& window, int n, int length, GPoint p);


int main() {
	GWindow window;
	
	int length = getInteger("Enter length: "); //Ask user to enter length of triangle
	while(length <= 0 ){
		cout << "Wrong input - Length should be positive" << endl;
		length = getInteger("Enter length: ");
	}
	int n = getInteger("Enter Row: "); //Ask use to enter row of triangle
	
	/* Triangle must be drawn in center. So triangle's center should be in window's centre,
	 * So left-bottom point of triangle should be on coordinate mentioned below
	 * Height of equilateral traingle = length * sqrt(3.0) / 2;
	 */
	GPoint p(window.getWidth() / 2 - length / 2, window.getHeight() / 2 + length * sqrt(3.0) / 4);
	
	drawTree(window, n, length, p);
	
	system("pause");
	return 0;
}


void drawTree(GWindow& window, int n, int length, GPoint p){
	//Base case. Draw triangle of zero row
	if(n == 0){
		
		window.drawPolarLine(p, length, HORIZONTAL_THETA);
		GPoint upperPoint = window.drawPolarLine(p, length, SIXTY_DEGREE_THETA);
		window.drawPolarLine(upperPoint, length, -SIXTY_DEGREE_THETA);
	
	} else { //Draw three triangles of n - 1 row
		drawTree(window, n - 1, length / 2, p);
		
		GPoint p2(p.getX() + length / 4, p.getY() - length * sqrt(3.0) / 4);
		drawTree(window, n - 1, length / 2, p2);
		
		GPoint p3(p.getX() + length / 2, p.getY());
		drawTree(window, n - 1, length / 2, p3);
	}
}