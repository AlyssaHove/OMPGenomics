/*Alyssa Hove and Katheryn Weeden
Due: 4/19/19
Design and implement a parallelized openMP C/C++ program that will determine 
where the standard start and stop codons can be found for a sequence. 
From which you can determine the length of the actual sequence. Sequences 
from the DNA analysis will contain leading codes that have to be ignored.

*/

// input a fasta file into an array. parse out header line and 
   // eliminate the newlines, etc., until end of file or new header > is found
   // LKR 4/2017
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;
int main() {
	ifstream inFastaFile("yeast.fasta", ios::in);

	if (!inFastaFile) {
		cerr << "File cannot be opened" << endl;
	}

	char seq[1000000];
	char header[255];
	int n = 0;  //elements in the array
	int lines = 1; //number of lines for the sequence

	char ch;

	//inFastaFile.getline(header, 255);

	//now process input codes until > or end of file
	while ((ch = inFastaFile.get()) != EOF) {
		if (ch >= 'A' && ch <= 'Z') seq[n++] = ch;
		if (ch == '>')break;
		if (ch == '\n') lines++;
	}

	cout << "Input complete for sequence: " << header << endl;
	cout << "The size of the array is " << n << " and there were " << lines
		<< " lines" << endl;
	seq[n] = '\0';
	cout << "The sequence is" << endl;
	cout << seq << endl;
	system("pause");
}