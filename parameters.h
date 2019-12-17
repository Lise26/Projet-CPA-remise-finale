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
		int initOptionalParametersDefault(int argc, char **argv);
		int initOptionalParametersAll(int argc, char **argv);
		
		string getNameSequence() const&;
		string getNameIndex() const&;
		string getNameHeader() const&;
		string getNameMatrix() const&;
		int getGapOpenPenalty() const&;
		int getGapExtensionPenalty() const&;
};
