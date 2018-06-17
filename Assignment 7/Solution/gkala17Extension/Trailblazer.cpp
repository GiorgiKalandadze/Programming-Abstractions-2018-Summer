/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 *
 * Extension - This program uses union-find data stucture/disjoint set to draw maze
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include <iostream>
using namespace std;


//My Function Prorotypes
Grid<Vertex*> createGraph(Grid<double>& world);
void restorePath(Vertex* &ptr, Vector<Loc> &result);
bool isInBounds(Loc location, int numRows, int numCols);
void createGraphForMaze(int numRows, int numCols, Set<Edge>& edges, TrailblazerPQueue<Edge>& pq,  Grid<Node*> &clusters);

//Extension Functions
Node* makeCluster(Loc location);
Node* find(Node* node);
void unionSets(Node* first, Node* second);
bool areInSameClusters(Node* first, Node* second);

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	
	Vector<Loc> result; 
	Grid<Vertex*> graph = createGraph(world); //Crate graph according to "world"
	Vertex* startVertex = graph[start.row][start.col]; //Keep startVertex
	Vertex* endVertex = graph[end.row][end.col]; //Keep endVertex

	startVertex -> color = YELLOW;  //Color startNode yellow
	TrailblazerPQueue<Vertex*> pq;
	double priority = heuristic(start, end, world);
	pq.enqueue(startVertex, priority); //Enqueue startNode into the priority queue with priority h(startNode, endNode)
	colorCell(world, startVertex -> location, startVertex -> color);

	while(!pq.isEmpty()) { //While the queue is not empty:
		Vertex* currentVertex = pq.dequeueMin(); //Dequeue the lowest-cost node curr from the priority queue.
		currentVertex -> color = GREEN; //Color current to green	
		colorCell(world, currentVertex -> location, currentVertex -> color);
		/* If curr is the destination node endNode, you have found the shortest path from startNode
		 * to endNode and are done
		 */
		if(currentVertex == endVertex) break;
		
		//For each neighbour node  connected to curr by an edge of length L:
		for(int row = currentVertex -> location.row - 1; row <= currentVertex -> location.row + 1; row++){
			for(int col = currentVertex -> location.col - 1; col <= currentVertex -> location.col + 1; col++){
				//If coordinate is out of bounds or itself continue
				if(row < 0 || row >= graph.numRows() || col < 0 || col >= graph.numCols() ||
					(row == currentVertex -> location.row && col == currentVertex -> location.col)) {
					continue;
				}
				Vertex * neighbour = graph[row][col];
				//Set neighbour candidate distance to be dist + L.
				double neighbourNewDistance = currentVertex -> shortestDistanceYet + costFn(currentVertex -> location, neighbour -> location, world);
				if(neighbour -> color == GRAY) { //When neighbour vertex is GRAY
					neighbour -> color = YELLOW; //Color neighbour yellow
					neighbour -> shortestDistanceYet = neighbourNewDistance;
					neighbour -> parent = currentVertex; //Set neighbour's parent to be curr.
					//Enqueue neighbour into the priority queue with priority dist + L + h(neighbour, endNode)
					pq.enqueue(neighbour, neighbour -> shortestDistanceYet + heuristic(neighbour -> location, end, world));
					colorCell(world, neighbour -> location, neighbour -> color);
				} else if(neighbour -> color == YELLOW && neighbour -> shortestDistanceYet > neighbourNewDistance) { //When neighbour vertice is yellow
					neighbour -> shortestDistanceYet = neighbourNewDistance; //Set neighbour's candidate distance to be dist + L.
					neighbour -> parent = currentVertex; //Set neighbour's parent to be curr
					//Update neighbour's priority in the priority queue to dist + L + h(v, endNode).
					pq.decreaseKey(neighbour, neighbour -> shortestDistanceYet + heuristic(neighbour -> location, end, world));
				}
			}
		}
	}	

	//Restore path
	restorePath(endVertex, result);
	return result;
}

Set<Edge> createMaze(int numRows, int numCols) {
	//Create graph and add edges in priority queue
	Set<Edge> edges; //Keep all edges
	TrailblazerPQueue<Edge> pq; //Add edges in priority queue 
	Grid<Node*> clusters(numRows, numCols);

	createGraphForMaze(numRows, numCols, edges, pq, clusters);
	int numOfClusters = numRows * numCols;
	//Spannin tree - result
	Set<Edge> spanningTree;
	
	while(numOfClusters > 1){
		Edge edge = pq.dequeueMin();
		Loc start = edge.start;
		Loc end = edge.end;

		Node * startNode = clusters[start.row][start.col];
		Node * endNode = clusters[end.row][end.col];

		if(!areInSameClusters(startNode, endNode)) {
			//Merge
			unionSets(startNode, endNode);
			numOfClusters--;
			spanningTree.add(edge);
		}
		
	}
	return spanningTree;
}

//My Functions
/*
 * This method creates graph according to Grid "world"
 */
Grid<Vertex*> createGraph(Grid<double>& world) {
	Grid<Vertex*> graph(world.numRows(), world.numCols());
	
	for(int row = 0; row < graph.numRows(); row++){
		for(int col = 0; col < graph.numCols(); col++){
			//Create new Vertex
			Vertex* newVertex = new Vertex;
			newVertex -> parent = NULL;
			newVertex -> shortestDistanceYet = 0;
			newVertex -> color = GRAY;
			newVertex -> location.row = row;
			newVertex -> location.col = col;
			//Add new Vertex in graph
			graph[row][col] = newVertex;
		}
	}

	return graph;
}
/*
 * This method restores path recursively according list which starts with endVertex
 */
void restorePath(Vertex* &ptr, Vector<Loc> &result) {
	if(ptr == NULL) return;

	restorePath(ptr -> parent, result);
	result.add(ptr -> location);
}
/*
 * This funtion checks whether location is in bounds or not
 */
bool isInBounds(Loc location, int numRows, int numCols){
	if(location.row < 0 || location.row >= numRows ||
		location.col < 0 || location.col >= numCols) {
		return false;
	}
	return true;
}
/*
 * This function creates graph for maze. It makes edges, then puts it in priority queue
 * randomly and also creates clusters for each vertex(Stores clusters in map).
 */
void createGraphForMaze(int numRows, int numCols, Set<Edge>& edges, TrailblazerPQueue<Edge>& pq,Grid<Node*> &clusters){
	for(int row = 0; row < numRows; row++){
		for(int col = 0; col < numCols; col++){
			Loc current = makeLoc(row, col);
			Loc right = makeLoc(row, col + 1);
			Loc down = makeLoc(row + 1, col);
			//Place each node into its own cluster.
			clusters[row][col] = makeCluster(current);
			
			if(isInBounds(right, numRows, numCols)){
				Edge newEdge = makeEdge(current, right);
				edges.add(newEdge);
				pq.enqueue(newEdge, randomReal(0, 1));
			}
			if(isInBounds(down, numRows, numCols)){
				Edge newEdge = makeEdge(current, down);
				edges.add(newEdge);
				pq.enqueue(newEdge, randomReal(0, 1));
			}
		}
	}
}



//Extension Part
Node* makeCluster(Loc location){
	Node* newNode = new Node;
	newNode -> location = location;
	newNode -> parent = newNode;
	newNode -> size = 1;
	
	return newNode;
}

//Return Represantative
Node* find(Node* node){
	if(node -> parent != node) {
		node -> parent = find(node -> parent);
	}
	return node -> parent;
}

/*
 * Merge two sets which are in different clusters
 */
void unionSets(Node* first, Node* second){
	//Find roots of vertices
	Node* firstRoot = find(first);
	Node* secondRoot = find(second);


	//If they aren't in same clusters merge them
	if(firstRoot -> size >= secondRoot -> size){
		secondRoot -> parent = firstRoot;
		firstRoot -> size += secondRoot -> size;
	} else {
		firstRoot -> parent = secondRoot;
		secondRoot -> size += firstRoot -> size;
	}
}
/*
 * Check whether vertices are in same clusters
 */
bool areInSameClusters(Node* first, Node* second){
	Node* firstRoot = find(first);
	Node* secondRoot = find(second);
	
	return firstRoot == secondRoot;
}
