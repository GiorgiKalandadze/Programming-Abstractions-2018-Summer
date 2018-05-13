/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	currentSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Cell * ptr = head;
	while(ptr != NULL){
		Cell * tmp = ptr;
		ptr = ptr -> next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return currentSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return currentSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell * newCell = new Cell;
	newCell->value = value;
	Cell * ptr = head;
	//If list is empty and its first element
	if(head == NULL){
		newCell->next = NULL;
		newCell->prev = NULL;
		head = newCell;
	} else {
		newCell->next = head;
		head->prev = newCell;
		newCell->prev = NULL;
		head = newCell;
	}
	currentSize++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("Error Text");
	}
	Cell * tmp = head;
	Cell * resultPointer = tmp;
	string result = head->value;
	while(tmp != NULL){
		if(tmp->value < result){
			result = tmp->value;
		}
		tmp = tmp->next;
	}
	return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("Error Text");
		return "";
	}
	Cell * tmp = head;
	string result = head->value; //First value for instance
	Cell * ptr = tmp; //Pointer to save result pointer
	while(tmp != NULL){
		if(tmp->value < result){
			result = tmp->value;
			ptr = tmp;
		}
		tmp = tmp->next;
	}
	if(ptr->next == NULL && ptr->prev == NULL){ //First and Last
		head = NULL;
	} else if (ptr->next == NULL) { //Last
		ptr->prev->next = NULL;
	} else if (ptr->prev == NULL){ //First
		head = ptr->next;
		ptr->next->prev = NULL;
	} else {
		ptr->next->prev = ptr->prev;
		ptr->prev->next = ptr->next;
	}
	delete ptr;
	currentSize--;
	return result;
}

