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
	int numberSequence;
	vector<int> tabOffset;
	int it;
	
	char letter;
	
	int *seqMax;
	int max = 0;
	int *qMax = 0;
	
	int *scoreMatrix;
	int *E;
	int *F;
	int Q;
	int R;
	int S = 0;
	
	int scoreMax[50];
	//int* offsetMax;
	int offMax[50];
	
	int* seqWithHighScore = 0;
	int* orderedOffset = 0;
	
	int blossum = getMatrixBl(28,28);
	
	public :
		void substiuteMatrix(ifstream& matrixFile);
		int init(int* &H, int* &E, int &S, int &F);
		int* sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty);
		void checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab, int it);
		//void checkSequence(int8_t *db, vector<int8_t>& proteinTab, int it, int *E, int *scoreMatrix, int *F);
		void sequenceWithHighScore(int* res);
		
		int const& getMatrixBl(int l, int c);
		int* const getScoreMax();
		int* const getOffsetMax();
};
