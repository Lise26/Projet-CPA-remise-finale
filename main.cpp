#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <byteswap.h>
using namespace std;

#include "parameters.h"
#include "protein.h"
#include "database.h"
#include "algorithm.h"

int main(int argc, char **argv) {
	
	parameters verif;
	protein prot;
	database datab;
	indeX ind;
	sequence seq;
	header head;
	algorithm algo;

	verif.verifParameters(argc, argv);						//verification of the number of parameters given in input
	
	//Open files
	ifstream proteinFile(argv[1]);							//opening proteinFile				
	ifstream sequenceFile(verif.getNameSequence());			//opening sequenceFile				
	ifstream indexFile(verif.getNameIndex());           	//opening indexFile
	ifstream headerFile(verif.getNameHeader());				//opening headerFile
	ifstream matrixFile(verif.getNameMatrix());				//opening matrixFile	
	
	int gapOpenPenalty = verif.getGapOpenPenalty();
	int gapExtensionPenalty = verif.getGapExtensionPenalty();
	
	//Informations about the query
	prot.fillProteinTable(proteinFile);
	int sizeQueryProtein = prot.getProteinTableSize();
	vector<int8_t> proteinTab = prot.getProteinTable();
	
	//Informations about the index
	ind.indexReader(indexFile);
	vector<int> seqOffset = ind.getSeqOffset();
	vector<int> headOffset = ind.getHeaderOffset();
	vector<char> title = ind.getTitle();
	vector<char> time = ind.getTime();	
	int lenTitle = ind.getLenTitle();
	int lenTime = ind.getLenTime();
	int64_t residu = ind.getResidu();
	int numbSeq = ind.getNbSeq();
	int lenMax = ind.getLenMax();
	
	//Informations about the sequence
	seq.fillSequenceSize(ind.getSeqOffset());
	vector<int> sequenceSize = seq.getSizeSequence();
	
	//Init the substitution matrix
	algo.substituteMatrix(matrixFile);	
	
	if(sequenceFile.is_open()) {
		int* res = algo.sequenceMatch(sequenceFile, seqOffset, sizeQueryProtein, proteinTab, gapOpenPenalty, gapExtensionPenalty);  //maximum scores of each sequence
		algo.sequenceWithHighScore(res);  //order offsets and maximums
		int *off = algo.getOffsetMax();
		head.header_name(headerFile, off, headOffset);  //take name of the sequences thanks to their offset
	}
	
	//Close files
	sequenceFile.close();
	proteinFile.close();
	indexFile.close();
	headerFile.close();
	matrixFile.close();
	
	int *score = algo.getScoreMax();  //maximums scores of each sequence
	string *names = head.getNames();  //names of sequences with high scores
	
	datab.attributes(score, title, time, lenTitle, lenTime, residu, numbSeq, lenMax, names);
	
	return 0;
}
