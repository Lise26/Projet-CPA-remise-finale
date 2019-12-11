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
	vector<char> protTab;
	
	vector<int> sizeSequence;
	
	int max = 0;
	int *seqMaxAndOffset;
	int *scoreMatrix;

	int Q = 0;
	int R = 0;
	int *E;
	int *F;
	
	//int blossum = matrix.getMatrixBl();
	
	public :
		void substiuteMatrix(ifstream& matrixFile);
		int* sequenceMatch(ifstream &sequenceFile, vector<int> tableauOffset, int sizeQueryProtein, vector<char> protTab, vector<int> sequenceSize, int gapOpenPenalty, int gapExtensionPenalty);
		void checkSequence(istream& sequenceFile, int it);
		int fillScoreMatrixQuery(vector<vector<int>>* scoreMatrix, char protLetter, int counter);
		int fillScoreMatrixSequence(vector<vector<int>>* scoreMatrix, char letter, int count);
		int fillScoreMatrix(int i, int j, int letterSeq, int letterQuer);
		int Matrix(vector<vector<int>>* scoreMatrix);
		
		int getMatrixBl(int l, int c);
};
