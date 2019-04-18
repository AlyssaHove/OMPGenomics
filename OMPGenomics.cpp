/*Alyssa Hove and Katheryn Weeden
Due: 4/19/19 at 19:00
Design and implement a parallelized openMP C/C++ program that will determine 
where the standard start and stop codons can be found for a sequence. 
From which you can determine the length of the actual sequence. Sequences 
from the DNA analysis will contain leading codes that have to be ignored.

1.inputs a DNA sequence using the code provided below
2.finds all the standard start codon ATG by position in the sequence
3.From each start codon, consider the subsequent codon triplets (next three characters) and search for the stop codon. The gotcha is that you have to search by triples. This isn't just a plain string search
4.As a full sequence is found, record the start position and lengths in arrays. The length can be the string length rather than the number of codons.
5.At the end of the program, print this list of information.

*/

// input a fasta file into an array. parse out header line and 
   // eliminate the newlines, etc., until end of file or new header > is found
   // LKR 4/2017
#include <iostream>
#include <string>
#include <stdio.h>
#include <omp.h>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;
int main() {

	ifstream inFastaFile("yeast.fasta", ios::in);

	if (!inFastaFile) {
		cerr << "File cannot be opened" << endl;
	}
	cout << "File opened, putting all characters in to an array" << endl;
	bool active = false; // if search is complete
	char ch; // character used in given code
	char seq[1000000]; // sequence 
	char header[255]; // header of file
	int n = 0;  //elements in the array
	int lines = 1; //number of lines for the sequence
	int length = 0;
	int seqAmount = 0; // amount of sequences
	int timeStart = 0; //
	int startLoc[2500]; // start locations
	int seqLength[2500]; // sequence length

	timeStart = GetTickCount(); // get start time

	inFastaFile.getline(header, 255);
	cout << "Search Start" << endl;

	//now process input codes until > or end of file
	while ((ch = inFastaFile.get()) != EOF) {
		if (ch >= 'A' && ch <= 'Z') seq[n++] = ch;
		if (ch == '>')break;
		if (ch == '\n') lines++;
	}
	
	int current = 0;
//#pragma omp parallel for private(i) firstprivate(seq,active)
		for (int i = 0; i < n; i++)
		{
//#pragma omp critical
			if (seq[i] == 'A' && seq[i + 1] == 'T' && seq[i + 2] == 'G' && active == false) // if sequence matches the start codon
			{
				startLoc[current] = i; // grab start
				active = true; // is it an active sequence
			
			}
			if (seq[i] == 'T' && seq[i + 1] == 'A' && seq[i + 2] == 'A' && active) {

				active = false; // sequence is now not active
				seqLength[current] = (i + 2) - startLoc[current];
				current++; // move the array space
				seqAmount++; // count the number of sequences
			}
		}

	cout << "Ticks taken to complete: " << GetTickCount() - timeStart << endl;
	cout << "The size of the array is " << n << " and there were " << lines
		<< " lines" << endl;
	cout << "Amount of sequences: " << seqAmount << endl;
	for (int j = 0; j < seqAmount; j++) {
	cout << "The start of the sequence is " << startLoc[j] << ". The length of the sequence is: " << seqLength[j] << endl;
	}

}