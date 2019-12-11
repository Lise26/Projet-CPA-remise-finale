#include "matrixInit.h"

void matrixInit::substiuteMatrix(ifstream& matrixFile){
	
	string line, key, garbage;	
	vector<string> keys;
	int data;
	
	for (int i = 0; i<28; i++){		//fill new matrix with zeros
		for (int j =0; j<28; j++){
			matrixBl[i][j] = 0;
		}
	}
	
	map<string,int> dicoNumbers = {{"A",1},{"B",2},{"C",3},{"D",4},{"E",5},{"F",6},{"G",7},{"H",8},{"I",9},{"J",27},{"K",10},{"L",11},{"M",12},{"N",13},{"O",26},{"P",14},{"Q",15},{"R",16},{"S",17},{"T",18},{"U",24},{"V",19},{"W",20},{"X",21},{"Y",22},{"Z",23},{"*",25}};
	
	for (int i=0; i < 6; i++){		//Pass the 6 first lines
		getline(matrixFile,line);
	}
	
	matrixFile.ignore();
	
	for (int i=0; i < 24; i++){		//init the keys into the vector
		matrixFile >> key;
		keys.push_back(key);
	}
	
	for (int i=0; i < 24; i++){ 	//fill the new matrix with the values from the matrix file
		matrixFile >> garbage;		//Pass the 1st elem
		for (int j=0; j < 24; j++){
			matrixFile >> data;
			matrixBl[dicoNumbers[keys[i]]][dicoNumbers[keys[j]]] = data;
		}
	}
}

int matrixInit::getMatrixBl(int l, int c){		//Accessor of matrixBl

	return matrixBl[l][c];

}

