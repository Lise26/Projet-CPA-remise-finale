#include "mapInit.h"



void mapInit::substiuteMatrix(unordered_map<string,int>& matrixMap, ifstream& matrixFile){
	
	string line, key, garbage;
	
	vector<string> keys;
	
	for (int i=0; i < 6; i++){		//Pass the 6 first lines
		getline(matrixFile,line);
	}
	
	matrixFile.ignore();
	
	for (int i=0; i < 24; i++){		//init the keys into the vector
		matrixFile >> key;
		keys.push_back(key);
	}
	
	int data;
	
	for (int i=0; i < 24; i++){ 	//init the values into the map
		matrixFile >> garbage;		//Pass the 1st elem
		for (int j=0; j < 24; j++){
			matrixFile >> data;
			key = keys[i]+keys[j];
			matrixMap.insert({key,data});
		}
	}
	
	
}
