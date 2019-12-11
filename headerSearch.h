#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class headerSearch {
	
	public :
		void header_name(ifstream& headerFile, int indice, vector<int> headerOffset, vector<char> *name, int *size);
		string decToHex(int decimal);
		int hexToDecimal(string hex_value);	
};
	
