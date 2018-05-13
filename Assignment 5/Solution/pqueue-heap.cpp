/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue(int newSize) {
	data = new string[newSize];
	currentSize = newSize;
	logLen = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete [] data;
}

int HeapPriorityQueue::size() {
	return logLen;
}

bool HeapPriorityQueue::isEmpty() {
	return logLen == 0;
}

void HeapPriorityQueue::enqueue(string value) {
		if(logLen == currentSize){
			currentSize *= 2;
			resize(currentSize);
			data[logLen] = value;
		} else {
			data[logLen] = value;
		}
		logLen++;
		int newNodeIndex = logLen;	
		//If only one element. This beacuse avoid problem in while loop. Null pointer / Out fo bounds
		if(newNodeIndex == 1){
			return;
		}
		while(value < data[newNodeIndex / 2 - 1]){ 
			swap(data[newNodeIndex - 1], data[newNodeIndex / 2 - 1]);
			newNodeIndex = newNodeIndex / 2;
			//This beacuse avoid problem in while loop. Null pointer / Out fo bounds
			if(newNodeIndex == 1){
				break;
			}
		}
			
}	

string HeapPriorityQueue::peek() {
	if(isEmpty()){
		error("Error Text");
	}
	return data[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("Error Text");
	}
	string result = "";
	//First, swap first element with last
	swap(data[0], data[logLen - 1]);
	result = data[logLen - 1];
	logLen--;

	//Bubble down
	int indexOfParent = 1;
	int indexOfMinSon = 1;
	while(true) {
		//Has 0 son
		if(logLen  < indexOfParent * 2){
			break;
		} else if(logLen >= indexOfParent * 2 + 1){ //has 2 sons
			if(data[indexOfParent * 2 - 1] <= data[indexOfParent * 2 + 1 - 1]) {
				indexOfMinSon = indexOfParent * 2;
			} else {
				indexOfMinSon = indexOfParent * 2 + 1;
			} 
			if(data[indexOfParent - 1] < data[indexOfMinSon - 1]){
				break;
			}	
			swap(data[indexOfParent - 1], data[indexOfMinSon - 1]);
			indexOfParent = indexOfMinSon;
		} else if(logLen >= indexOfParent * 2){ //Has 1 sone SOS 2
			if(data[indexOfParent - 1] < data[indexOfParent * 2 - 1]){
				break;
			} 
			swap(data[indexOfParent - 1], data[indexOfParent * 2 - 1]);	
			indexOfParent = indexOfParent * 2;
		}	
	}	
	return result;
}
	
void HeapPriorityQueue :: resize(int newSize){
	string * tmp = new string[newSize];
	for(int i = 0; i < logLen; i++){
		tmp[i] = data[i];
	}
	delete [] data;
	data = tmp;
}