#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class algorithm {
	
	string line, key, garbage;	
	vector<string> keys;
	int data;
	int matrixBl[28][28]; 		//Ordered matrix containing the values from the matrix file
	
	int sizeQuery = 0;
	vector<int> tabOffset;
	int it;
	
	int indiceLetter;
	char letter;
	
	int *seqMax = 0;
	int *qMax = 0;
	
	int *H = 0;
	int *E = 0;
	int *N = 0;
	int F = 0;
	int Q;
	int R;
	int S = 0;
	
	vector<int> scoreMax;
	vector<int> offsetMax;
	vector<int> offMax;
	
	int* seqWithHighScore = 0;
	int* orderedOffset = 0;
	
	//int blossum = matrix.getMatrixBl();
	
	public :
		void substiuteMatrix(ifstream& matrixFile);
		int init(int* &H, int* &E, int &S, int &F);
		int* sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty);
		void checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab);
		void sequenceWithHighScore(int* res);
		
		int const& getMatrixBl(int l, int c);
		vector<int> const& getScoreMax();
		vector<int> const& getOffsetMax();
};
