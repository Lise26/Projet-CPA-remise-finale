#include "algorithm.h"

void algorithm::substiuteMatrix(ifstream& matrixFile){
	
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

int* algorithm::sequenceMatch(ifstream &sequenceFile, vector<int> tableauOffset, int sizeQueryProtein, vector<char> proteinTab, vector<int> sequenceSize, int gapOpenPenalty, int gapExtensionPenalty) {
	
	sizeQuery = sizeQueryProtein;
	protTab = proteinTab;
	
	sizeSequence = sequenceSize;
	
	int numberSequence = tableauOffset.size();
	
	seqMaxAndOffset = new int[numberSequence*2];
	
	Q = gapOpenPenalty + gapExtensionPenalty;
	R = gapExtensionPenalty;
	
	int it = 0;

	while(!sequenceFile.eof() and it < numberSequence){
		
		int offset = tableauOffset[it];
		cout << offset << endl;
		seqMaxAndOffset[it*2] = offset;
		
		max = 0;
						
		int size = sizeSequence[it];		
		scoreMatrix = new int[size*sizeQuery];
		E = new int[size*sizeQuery];
		F = new int[size*sizeQuery];
			
		checkSequence(sequenceFile.seekg(offset), it);
		it++;
	}
	
	delete[] scoreMatrix;
	delete[] E;
	delete[] F;
	
	return seqMaxAndOffset;
}

void algorithm::checkSequence(istream& sequenceFile, int it){ 

	int indiceLetter = 0;
	char letter;
	
	while(sequenceFile.get(letter) and int(letter)!=0){    	
		
		for (int i=0; i < sizeQuery; i++) {
			//cout << "sequence : " << int(letter) << " query : " << protTab[i] << endl;
			fillScoreMatrix(indiceLetter, i, int(letter), protTab[i]);   
		
			if (scoreMatrix[(indiceLetter*sizeQuery)+i] > max) {
				max = scoreMatrix[(indiceLetter*sizeQuery)+i];
			}
		}
		indiceLetter++; 
	}
	
	seqMaxAndOffset[(it*2)+1] = max;
	 
}

int algorithm::fillScoreMatrix(int i, int j, int letterSeq, int letterQuer) {

	if (j>0){
		E[(i*sizeQuery)+j] = std::max(scoreMatrix[(i*sizeQuery)+(j-1)]-Q, E[(i*sizeQuery)+(j-1)]-R);
	}
	else if (j==0){
		E[(i*sizeQuery)+j] = 0;
	}

	if (i>0){
		F[(i*sizeQuery)+j] = std::max(scoreMatrix[((i-1)*sizeQuery)+j]-Q, F[((i-1)*sizeQuery)+j]-R);
	}
	else if (i==0){
		F[(i*sizeQuery)+j] = 0;
	}

	if (i>0 and j>0){
		scoreMatrix[(i*sizeQuery)+j]= std::max(scoreMatrix[((i-1)*sizeQuery)+(j-1)]+matrixBl[letterSeq][letterQuer], std::max(E[(i*sizeQuery)+j], std::max(F[(i*sizeQuery)+j],0)));
	}
	else if (i==0 or j==0){
		scoreMatrix[(i*sizeQuery)+j]=0;
	}
	
	return 0;
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


//GETTERS AND SETTERS

int algorithm::getMatrixBl(int l, int c){
	return matrixBl[l][c];
}
