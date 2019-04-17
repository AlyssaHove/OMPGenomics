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
#include <fstream>
#include <iomanip>
#include <string>
#include <omp.h>
#include <Windows.h>
#include <cstdlib>
using namespace std;
int main() {

	ifstream inFastaFile("yeast.fasta", ios::in);

	if (!inFastaFile) {
		cerr << "File cannot be opened" << endl;
	}
	cout << "File opened, putting all characters in to an array" << endl;
	bool complete = false; // if search is complete
	char seq[1000000];
	char header[255];
	int locations[1000]; // array of location
	int n = 0;  //elements in the array
	int lines = 1; //number of lines for the sequence
	int start = 1;
	int stringLength = 0;
	char ch;

	inFastaFile.getline(header, 255);

	//now process input codes until > or end of file
	while ((ch = inFastaFile.get()) != EOF) {
		if (ch >= 'A' && ch <= 'Z') seq[n++] = ch;
		if (ch == '>')break;
		if (ch == '\n') lines++;
	}
	cout << "Array created" << endl;
	
	// Kinda like this from ID
	//Note: how about a 3 dimentional array
	int k = 0;
#pragma omp parallel for private(seq, i, start)
		for (int i = 0; i < n; i++)
		{
			if (seq [i] == 'A' && seq[i + 1] == 'T' && seq[i + 2] == 'G') // if sequence matches the start codon
			{
				start++; // grab locations of 
				locations[k] = i;
				k++;
			}
		}
#pragma omp 
		for(int j = 0; j < start; )

	cout << "Input complete for sequence: " << header << endl;
	cout << "The size of the array is " << n << " and there were " << lines
		<< " lines" << endl;
	seq[n] = '\0';
	cout << "The sequence is" << endl;
	cout << start << endl;
	system("pause");
}