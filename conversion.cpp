#include "conversion.h"

string conversion::decToHex(int decimal){ 				//Convert from decimal to hexadecimal
	stringstream ss;
	ss << hex << decimal;
	string res ( ss.str() );
	return res;
}

int conversion::hexToDecimal(string hex_value){				//Convert from hexadecimal to decimal
	stringstream ss;
	ss << hex_value;
	int res;
	ss >> hex >> res ;
	return res;
}

void conversion::charToString(string& s, vector<char> tab, int size){		//Convert from vector<char> to string
	for(int i = 0; i < size; i++){
		s[i] = tab[i];
	}
}
