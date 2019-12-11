#include "sequence.h"

int sequence::sequenceSize(vector<int> *tableauOffset) {
	
	for (unsigned int i=1; i < (*tableauOffset).size(); i++) {
		int size = (*tableauOffset)[i] - (*tableauOffset)[i-1];
		(*sizeSequence).push_back(size);
	}
	(*sizeSequence).push_back(0);  									//comment récupérer la taille de la dernière séquence?
	
	
	return 0;
}

vector<int>* sequence::getSizeSequence() {
	return sizeSequence;
}
