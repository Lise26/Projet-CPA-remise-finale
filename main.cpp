//to compile this program, a makefile has been made
//to run this program: ./project ./"protein searched" ./uniprot_sprot.fasta

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

#include "parameters.h"
#include "indeX.h"
#include "algorithm.h"
#include "headerSearch.h"
#include "matrixInit.h"
#include "conversion.h"

int main(int argc, char **argv) {
	
	parameters verif;
	indeX ind;
	algorithm a;
	headerSearch head;
	matrixInit mapi;
	conversion conv;
	
	verif.verifParameters(argc, argv);			//verification of the number of parameters given in input
	
	string nameSequence = argv[2];
	nameSequence.append(".psq");				//construction of the name of the sequence file in the database
	
	string nameIndex = argv[2];
	nameIndex.append(".pin");					//construction of the name of the index file in the database
	
	string nameHeader = argv[2];
	nameHeader.append(".phr");					//construction of the name of the header file in the database
	
	ifstream proteinFile(argv[1]);				//opening proteinFile				
	ifstream sequenceFile(nameSequence);		//opening sequenceFile				
	ifstream indexFile(nameIndex);              //opening indexFile
	ifstream headerFile(nameHeader);			//opening headerFile
	ifstream matrixFile("matrix_BLOSUM62.txt");
	
	vector<int> tableauOffset(0);				//varaiables to keep information from the indexFile
	vector<char> name;
	int size=0;
	
	//Init the substitution matrix
	mapi.substiuteMatrix(matrixFile);
	
	ind.indexReader(indexFile, &tableauOffset);		
	
	if(sequenceFile.is_open()) {
		//search for a match between the query protein and the sequence file of the database
	cout <<	a.sequenceMatch(proteinFile, sequenceFile, &tableauOffset) << endl;
		head.header_name(headerFile, a.sequenceMatch(proteinFile, sequenceFile, &tableauOffset), ind.getHeaderOffset(), &name, &size); 
	}
	//cout << ind.getHeaderOffset()[0] << endl;
	sequenceFile.close();
	proteinFile.close();
	indexFile.close();
	
	string p(ind.getLenTitle(),0);
	conv.charToString(p, ind.getTitle(), ind.getLenTitle());
	
	string d(ind.getLenTime()-7,0);
	conv.charToString(d, ind.getTime(), ind.getLenTime()-7);
	
	string n(size,0);
	conv.charToString(n, name, size);
	
	ofstream result("./result.txt");		//return the result of the research into a file : result.txt
	if(result){	
		result << "YOOOOOO" << endl;														
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

