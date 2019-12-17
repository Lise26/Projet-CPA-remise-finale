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

	//verification of the number of parameters given in input and recuperation of their values
	verif.verifParameters(argc, argv);	
	
	//Open files
	ifstream proteinFile(argv[1]);										
	ifstream sequenceFile(verif.getNameSequence());					
	ifstream indexFile(verif.getNameIndex());       
	ifstream headerFile(verif.getNameHeader());		
	ifstream matrixFile(verif.getNameMatrix());					
	
	int gapOpenPenalty = verif.getGapOpenPenalty();
	int gapExtensionPenalty = verif.getGapExtensionPenalty();
	
	//The program will only works if the files given in input are valid
	if ((proteinFile.is_open() && sequenceFile.is_open() && indexFile.is_open() && headerFile.is_open())!=0);
	else {
		cout << "Problème lors de l'ouverture des fichiers" << endl;
		exit(0);
	}
	
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
	
	//Init the substitution matrix (if it is given by the user)
	if(matrixFile.is_open()) {
		algo.substituteMatrix(matrixFile);
	}
	
	//calculate the scores of each sequence
	int* res = algo.researchScore(sequenceFile, seqOffset, sizeQueryProtein, proteinTab, gapOpenPenalty, gapExtensionPenalty);
	
	//order offsets and maximums
	algo.sequenceWithHighScore(res);
	int *off = algo.getOffsetMax();
	int *score = algo.getScoreMax();
	
	//find the names of the sequences thanks to their offset
	head.header_name(headerFile, off, headOffset);
	
	//return the result of the research into a file : result.txt
	ofstream result("./result.txt");
	
	datab.attributes(result, title, time, lenTitle, lenTime, residu, numbSeq, lenMax);  //informations about the database
	prot.info(result, argv[1]);															//informations about the query
	
	result << "Score Matrix : ";
	if(matrixFile.is_open()) {
		result << verif.getNameMatrix() << endl;
	}
	else {
		result << "BLOSUM 62" << endl;
	}
	result << "Gap Open Penalty : ";
	result << gapOpenPenalty << endl;
	result << "Gap Extension Penalty : ";
	result << gapExtensionPenalty << endl;
	
	head.info(result, score);															//names of the best sequences
	
	//Close files
	sequenceFile.close();
	proteinFile.close();
	indexFile.close();
	headerFile.close();
	matrixFile.close();
	
	return 0;
}
