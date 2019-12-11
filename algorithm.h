#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <map>
#include <string>
using namespace std;

#include "protein.h"
#include "sequence.h"

class algorithm {
	int offset;
		
	protein prot;
	sequence seq;
	
	vector<char>* protTab = prot.getProteinTable();
	int* sizeQuery = prot.getProteinTableSize();
	
	int max = 0;
	
	public :
		int matrix();
		int sequenceMatch(ifstream &proteinFile, ifstream &sequenceFile, vector<int>* tableauOffset);
		void checkSequence(istream& sequenceFile, int seqMaxAndOffset[][2], int it);
		int fillScoreMatrixQuery(vector<vector<int>>* scoreMatrix, char protLetter, int counter);
		int fillScoreMatrixSequence(vector<vector<int>>* scoreMatrix, char letter, int count);
		int displayMatrix(vector<vector<int>>* scoreMatrix
		);
	
	
};
