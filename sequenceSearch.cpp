#include "sequenceSearch.h"

int sequenceSearch::sequenceMatch(ifstream &proteinFile, ifstream &sequenceFile, vector<int> *tableauOffset) {
		
	getline(proteinFile,protLine);  									//skip the first line of the proteinFile which is the title of the protein
		
	while(proteinFile >> protLetter and !proteinFile.eof()){  			//first condition puts each character of the proteinFile, one by one, into a variable protLetter
																		//second condition : stop the loop when the end of the proteinFile is reached 
		proteinTable.push_back(protLetter);								//add each letter in a table
		counter++;					
	}

	while(!sequenceFile.eof() and proteinFound == false){
		offset = tableauOffset->at(it);									//directly go to the beginning of a sequence in the sequence File
		proteinFound = c.checkSequence(sequenceFile.seekg(offset), proteinTable);
		it++;
	}
	indiceFINAL = it-1;
	
	return indiceFINAL;
}
