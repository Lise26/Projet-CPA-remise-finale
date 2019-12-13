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
		void header_name(ifstream& headerFile, vector<int> offMax, vector<int> headerOffset);
		void charToString(string& s, vector<char> tab, int size);
		int const& getSize();
		vector<char> const& getName();
		string const& getNames(int i);	
};
	
