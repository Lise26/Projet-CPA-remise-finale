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
	
	int it;
	
	int indiceLetter;
	char letter;
	
	int *seqMax;
	
	int *H;
	int *E;
	int *N;
	int F = 0;
	int Q;
	int R;
	int S = 0;
	
	int* seqWithHighScore;
	
	//int blossum = matrix.getMatrixBl();
	
	public :
		void substiuteMatrix(ifstream& matrixFile);
		int init(int* &H, int* &E, int &S);
		int* sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty);
		void checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab);
		int* const& sequenceWithHighScore();
		
		int const& getMatrixBl(int l, int c);
};
