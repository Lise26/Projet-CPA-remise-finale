#include "protein.h"

int protein::fillProteinTable(ifstream& proteinFile) {
	
	map<char,int8_t> dicoLetters = {{' ',0},{'A',1},{'B',2},{'C',3},{'D',4},{'E',5},{'F',6},{'G',7},{'H',8},{'I',9},{'J',27},{'K',10},{'L',11},{'M',12},{'N',13},{'O',26},{'P',14},{'Q',15},{'R',16},{'S',17},{'T',18},{'U',24},{'V',19},{'W',20},{'X',21},{'Y',22},{'Z',23},{'*',25}};
	
	getline(proteinFile,protLine);								//skip the first line of the proteinFile which is the title of the protein
	int counter = 0; 

	while(proteinFile >> protLetter and !proteinFile.eof()){  	//first condition puts each character of the proteinFile, one by one, into a variable protLetter		
																//second condition stops the loop when the end of the proteinFile is reached 
		proteinTable.push_back(dicoLetters[protLetter]);		//add each letter in a table
		counter++;					
	}
	
	setProteinTableSize(proteinTable.size());
	
	return 0;
}

//GETTERS AND SETTERS

vector<int8_t>const& protein::getProteinTable() {
	return proteinTable;
}

int const& protein::getProteinTableSize() {
	return size;
}

void protein::setProteinTableSize(int s) {
	size += s;
}
