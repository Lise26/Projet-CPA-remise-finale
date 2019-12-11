#include "indeX.h"

inline void indeX::littleBigEndian (int &x) {
	x = ((x >> 24) & 0xffL) | ((x >> 8) & 0xff00L) | ((x << 8) & 0xff0000L) | ((x << 24) & 0xff000000L);
}

void indeX::readFile(ifstream& file, int& value, int multiple, int type){    //type = 0 : same as value, 1 : int, 2 : char
	if(type == 0)
		file.read ((char *)&value, multiple*sizeof(value));
	else if(type == 1)
		file.read ((char *)&value, multiple*sizeof(int));
	else if(type == 2)
		file.read ((char *)&value, multiple*sizeof(char));
	littleBigEndian(value);	
}

int indeX::indexReader(ifstream& indexFile){
	
	readFile(indexFile, version, 1, 0);
	
	readFile(indexFile, type, 1, 0);
	
	readFile(indexFile, lenTitle, 1, 0);
		
	char titleC[lenTitle];		
	indexFile.read ((char *)&titleC, lenTitle*sizeof(char));
	for(int i = 0; i < lenTitle; i++){
		title.push_back(titleC[i]);
	}
	
	readFile(indexFile, lenTime, 1, 0);
		
	char tstamp[lenTime];		
	indexFile.read ((char *)&tstamp, lenTime*sizeof(char));
	for(int i = 0; i < lenTime; i++){
		time.push_back(tstamp[i]);
	}
	
	readFile(indexFile, nbSeq, 1, 0);
		
	indexFile.read ((char *)&residu, sizeof(residu));
	
	readFile(indexFile, lenMax, 1, 0);	
		
	int headerOff[nbSeq+1];
	for(int i=0; i < (nbSeq+1); i++){
		readFile(indexFile, headerOff[i], 1, 1);
		headOffset.push_back(headerOff[i]);
	}
	
	int seqOff[nbSeq+1];
	for(int i=0; i < (nbSeq+1); i++){
		readFile(indexFile, seqOff[i], 1, 1);
		seqOffset.push_back(seqOff[i]);
	}

	return 0;
}

//GETTERS AND SETTERS

int indeX::getVersion() const {
	return version;
}

int indeX::getLenTitle() const {
	return lenTitle;
}

int indeX::getLenTime() const {
	return lenTime;
}

int indeX::getNbSeq() const {
	return nbSeq;
}

int64_t indeX::getResidu() const {
	return residu;
}

int indeX::getLenMax() const {
	return lenMax;
}

vector<int> indeX::getHeaderOffset() const {
	return headOffset;
}

vector<char> indeX::getTitle() const {
	return title;
}

vector<char> indeX::getTime() const {
	return time;
}

vector<int> indeX::getSeqOffset() const {
	return seqOffset;
}
