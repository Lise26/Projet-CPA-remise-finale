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

int algorithm::init(int* &H, int* &F, int &S) {
	for (int i = 0; i < sizeQuery; i++) {
		H[i] = 0;
		E[i] = 0;
		S = 0;
	}
	return 0;
}

int* algorithm::sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty) {
	
	sizeQuery = sizeQueryProtein;
	
	int numberSequence = tableauOffset.size();
	
	seqMax = new int[numberSequence];
	H = new int[sizeQuery];
	E = new int[sizeQuery];
	N = new int[sizeQuery];
	for (int i = 0; i < sizeQuery; i++) {
		N[i] = 0;
	}
	
	Q = gapOpenPenalty + gapExtensionPenalty;
	R = gapExtensionPenalty;
	
	it = 0;

	while(!sequenceFile.eof() and it < numberSequence){
		
		int offset = tableauOffset[it];
		
		init(H, E, S);
		indiceLetter = 0;	
			
		checkSequence(sequenceFile.seekg(offset), proteinTab);
		it++;
	}
	
	delete[] H;
	delete[] E;
	
	return seqMax;
}

void algorithm::checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab){ 
	
	while(sequenceFile.get(letter) and int(letter)!=0){    	
		
		for (int i = 0; i < sizeQuery; i++) {
			
			H[i] = N[i]+ matrixBl[int(letter)][proteinTab[i]];
			H[i] = std::max(H[i], F);
			H[i] = std::max(H[i], E[i]);
			H[i] = std::max(H[i], 0);
			S = std::max(S, H[i]);
			F = F - R;
			E[i] = E[i] - R;
			N[i] = H[i];
			H[i] = H[i] - Q;
			E[i] = std::max(H[i], E[i]);
			F = std::max(H[i], F);
		}
		indiceLetter++; 
	}
	
	seqMax[it] = S;
	 
}

int* const& algorithm::sequenceWithHighScore() {
	
	return seqWithHighScore;
}


//GETTERS AND SETTERS

int const& algorithm::getMatrixBl(int l, int c){
	return matrixBl[l][c];
}
