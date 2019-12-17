#include "indeX.h"

inline void indeX::littleBigEndian (int &x) {		//Change the endianness of the byte (big to little)
	x = ((x >> 24) & 0xffL) | ((x >> 8) & 0xff00L) | ((x << 8) & 0xff0000L) | ((x << 24) & 0xff000000L);
}

void indeX::readFile(ifstream& file, int& value, int multiple, int type){    	//Read the .pin file
	if(type == 0)								//type = 0 : same as value, 1 : int, 2 : char
		file.read ((char *)&value, multiple*sizeof(value));
	else if(type == 1)
		file.read ((char *)&value, multiple*sizeof(int));
	else if(type == 2)
		file.read ((char *)&value, multiple*sizeof(char));
	littleBigEndian(value);	
}

int indeX::indexReader(ifstream& indexFile){
	
	readFile(indexFile, version, 1, 0);	//Version of the database
	
	readFile(indexFile, type, 1, 0);	//Type of the database : 0-DNA, 1-Protein
	
	readFile(indexFile, lenTitle, 1, 0);	//Length of the title string
		
	char titleC[lenTitle];			//Title of the database
	indexFile.read ((char *)&titleC, lenTitle*sizeof(char));
	for(int i = 0; i < lenTitle; i++){
		title.push_back(titleC[i]);
	}
	
	readFile(indexFile, lenTime, 1, 0);	//Length of the timestamp string
		
	char tstamp[lenTime];			//Timestamp
	indexFile.read ((char *)&tstamp, lenTime*sizeof(char));
	for(int i = 0; i < lenTime; i++){
		time.push_back(tstamp[i]);
	}
	
	readFile(indexFile, nbSeq, 1, 0);	//Number of sequences in the database
		
	indexFile.read ((char *)&residu, sizeof(residu));	//Total number of residues in the database
	
	readFile(indexFile, lenMax, 1, 0);	//Length of the longest sequence in the database
		
	int headerOff[nbSeq+1];			//Offsets into the sequence’s header file
	for(int i=0; i < (nbSeq+1); i++){
		readFile(indexFile, headerOff[i], 1, 1);
		headOffset.push_back(headerOff[i]);
	}
	
	int seqOff[nbSeq+1];			//Offsets into the sequence’s residue file
	for(int i=0; i < (nbSeq+1); i++){
		readFile(indexFile, seqOff[i], 1, 1);
		seqOffset.push_back(seqOff[i]);
	}

	return 0;
}

//GETTERS

int const& indeX::getVersion() {
	return version;
}

int const& indeX::getLenTitle() {
	return lenTitle;
}

int const& indeX::getLenTime() {
	return lenTime;
}

int const& indeX::getNbSeq() {
	return nbSeq;
}

int64_t const& indeX::getResidu() {
	return residu;
}

int const& indeX::getLenMax() {
	return lenMax;
}

vector<int> const& indeX::getHeaderOffset() {
	return headOffset;
}

vector<char> const& indeX::getTitle() {
	return title;
}

vector<char> const& indeX::getTime() {
	return time;
}

vector<int> const& indeX::getSeqOffset() {
	return seqOffset;
}
