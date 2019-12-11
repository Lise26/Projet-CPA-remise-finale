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
	int size = 0;
	
	vector<char> proteinTable;
	
	public :
		int fillProteinTable(ifstream& proteinFile);
		vector<char> getProteinTable();
		int getProteinTableSize();
		void setProteinTableSize(int s);
};
