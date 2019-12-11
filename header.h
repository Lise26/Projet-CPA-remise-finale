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
	int size=0;
	
	public :
		void header_name(ifstream& headerFile, int indice, vector<int> headerOffset);
		int getSize();
		vector<char> getName();	
};
	
