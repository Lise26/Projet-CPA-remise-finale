#include "indexSearch.h"

inline void indexSearch::littleBigEndian (int &x) {
	x = ((x >> 24) & 0xffL) | ((x >> 8) & 0xff00L) | ((x << 8) & 0xff0000L) | ((x << 24) & 0xff000000L);
}

int indexSearch::indexReader(ifstream& indexFile, vector<int> *tableauOffset, vector<int> *headerOffset, int *nbSeqt, int *lmaxt, int64_t *residut, vector<char> *titlet, vector<char> *datet, int *sizet, int *sized){
	
	int type, len, lenT, nbSeq, lenMax = 0;
	int64_t residu = 0;
	
	indexFile.read ((char *)&version, sizeof(version));
	littleBigEndian(version);
		
	indexFile.read ((char *)&type, sizeof(type));
	littleBigEndian(type);
		
	indexFile.read ((char *)&len, sizeof(len));
	littleBigEndian(len);
	(*sizet) = len;
		
	char title[len];		
	indexFile.read ((char *)&title, len*sizeof(char));
	string s(len,0);
	for(int i = 0; i < len; i++){
		s[i] = title[i];
		(*titlet).push_back(title[i]);
	}
		
	indexFile.read ((char *)&lenT, sizeof(lenT));
	littleBigEndian(lenT);
		
	char tstamp[lenT];		
	indexFile.read ((char *)&tstamp, lenT*sizeof(char));
	string p(lenT,0);
	for(int i = 0; i < lenT; i++){
		p[i] = tstamp[i];
		(*sized) = i - 6;
		(*datet).push_back(tstamp[i]);
	}
		
	indexFile.read ((char *)&nbSeq, sizeof(nbSeq));
	littleBigEndian(nbSeq);
	(*nbSeqt) = nbSeq;
		
	indexFile.read ((char *)&residu, sizeof(residu));
	(*residut) = residu;
		
	indexFile.read ((char *)&lenMax, sizeof(lenMax));
	littleBigEndian(lenMax);
	(*lmaxt) = lenMax;
		
	int headerOff[nbSeq+1];
	for(int i=0; i < (nbSeq+1); i++){
		indexFile.read ((char *)&headerOff[i], sizeof(int));
		littleBigEndian(headerOff[i]);
		(*headerOffset).push_back(headerOff[i]);
	}
		
	int seqOff[nbSeq+1];
	for(int i=0; i < (nbSeq+1); i++){
		indexFile.read ((char *)&seqOff[i], sizeof(int));
		littleBigEndian(seqOff[i]);
		(*tableauOffset).push_back(seqOff[i]);
	}

	return 0;
}

int indexSearch::getHeaderOffset(){
	return version;
}

//int* const& getseqOff() {	
	//return seqOff[nbSeq+1];
//}
