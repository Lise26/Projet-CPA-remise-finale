#include <fstream>
#include <iostream>
#include <vector> 
#include <string>
#include <stdio.h>
using namespace std;

#include "indeX.h"
#include "header.h"
#include "sequence.h"

class database {
	indeX ind;
	header head;
	sequence seq;
	
	conversion conv;
	
	public :
		int attributes(ofstream &result, vector<char> title, vector<char> time, int lenTitle, int lenTime, int64_t residu, int numbSeq, int lenMax);

};
