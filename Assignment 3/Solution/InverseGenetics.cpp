/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

//Returns all possible RNA stands
Set<string> listAllRNA(string protein, Map<char, Set<string> >& codons);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	//Test program
	string protein = getLine("Enter protein: "); //Enter protein name
	
	listAllRNAStrandsFor(protein, codons);
	
	system("pause");
	return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}


Set<string> listAllRNA(string protein, Map<char, Set<string> >& codons){
	/*	Base case - If protein contains only one Amino
	 *	return it's set
	 */
	if(protein.length() == 1){
		return codons.get(protein[0]) ;
	} 
	/* Else - find allRNAstrandsFor for Amino's, except first Amino of a corresponding protein,
	 * and then add first Amino's codons to others. 
	 */
	else { 
		Set<string> result; //Final result. All combinations
		char firstAmino = protein[0]; //First Amino from a apecific protein. For example: from "KWS" - "K"
		//Protein substracted, left without first character(amino) 		
		//For Example : from "KWS" - WS
		string leftProtein = protein.erase(0,1); 
		//Combinations of aminos without first amino in protein
		Set<string> withoutFirst = listAllRNA(leftProtein,codons);
		//Add first amino's codons to others
		foreach(string firstCodon in codons.get(firstAmino)){
			foreach(string otherCodon in withoutFirst){
				//add first aminos codons one by one to other's codons(ony by one)
				string res = firstCodon + otherCodon;
				//add new combination(protein) to final result
				result += res;
			}
		}
		return result;
	}
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Set<string> result = listAllRNA(protein, codons);
	cout << result << endl;
}