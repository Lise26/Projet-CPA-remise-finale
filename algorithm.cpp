#include "algorithm.h"
using namespace std;

void algorithm::substituteMatrix(ifstream& matrixFile){

	for (int i = 0; i<28; i++){				//fill new blosum matrix with zeros
		for (int j =0; j<28; j++){
			matrixBl[i][j] = 0;
		}
	}
	
	map<string,int> dicoNumbers = {{"A",1},{"B",2},{"C",3},{"D",4},{"E",5},{"F",6},{"G",7},{"H",8},{"I",9},{"J",27},{"K",10},{"L",11},{"M",12},{"N",13},{"O",26},{"P",14},{"Q",15},{"R",16},{"S",17},{"T",18},{"U",24},{"V",19},{"W",20},{"X",21},{"Y",22},{"Z",23},{"*",25}};
	
	for (int i=0; i < 6; i++){				//select the 6 first lines of blosum file
		getline(matrixFile,line);
	}
	
	matrixFile.ignore();					//pass these 6 lines
	
	for (int i=0; i < 24; i++){				//put the keys into a vector
		matrixFile >> key;
		keys.push_back(key);
	}
	
	for (int i=0; i < 24; i++){ 			//fill the new blosum matrix with the values of the blosum matrix file
		matrixFile >> garbage;				//pass the first element
		for (int j=0; j < 24; j++){
			matrixFile >> data;				//extract data from blosum matrix file
			matrixBl[dicoNumbers[keys[i]]][dicoNumbers[keys[j]]] = data;  //fill new blosum matrix with right values
		}
	}
}

int* algorithm::sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, int &gapOpenPenalty, int &gapExtensionPenalty) {
	
	sizeQuery = sizeQueryProtein;
	
	numberSequence = tableauOffset.size()-1;  //last offset doesn't contain any sequence
	
	seqMax = new int[numberSequence];  //table with max score of each sequence
	
	Q = gapOpenPenalty + gapExtensionPenalty;
	R = gapExtensionPenalty;
	
	it = 0;
	
	while(it < numberSequence){ 
		 
		int offset = tableauOffset[it];  //adress of sequence in sequenceFile
		max = 0;
	
		scoreMatrix = new int[2*(sizeQuery+1)];  //matrixes with 2 lines and (sizeQuery+1) columns
		E = new int [2*(sizeQuery+1)];
		F = new int [2*(sizeQuery+1)];
			
		checkSequence(sequenceFile.seekg(offset), proteinTab, it);
		it++;
	}
	
	return seqMax;  //returns a table with maximum score of each sequence
}

void algorithm::checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab, int it){    //algorithm
	
	for(int m=0; m<2; m++) {
		for (int j = 0; j < sizeQuery+1; j++) {
			E[(m*(sizeQuery+1))] = 0;
			F[j] = 0;
			scoreMatrix[m*(sizeQuery+1)]=0;  //initialize first column of matrix
			scoreMatrix[j] = 0;  //initialize first line of matrix
		}
	}
	
	int m = 1;	
	while(sequenceFile.get(letter) and int(letter)!=0){ 		
			
		for (int j = 1; j < sizeQuery+1; j++) {  //algorithm
				
				if (j>0){
					E[(m*(sizeQuery+1))+j] = std::max(scoreMatrix[(m*(sizeQuery+1))+(j-1)]-Q, E[(m*(sizeQuery+1))+(j-1)]-R);
				}
				
				if (m>0){
					F[(m*(sizeQuery+1))+j] = std::max(scoreMatrix[((m-1)*(sizeQuery+1))+j]-Q, F[((m-1)*(sizeQuery+1))+j]-R);
				}
				
				if (m>0 and j>0){
					scoreMatrix[(m*(sizeQuery+1))+j]= std::max(scoreMatrix[((m-1)*(sizeQuery+1))+(j-1)]+matrixBl[int(letter)][proteinTab[j-1]], std::max(E[(m*(sizeQuery+1))+j], std::max(F[(m*(sizeQuery+1))+j],0)));
				}
				
				max = std::max(max, scoreMatrix[(m*(sizeQuery+1))+j]);  //keep the scoreMatrix maximum
		}
		
		for(int j=0; j < sizeQuery+1; j++) {
			scoreMatrix[j] = scoreMatrix[(sizeQuery+1)+j];  //we replace the first lines by the second ones so that we only work with two lines
			E[j] = E[(sizeQuery+1)+j];
			F[j] = F[(sizeQuery+1)+j];
		}	
	}
	
	delete[] scoreMatrix;
	delete[] E;
	delete[] F;
	seqMax[it] = max;  //maximum of the sequence
}

void algorithm::sequenceWithHighScore(int* res) {	//Order the scores and their offset
													//res = table of maximum score of each sequence
	int offsetMax[numberSequence];
	for(int i=0; i < numberSequence; i++) {
		offsetMax[i] = i;
	}
	
	for (int i = 0; i < numberSequence; i++){
		for(int j = i + 1; j < numberSequence; j++){
			if(res[i] < res[j]){
				int temp  = res[i];
				res[i] = res[j];
				res[j] = temp;
				int temp2 = offsetMax[i];  //also order offsetTable to keep a correspondance between offsetTable and table of maximums of each sequence 
				offsetMax[i] = offsetMax[j];
				offsetMax[j] = temp2;
			}
		}
	}
	
	for(int i=0; i<50; i++) {
		scoreMax[i] = res[i];  //take the 50 better scores
	}
	
	for(int i = 0; i<50; i++){
		offMax[i] = offsetMax[i];	//take the 50 adresses of sequences with high scores
	}
	
	delete[] seqMax;
	
}


//GETTERS

int const& algorithm::getMatrixBl(int l, int c){
	return matrixBl[l][c];
}
int* const algorithm::getScoreMax(){
	return scoreMax;
}
int* const algorithm::getOffsetMax(){
	return offMax;
}

