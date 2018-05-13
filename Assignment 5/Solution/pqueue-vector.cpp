/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	return vector.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return vector.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	vector.add(value);
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) {
		error("Error Text: Vector is Empty");
	}
	string result = vector[0];
	for(int i = 0; i < vector.size(); i++) {
		if(vector[i] < result){
			result = vector[i]; //Keep minimum element
		}
	}
	return result;
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if(isEmpty()) {
		error("Error Text: Vector is Empty");
	}
	string result = vector[0];
	int indexOfResult = 0;
	for(int i = 0; i < vector.size(); i++) {
		if(vector[i] < result){
			result = vector[i]; //Keep minimum element
			indexOfResult = i; //Keep index of minimum element
		}
	}
	//Delete element
	vector.remove(indexOfResult);
	return result;
}

