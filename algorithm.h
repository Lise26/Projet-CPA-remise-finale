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
	
	int sizeQuery = 0;
	int numberSequence;
	int it;
	
	char letter;
	
	//Ordered matrix containing the blosum 62 matrix
	int matrixBl[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},				
		{0, 4, -2, 0, -2, -1, -2, 0, -2, -1, -1, -1, -1, -2, -1, -1, -1, 1, 0, 0, -3, 0, -2, -1, 0, -4, 0, 0},
		{0, -2, 4, -3, 4, 1, -3, -1, 0, -3, 0, -4, -3, 3, -2, 0, -1, 0, -1, -3, -4, -1, -3, 1, 0, -4, 0, 0},
		{0, 0, -3, 9, -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2, -2, -3, 0, -4, 0, 0},
		{0, -2, 4, -3, 6, 2, -3, -1, -1, -3, -1, -4, -3, 1, -1, 0, -2, 0, -1, -3, -4, -1, -3, 1, 0, -4, 0, 0},
		{0, -1, 1, -4, 2, 5, -3, -2, 0, -3, 1, -3, -2, 0, -1, 2, 0, 0, -1, -2, -3, -1, -2, 4, 0, -4, 0, 0},
		{0, -2, -3, -2, -3, -3, 6, -3, -1, 0, -3, 0, 0, -3, -4, -3, -3, -2, -2, -1, 1, -1, 3, -3, 0, -4, 0, 0},
		{0, 0, -1, -3, -1, -2, -3, 6, -2, -4, -2, -4, -3, 0, -2, -2, -2, 0, -2, -3, -2, -1, -3, -2, 0, -4, 0, 0},
		{0, -2, 0, -3, -1, 0, -1, -2, 8, -3, -1, -3, -2, 1, -2, 0, 0, -1, -2, -3, -2, -1, 2, 0, 0, -4, 0, 0},
		{0, -1, -3, -1, -3, -3, 0, -4, -3, 4, -3, 2, 1, -3, -3, -3, -3, -2, -1, 3, -3, -1, -1, -3, 0, -4, 0, 0},
		{0, -1, 0, -3, -1, 1, -3, -2, -1, -3, 5, -2, -1, 0, -1, 1, 2, 0, -1, -2, -3, -1, -2, 1, 0, -4, 0, 0},
		{0, -1, -4, -1, -4, -3, 0, -4, -3, 2, -2, 4, 2, -3, -3, -2, -2, -2, -1, 1, -2, -1, -1, -3, 0, -4, 0, 0},
		{0, -1, -3, -1, -3, -2, 0, -3, -2, 1, -1, 2, 5, -2, -2, 0, -1, -1, -1, 1, -1, -1, -1, -1, 0, -4, 0, 0},
		{0, -2, 3, -3, 1, 0, -3, 0, 1, -3, 0, -3, -2, 6, -2, 0, 0, 1, 0, -3, -4, -1, -2, 0, 0, -4, 0, 0},
		{0, -1, -2, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2, 7, -1, -2, -1, -1, -2, -4, -2, -3, -1, 0, -4, 0, 0},
		{0, -1, 0, -3, 0, 2, -3, -2, 0, -3, 1, -2, 0, 0, -1, 5, 1, 0, -1, -2, -2, -1, -1, 3, 0, -4, 0, 0},
		{0, -1, -1, -3, -2, 0, -3, -2, 0, -3, 2, -2, -1, 0, -2, 1, 5, -1, -1, -3, -3, -1, -2, 0, 0, -4, 0, 0},
		{0, 1, 0, -1, 0, 0, -2, 0, -1, -2, 0, -2, -1, 1, -1, 0, -1, 4, 1, -2, -3, 0, -2, 0, 0, -4, 0, 0},
		{0, 0, -1, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1, 0, -1, -1, -1, 1, 5, 0, -2, 0, -2, -1, 0, -4, 0, 0},
		{0, 0, -3, -1, -3, -2, -1, -3, -3, 3, -2, 1, 1, -3, -2, -2, -3, -2, 0, 4, -3, -1, -1, -2, 0, -4, 0, 0},
		{0, -3, -4, -2, -4, -3, 1, -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11, -2, 2, -3, 0, -4, 0, 0},
		{0, 0, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1, 0, 0, -1, -2, -1, -1, -1, 0, -4, 0, 0},
		{0, -2, -3, -2, -3, -2, 3, -3, 2, -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1, 2, -1, 7, -2, 0, -4, 0, 0},
		{0, -1, 1, -3, 1, 4, -3, -2, 0, -3, 1, -3, -1, 0, -1, 3, 0, 0, -1, -2, -3, -1, -2, 4, 0, -4, 0, 0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 0, 1, 0, 0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	
	int *seqMax = 0;
	int max = 0;
	
	int *scoreMatrix = 0;
	int *E = 0;
	int *F = 0;
	int Q;
	int R;
	
	int scoreMax[50];
	int offMax[50];
	
	public :
		void substituteMatrix(ifstream& matrixFile);
		int init(int* &H, int* &E, int &S, int &F);
		int* researchScore(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, int &gapOpenPenalty, int &gapExtensionPenalty);
		void algo(istream& sequenceFile, vector<int8_t>& proteinTab, int it);
		void sequenceWithHighScore(int* res);
		
		int const& getMatrixBl(int l, int c);
		int* const getScoreMax();
		int* const getOffsetMax();
};
