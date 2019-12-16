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


int* algorithm::sequenceMatch(ifstream &sequenceFile, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty) {
//int algorithm::sequenceMatch(int8_t *db, vector<int> &tableauOffset, int &sizeQueryProtein, vector<int8_t> &proteinTab, vector<int> &sequenceSize, int &gapOpenPenalty, int &gapExtensionPenalty) {	
	
	sizeQuery = sizeQueryProtein;
	tabOffset = tableauOffset;
	
	numberSequence = tableauOffset.size()-1;
	
	seqMax = new int[numberSequence];
	
	Q = gapOpenPenalty + gapExtensionPenalty;
	R = gapExtensionPenalty;
	
	it = 0;
	
	while(it < numberSequence){ 
		
		//cout << it << endl;
		 
		int offset = tableauOffset[it];
		//cout << offset << endl;
		max = 0;
		int size = sequenceSize[it];
		scoreMatrix = new int[(size+1)*(sizeQuery+1)];
		E = new int [(size+1)*(sizeQuery+1)];
		F = new int [(size+1)*(sizeQuery+1)];
			
		checkSequence(sequenceFile.seekg(offset), proteinTab, it); 
		it++;
	}
	
	return seqMax;
}

void algorithm::checkSequence(istream& sequenceFile, vector<int8_t>& proteinTab, int it){ 
	/*
	chercher dans l offset table l'indice de début de sequence de la séquence it
	debutSequence = tabOffset[it]
	
	
	taille_sequence = ce que tu veux
	for (int i = 0; i < taille_sequence; i++){
		for (int j = 0; i < Querysize ; j++){
			
			proteinTab[i] --> chaque lettre de proteinTab 
			
			db[debutSequence + j] //--> chaque lettre de ta sequence
			
		}
	}
	*/
	int i = 0;
	while(sequenceFile.get(letter) and int(letter)!=0){ 	
		
		for (int j = 0; j < sizeQuery+1; j++) {
			if (j==0){
				E[(i*sizeQuery)+j] = 0;
			}
			//E[(i*sizeQuery)] = 0;
			//F[j] = 0;
			//scoreMatrix[0]=0;
			
			else if (j>0){
				E[(i*(sizeQuery+1))+j] = std::max(scoreMatrix[(i*(sizeQuery+1))+(j-1)]-Q, E[(i*(sizeQuery+1))+(j-1)]-R);
			}

			if (i==0){
				F[(i*sizeQuery)+j] = 0;
			}
			
			else if (i>0){
				F[(i*(sizeQuery+1))+j] = std::max(scoreMatrix[((i-1)*(sizeQuery+1))+j]-Q, F[((i-1)*(sizeQuery+1))+j]-R);
			}

			if (i==0 or j==0){
				scoreMatrix[(i*sizeQuery)+j]=0;
			}
			
			else if (i>0 and j>0){
				scoreMatrix[(i*(sizeQuery+1))+j]= std::max(scoreMatrix[((i-1)*(sizeQuery+1))+(j-1)]+matrixBl[int(letter)][proteinTab[j]], std::max(E[(i*(sizeQuery+1))+j], std::max(F[(i*(sizeQuery+1))+j],0)));
			}
			
			max = std::max(max, scoreMatrix[(i*(sizeQuery+1))+j]);
		
		}
		
		i++;
	}
	delete[] scoreMatrix;
	delete[] E;
	delete[] F;
	seqMax[it] = max;
}

void algorithm::sequenceWithHighScore(int* res) {	//Order the scores and their offset
													//res = table of maximum scores of each sequence
	
	int offsetMax[numberSequence];
	
	for (int i = 0; i < numberSequence; i++){	
		for(int j = i + 1; j < numberSequence; j++){
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
	
	for(int i=0; i<50; i++) {
		scoreMax[i] = res[i];
	}
	
	for(int i = 0; i<50; i++){
		offMax[i] = offsetMax[i];
		cout << offMax[0] << endl;	
	}
	
}


//GETTERS AND SETTERS

int const& algorithm::getMatrixBl(int l, int c){
	return matrixBl[l][c];
}
int* const algorithm::getScoreMax(){
	return scoreMax;
}
int* const algorithm::getOffsetMax(){
	return offMax;
}

