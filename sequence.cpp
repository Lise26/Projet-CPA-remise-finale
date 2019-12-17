#include "sequence.h"

int sequence::fillSequenceSize(vector<int> tableauOffset) {				//puts into a table the sizes of the protein of the sequence file in the database
	
	for (unsigned int i=1; i < tableauOffset.size(); i++) {			
		int size = tableauOffset[i] - tableauOffset[i-1];				//sizes are calculated from the offset table
		sizeSequence.push_back(size);
	}
	
	return 0;
}

//GETTER

vector<int> const& sequence::getSizeSequence() {
	return sizeSequence;
}
