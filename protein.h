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
	
	vector<int8_t> proteinTable;
	
	public :
		int fillProteinTable(ifstream& proteinFile);
		int info(ofstream &result, char* name);
		vector<int8_t>const& getProteinTable();
		int const& getProteinTableSize();
		void setProteinTableSize(int s);
};
