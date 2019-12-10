#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class matrixInit {
	
	int matrixBl[28][28]; 		//Ordered matrix containing the values from the matrix file
	
	public:
		void substiuteMatrix(ifstream& matrixFile);
		int getMatrixBl(int l, int c);
};
