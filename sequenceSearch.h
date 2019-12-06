#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;

#include "check.h"

class sequenceSearch {
    vector<char> proteinTable;
    char protLetter;
	int counter = 0;		
	string protLine;
	
	bool proteinFound = false;
	int indiceFINAL;
	int it = 0;
	int offset;
	
	check c;
  
  public:
    int sequenceMatch(ifstream &proteinFile, ifstream &sequenceFile, vector<int> *tableauOffset);
};
