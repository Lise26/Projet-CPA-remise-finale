#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "conversion.h"

class header {
	
	conversion conv; 
	
	vector<char> name;
	string names[50];
	int size=0;
	
	public :
		void header_name(ifstream& headerFile, int* offMax, vector<int> headerOffset);
		int info(ofstream &result, int *score);
		int const& getSize();
		vector<char> const& getName();
		string* const& getNames();	
};
	
