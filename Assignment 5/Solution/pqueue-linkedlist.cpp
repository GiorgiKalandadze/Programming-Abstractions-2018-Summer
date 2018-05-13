/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue :: LinkedListPriorityQueue() {
	head = NULL;
	currentSize = 0;
}

LinkedListPriorityQueue :: ~LinkedListPriorityQueue() {
	Cell * ptr = head;
	while(ptr != NULL){
		Cell * tmp = ptr;
		ptr = ptr->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue :: size() {	
	return currentSize;
}

bool LinkedListPriorityQueue :: isEmpty() {
	return currentSize == 0;
}

void LinkedListPriorityQueue :: enqueue(string value) {
	Cell * newCell = new Cell;
	newCell->value = value;
	newCell->next = NULL;
	Cell * ptr = head;
	//If list is empty or with one element only and its first element
	if(head == NULL){
		head = newCell;
	} else if(head->value > value){
		newCell->next = head;
		head = newCell;
	} else {
		//Find place where that value should be insert
		while(ptr->next != NULL && ptr->next->value < value){
			ptr = ptr->next;
		}
		newCell->next = ptr->next;
		ptr->next = newCell;
	}
	currentSize++;
}

string LinkedListPriorityQueue :: peek() {
	if(isEmpty()) {
		error("Error Text");
	} 
	return head->value;
}

string LinkedListPriorityQueue :: dequeueMin() {
	if(isEmpty()) {
		error("Error Text");
	} 
	string result = "";
	Cell * tmp = head->next; //Keep second cell
	result = head->value; //Keep first's value / result
	delete head; //Delete first cell
	currentSize--; //Reduce size
	head = tmp; //Make head point on second(now first) cell
	return result;
}

