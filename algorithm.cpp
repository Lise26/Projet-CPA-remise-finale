#include "algorithm.h"
using namespace std;

void algorithm::substituteMatrix(ifstream& matrixFile){		//this function is only used if the blosum matrix is given as parameter by the user
															//it will take the matrix given and reorganize its terms in an order that suit our needs
															//wich is the order of the dictionnary below
	
	for (int i = 0; i<28; i++){								//fill new matrix with zeros
		for (int j =0; j<28; j++){
			matrixBl[i][j] = 0;
		}
	}
	
	map<string,int> dicoNumbers = {{"A",1},{"B",2},{"C",3},{"D",4},{"E",5},{"F",6},{"G",7},{"H",8},{"I",9},{"J",27},{"K",10},{"L",11},{"M",12},{"N",13},{"O",26},{"P",14},{"Q",15},{"R",16},{"S",17},{"T",18},{"U",24},{"V",19},{"W",20},{"X",21},{"Y",22},{"Z",23},{"*",25}};
	
	for (int i=0; i < 6; i++){								//take the 6 first lines of blosum file
		getline(matrixFile,line);
	}
	
	matrixFile.ignore();									//change the way the file is read
	
	for (int i=0; i < 24; i++){								//put the keys into a vector
		matrixFile >> key;
		keys.push_back(key);
	}
	
	for (int i=0; i < 24; i++){ 							//fill the new blosum matrix with the values of the blosum matrix file
		matrixFile >> garbage;								//pass the first element
		for (int j=0; j < 24; j++){
			matrixFile >> data;								//extract data from blosum matrix file
			matrixBl[dicoNumbers[keys[i]]][dicoNumbers[keys[j]]] = data;  //fill new blosum matrix with right values
		}
	}
}

int* algorithm::researchScore(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, int &gapOpenPenalty, int &gapExtensionPenalty) {
															//this function is the starting point of the Smith-Waterman algorithm
												
	sizeQuery = sizeQueryProtein;
	
	numberSequence = tableauOffset.size()-1;				//last offset doesn't contain any sequence
	
	seqMax = new int[numberSequence];						//table with max score of each sequence
	
	Q = gapOpenPenalty + gapExtensionPenalty;
	R = gapExtensionPenalty;
	
	it = 0;
	
	while(it < numberSequence){ 
		 
		int offset = tableauOffset[it];						//offset of the it sequence in sequenceFile
		max = 0;
	
		scoreMatrix = new int[2*(sizeQuery+1)];				//these are the matrix of the algorithm (one with the score of the sequence and two that allow to fill the first one)
		E = new int [2*(sizeQuery+1)];						//they have (sizeQuery+1) columns and only 2 lines, because there is no need to keep the whole matrixes in memory :
		F = new int [2*(sizeQuery+1)];						//to fill a line of the matrixes, only the one above is needed
			
		algo(sequenceFile.seekg(offset), proteinTab, it); 
		it++;
	}
	
	return seqMax;											//returns a table with maximum score of each sequence
}

void algorithm::algo(istream& sequenceFile, vector<int8_t>& proteinTab, int it){ 		//implementation of the algorithm
	
	for(int m=0; m<2; m++) {
		for (int j = 0; j < sizeQuery+1; j++) {				
			E[(m*(sizeQuery+1))] = 0;						//initialise the first column of E
			F[j] = 0;										//initialise the first line of F
			scoreMatrix[m*(sizeQuery+1)]=0;					//initialize the first column of scoreMatrix
			scoreMatrix[j] = 0;								//initialize the first line of matrix
		}
	}
	
	int m = 1;	
	while(sequenceFile.get(letter) and int(letter)!=0){ 		
			
		for (int j = 1; j < sizeQuery+1; j++) {				//fill scoreMatrix, E and F with the values planned by the algorithm
			E[(m*(sizeQuery+1))+j] = std::max(scoreMatrix[(m*(sizeQuery+1))+(j-1)]-Q, E[(m*(sizeQuery+1))+(j-1)]-R);
			F[(m*(sizeQuery+1))+j] = std::max(scoreMatrix[((m-1)*(sizeQuery+1))+j]-Q, F[((m-1)*(sizeQuery+1))+j]-R);
			scoreMatrix[(m*(sizeQuery+1))+j]= std::max(scoreMatrix[((m-1)*(sizeQuery+1))+(j-1)]+matrixBl[int(letter)][proteinTab[j-1]], std::max(E[(m*(sizeQuery+1))+j], std::max(F[(m*(sizeQuery+1))+j],0)));
			max = std::max(max, scoreMatrix[(m*(sizeQuery+1))+j]);		//update the scoreMatrix maximum if needed
		}
		
		for(int j=0; j < sizeQuery+1; j++) {				//replace the first line of the matrixes by the second one to store line j in order to fill line j+1
			scoreMatrix[j] = scoreMatrix[(sizeQuery+1)+j];
			E[j] = E[(sizeQuery+1)+j];
			F[j] = F[(sizeQuery+1)+j];
		}	
	}
	
	delete[] scoreMatrix;
	delete[] E;
	delete[] F;
	seqMax[it] = max;										//the maximum score of the sequence is added to the table that contains maximums of all the sequences maximums
}

void algorithm::sequenceWithHighScore(int* res) {			//Order the scores and their offset (in ascending order)
															//res = table that contains all the sequences maximums
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
				int temp2 = offsetMax[i];					//also order offsetTable to keep a correspondance between the offset and its sequence
				offsetMax[i] = offsetMax[j];
				offsetMax[j] = temp2;
			}
		}
	}
	
	for(int i=0; i<50; i++) {								//take the 50 higher scores
		scoreMax[i] = res[i];
	}
	
	for(int i = 0; i<50; i++){								//and the 50 offset of sequences with the higher scores
		offMax[i] = offsetMax[i];		
	}
	
	delete[] seqMax;
	
}


//GETTERS

int const& algorithm::getMatrixBl(int l, int c){
	cout << matrixBl[1][1] << endl;
	return matrixBl[l][c];
}

int* const& algorithm::getScoreMax(){
	return scoreMax;
}
int* const& algorithm::getOffsetMax(){
	return offMax;
}

