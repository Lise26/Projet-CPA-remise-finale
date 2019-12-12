//to compile this program, a makefile has been made
//to run this program: ./project ./"protein searched" ./uniprot_sprot.fasta [MATRIX FILE] [GAP OPEN PENALTY] [GAP EXTENSION PENALTY]

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

#include "parameters.h"
#include "protein.h"
#include "database.h"

#include "algorithm.h"

void charToString(string& s, vector<char> tab, int size){		//Convert from vector<char> to string
	for(int i = 0; i < size; i++){
		s[i] = tab[i];
	}
}

int main(int argc, char **argv) {
	
	parameters verif;
	protein prot;
	database data;
	
	indeX ind;
	sequence seq;
	header head;

	algorithm algo;

	verif.verifParameters(argc, argv);					//verification of the number of parameters given in input
	
	ifstream proteinFile(argv[1]);						//opening proteinFile				
	ifstream sequenceFile(verif.getNameSequence());		//opening sequenceFile				
	ifstream indexFile(verif.getNameIndex());           //opening indexFile
	ifstream headerFile(verif.getNameHeader());			//opening headerFile
	ifstream matrixFile(verif.getNameMatrix());			//opening matrixFile
	
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
	
	//Informations about the sequence
	seq.fillSequenceSize(ind.getSeqOffset());
	vector<int> sequenceSize = seq.getSizeSequence();
	
	//Init the substitution matrix
	algo.substiuteMatrix(matrixFile);	
	
	if(sequenceFile.is_open()) {
		int *res = algo.sequenceMatch(sequenceFile, seqOffset, sizeQueryProtein, proteinTab, sequenceSize, gapOpenPenalty, gapExtensionPenalty);
		for(int i=0; i<seqOffset.size(); i++) {
			cout << res[i] << endl;
		}
		//head.header_name(headerFile, algo.sequenceMatch(sequenceFile, seqOffset, sizeQueryProtein, proteinTab, sequenceSize), headOffset);
	}
	
	sequenceFile.close();
	proteinFile.close();
	indexFile.close();
	headerFile.close();
	matrixFile.close();
	
	//à mettre dans data.attributes();
	
	string p(ind.getLenTitle(),0);
	charToString(p, ind.getTitle(), ind.getLenTitle());
	
	string d(ind.getLenTime()-7,0);
	charToString(d, ind.getTime(), ind.getLenTime()-7);
	
	string n(head.getSize(),0);
	charToString(n, head.getName(), head.getSize());

	ofstream result("./result.txt");		//return the result of the research into a file : result.txt
	if(result){															
		result << "Database title : ";
		result << p << endl;
		result << "Database time : ";
		result << d << endl;
		result << "Database size : ";
		result << ind.getResidu() << " residues in " << ind.getNbSeq() << " sequences"<< endl;
		result << "Longeset db sequence : ";
		result << ind.getLenMax() << endl;
		result << "\n\n" << endl;
		result << "The matching protein is : \n" << n << endl;
	}
	
	return(0);
}



