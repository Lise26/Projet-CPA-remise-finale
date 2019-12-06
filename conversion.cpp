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
