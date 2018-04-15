/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
  
	/* TODO: Add testing code here! */
	Set<string>  cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");
	
	Vector< Set<string> > locations;
	
	Set<string> first;
	first.add("A");
	first.add("B");
	first.add("C");
	
	Set<string> second;
	second.add("A");
	second.add("C");
	second.add("D");
	
	Set<string> third;
	third.add("B");
	third.add("F");
	
	Set<string> four;
	four.add("C");
	four.add("E");
	four.add("F");
	
	locations.add(first);
	locations.add(second);
	locations.add(third);
	locations.add(four);
	
	Vector< Set<string> > result;
	int numHospitals = getInteger("Enter numHospitals: ");
	cout << canOfferUniversalCoverage(cities, locations, numHospitals, result) << endl;
	cout << result << endl;
	
	return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){
								
	//Base case	1. All cities satisfied(empty)				
	if(cities.size() == 0){
		return true;
	}								  
	/* Base case 2. Locations are empty and cities not satisfied(not empty)
	 * or no hospitals left.
     * If one hospital is left and exactly it includes last cities
	 * This is considered in first if statement so no problem
	 */
	if(numHospitals < 1){
		return false;
	}
	if(locations.size() == 0 && cities.size() > 0){
		return false;
	}

	//Else 
	for(int i = 0; i < locations.size(); i++){	
		Set<string> hospital = locations[i];
		locations.remove(i);
		foreach(string city in hospital){
			if(cities.contains(city)){		  
				cities.remove(city);	
			}
		}
		if(canOfferUniversalCoverage(cities, locations, numHospitals - 1, result)){
			result.add(hospital);
			return true;
		}
		/* Return hospital in locations
		 * and hospital's cities(which that hospital includes) in Set<string> cities
		 */
		locations.insert(i, hospital);
		foreach(string city in hospital){
			cities.add(city);
		}
	}
	return false;
}


