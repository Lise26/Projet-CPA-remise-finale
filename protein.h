#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
using namespace std;

class protein {
	string protLine;
	char protLetter;
	int size1 = 1;
	int* size = &size1;
	
	vector<char> proteinTab;
	vector<char> *proteinTable = &proteinTab;
	
	public :
		int fillProteinTable(ifstream& proteinFile);
		vector<char>* getProteinTable();
		int* getProteinTableSize();
		void setProteinTableSize(int s);
};
