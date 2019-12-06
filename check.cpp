#include "check.h"

bool check::checkSequence(istream& sequenceFile, vector<char> proteinTable){    //search for a match between the query and the sequence file of the database
	
	char letter;
	int indiceLetter = 0;
	bool equal = true;
	
	map<int,string> dicoNumbers = {{0," "},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"F"},{7,"G"},{8,"H"},{9,"I"},{27,"J"},{10,"K"},{11,"L"},{12,"M"},{13,"N"},{26,"O"},{14,"P"},{15,"Q"},{16,"R"},{17,"S"},{18,"T"},{24,"U"},{19,"V"},{20,"W"},{21,"X"},{22,"Y"},{23,"Z"},{25,"*"}};

	while(sequenceFile.get(letter) and int(letter)!=0 and equal == true){    //we go trough the sequence file until we find the protein that matches the query
		
		if(dicoNumbers[int(letter)][0] != proteinTable[indiceLetter]){ 	 //as soon as one letter of the query is different from the sequence that we are reading in the sequence file, we go to the next sequence of the file
			equal=false;
	    }
	    indiceLetter++; 
	}

	return equal;
}
