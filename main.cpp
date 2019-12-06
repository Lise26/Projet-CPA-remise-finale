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
#include "indexSearch.h"
#include "sequenceSearch.h"
#include "headerSearch.h"
#include "mapInit.h"

int main(int argc, char **argv) {
	
	parameters verif;
	indexSearch ind;
	sequenceSearch s;
	headerSearch head;
	mapInit mapi;
	
	verif.verifParameters(argc, argv);			//verification of the number of parameters given in input
	
	string nameSequence = argv[2];
	nameSequence.append(".psq");				//construction of the name of the sequence file in the database
	
	string nameIndex = argv[2];
	nameIndex.append(".pin");				//construction of the name of the index file in the database
	
	string nameHeader = argv[2];
	nameHeader.append(".phr");				//construction of the name of the header file in the database
	
	ifstream proteinFile(argv[1]);				//opening proteinFile				
	ifstream sequenceFile(nameSequence);		//opening sequenceFile				
	ifstream indexFile(nameIndex);              //opening indexFile
	ifstream headerFile(nameHeader);			//opening headerFile
	ifstream matrixFile("matrix_BLOSUM62.txt");
	
	vector<int> tableauOffset(0);				//varaiables to keep information from the indexFile
	vector<int> headerOffset(0);
	vector<char> title;
	vector<char> date;
	vector<char> name;
	int nbSeq, lmax, size, sizet, sized =0;
	int64_t residu = 0;
	
	//Init the substitution matrix
	unordered_map<string,int> matrixMap;
	mapi.substiuteMatrix(matrixMap, matrixFile);
	///////////////////////////// ON LIT LE DICO COMME ÇA ///////////////////////////////
	cout << matrixMap["YF"] << endl;
	
	ind.indexReader(indexFile, &tableauOffset, &headerOffset, &nbSeq, &lmax, &residu, &title, &date, &sizet, &sized);		
	
	if(sequenceFile.is_open()) {
		//search for a match between the query protein and the sequence file of the database
		head.header_name(headerFile, s.sequenceMatch(proteinFile, sequenceFile, &tableauOffset), headerOffset, &name, &size); 
	}
	
	sequenceFile.close();
	proteinFile.close();
	
	string p(sizet,0);
	for(int i = 0; i < sizet; i++){
		p[i] = title[i];
	}
	
	string d(sized,0);
	for(int i = 0; i < sized; i++){
		d[i] = date[i];
	}
	
	string n(size,0);
	for(int i = 0; i < size; i++){
		n[i] = name[i];
	}
	///////////////////////////////////////TO DO : accesseurs
	

	ofstream result("./result.txt");		//return the result of the research into a file : result.txt
	if(result){															
		result << "Database title : ";
		result << p << endl;
		result << "Database time : ";
		result << d << endl;
		result << "Database size : ";
		result << residu << " residues in " << nbSeq << " sequences"<< endl;
		result << "Longeset db sequence : ";
		result << lmax << endl;
		result << "\n\n" << endl;
		result << "The matching protein is : \n" << n << endl;
	}	
	
	return(0);
}

