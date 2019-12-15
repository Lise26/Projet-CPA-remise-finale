#include "algorithm.h"
using namespace std;

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

int algorithm::init(int* &H, int* &E, int &S, int &F) {
	for (int i = 0; i < sizeQuery; i++) {
		H[i] = 0;
		F = 0;
		E[i] = 0;
		S = 0;
	}
	return 0;
}

int* algorithm::sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty) {
	
	sizeQuery = sizeQueryProtein;
	tabOffset = tableauOffset;
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
		
		init(H, E, S, F);
		indiceLetter = 0;	
		
		
		
		if (it == 2958)	
			checkSequence(sequenceFile.seekg(offset), proteinTab);
		//if (left(names[it],9) == "sp|P00533"){
		//	cout << names[it] << seqMax[it] << endl;
		//}
		it++;
	
	}
	delete[] H;
	delete[] E;
	
	return seqMax;
}

void algorithm::checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab){ 
	int compteur = 0;
	while(sequenceFile.get(letter) and int(letter)!=0){  
		compteur ++;  	
		
		for (int i = 0; i < sizeQuery; i++) {
			//cout << N[i] << endl;
			
			H[i] = H[i]+ matrixBl[int(letter)][proteinTab[i]];
			H[i] = max(H[i], F);
			H[i] = max(H[i], E[i]);
			H[i] = max(H[i], 0);
			S = max(S, H[i]);
			F = F - R;
			E[i] = E[i] - R;
			N[i] = H[i];
			H[i] = H[i] - Q;
			E[i] = max(H[i], E[i]);
			F = max(H[i], F);
			
		}
		indiceLetter++; 
	}
	
	seqMax[it] = S;
	cout << "Max : " << S << endl;
	cout << "Compteur : " << compteur << endl;
	cout << "query : " << sizeQuery << endl;
}

void algorithm::sequenceWithHighScore(int* res) {	//Order the scores and their offset
													//res = table of maximum scores of each sequence
	for(int i = 0; i < tabOffset.size(); i++){
		offsetMax.push_back(i);
	}
	for (int i = 0; i < tabOffset.size(); i++){	
		for(int j = i + 1; j < tabOffset.size(); j++){
			if(res[i] < res[j]){
				int temp  = res[i];
				res[i] = res[j];
				res[j] = temp;
				int temp2 = offsetMax[i];
				offsetMax[i] = offsetMax[j];
				offsetMax[j] = temp2;
			}
		}
	}
	
	for(int i=0; i<500; i++) {
		scoreMax.push_back(res[i]);
	}
	
}


//GETTERS AND SETTERS

int const& algorithm::getMatrixBl(int l, int c){
	return matrixBl[l][c];
}
vector<int> const& algorithm::getScoreMax(){
	return scoreMax;
}
vector<int> const& algorithm::getOffsetMax(){
	for(int i = 0; i<500; i++){
		offMax.push_back(offsetMax[i]);		
	}
	return offMax;
}

