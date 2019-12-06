#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "conversion.h"

class headerSearch {
	
	conversion conv;
	
	public :
		void header_name(ifstream& headerFile, int indice, vector<int> headerOffset, vector<char> *name, int *size);	
};
	
