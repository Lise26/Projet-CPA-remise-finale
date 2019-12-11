#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

class parameters {
	string nameSequence;
	string nameIndex;
	string nameHeader;
	string nameMatrix;
	int gapOpenPenalty;
	int gapExtensionPenalty;
	
	public:
		int verifParameters(int argc, char **argv);
		int initParameters(int argc, char **argv);
		int initOptionalParameters(int argc, char **argv);
		string getNameSequence();
		string getNameIndex();
		string getNameHeader();
		string getNameMatrix();
		int getGapOpenPenalty();
		int getGapExtensionPenalty();
};
