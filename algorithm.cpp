#include "algorithm.h"

int algorithm::sequenceMatch(ifstream &proteinFile, ifstream &sequenceFile, vector<int>* tableauOffset) {
	
	prot.fillProteinTable(proteinFile);
	
	seq.sequenceSize(tableauOffset);
	vector<int>* sizeSequence = seq.getSizeSequence();
	
	int sizeTableauOffset = (*tableauOffset).size();
	int seqMaxAndOffset[sizeTableauOffset][2];
	
	int it = 0;

	while(!sequenceFile.eof() and it < sizeTableauOffset){
		
		offset = (*tableauOffset)[it];
		
		seqMaxAndOffset[it][0] = offset;
						
		int size = (*sizeSequence)[it];		
		int scoreMatrix[size][*sizeQuery];
		checkSequence(sequenceFile.seekg(offset), seqMaxAndOffset, it);
		it++;
	}
	
	return 0;
}

void algorithm::checkSequence(istream& sequenceFile, int seqMaxAndOffset[][2], int it){ //search for a match between the protein and a sequence

	int indiceLetter = 0;
	char letter;
	
	while(sequenceFile.get(letter) and int(letter)!=0){    		//we go trough the sequence file until we find the protein that matches the query
		
		for (int i=0; i < (*sizeQuery); i++) {
			//scoreMatrix[indiceLetter][i] = mat[int8_t(letter)][(*protTab)[indiceLetter]];
			
			//if (scoreMatrix[indiceLetter][i] > max) {
				//max = scoreMatrix[indiceLetter][i];
		}
		indiceLetter++; 
	}
	
	seqMaxAndOffset[it][1] = max;
	 
}

/*int algorithm::matrix(vector<vector<int>>* scoreMatrix) {

	cout << " ";
	for (unsigned int i=0; i < (*sizeSequence).size(); i++) {
		
		int scoreMatrix[*sizeQuery][(*sizeSequence)[i]];
		
		for (unsigned int s = 0; s<(*sizeSequence)[i]; s++) {
			cout << char(scoreMatrix[0][s]) << " " ;
		}
		cout << endl; 
		for(unsigned int q=1; q<(*sizeQuery); q++){
			cout << char(scoreMatrix[q][0]) << " " ;
			for(int s=1; s<(*sizeSequence)[i]; s++){
				cout << scoreMatrix[q][s] << " " ;
			}
			cout << endl;
		}	
	}
	return 0;
}*/
