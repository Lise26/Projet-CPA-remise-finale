#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class mapInit {
	
	public:
		void substiuteMatrix(unordered_map<string,int>& matrixMap, ifstream& matrixFile);
};
