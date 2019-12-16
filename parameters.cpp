#include "parameters.h"

int parameters::verifParameters(int argc, char **argv) {        
	if(argc > 6 or argc < 3) {
		cout << "Le nombre de paramètres entrés n'est pas correct, le format est : project query.fasta database.fasta [BLOSUM] [GAP OPEN PENALTY] [GAP EXTENSION PENALTY].\n" << endl;
		exit(0);
	}
	
	if(argc > 3) {
		if(argc = 4){
			initParameters(argc, argv);
			nameMatrix = argv[3];
			gapOpenPenalty = 11;
			gapExtensionPenalty = 1;
		}
		else if(argc = 5){
			initParameters(argc, argv);
			nameMatrix = argv[3];
			string gapOpen = argv[4];
			gapOpenPenalty = stoi(gapOpen);
			gapExtensionPenalty = 1;
		}
		else {	
			initParameters(argc, argv);
			initOptionalParametersAll(argc, argv);
		}
	}
	else {
		initParameters(argc, argv);
		initOptionalParametersDefault(argc, argv);
	}
	
	return(0);
}

int parameters::initParameters(int argc, char **argv) {
	nameSequence = argv[2];
	nameSequence.append(".psq");				//construction of the name of the sequence file in the database
	
	nameIndex = argv[2];
	nameIndex.append(".pin");					//construction of the name of the index file in the database
	
	nameHeader = argv[2];
	nameHeader.append(".phr");					//construction of the name of the header file in the database
	
	return 0;
}

int parameters::initOptionalParametersDefault(int argc, char **argv) {
	
	nameMatrix = "BLOSUM62.txt";				//à remplir directement PAS FICHIER
	
	gapOpenPenalty = 11;
	
	gapExtensionPenalty = 1;
	
	return 0;
}

int parameters::initOptionalParametersAll(int argc, char **argv) {
	nameMatrix = argv[3];
	
	string gapOpen = argv[4];
	gapOpenPenalty = stoi(gapOpen);				//transforme un string en entier
	
	string gapExtension = argv[5];
	gapExtensionPenalty = stoi(gapExtension);
	
	return 0;
}

//GETTERS AND SETTERS

string parameters::getNameSequence() const {
	return nameSequence;
}

string parameters::getNameIndex() const{
	return nameIndex;
}

string parameters::getNameHeader() const{
	return nameHeader;
}

string parameters::getNameMatrix() const{
	return nameMatrix;
}

int parameters::getGapOpenPenalty() const{
	return gapOpenPenalty;
}

int parameters::getGapExtensionPenalty() const{
	return gapExtensionPenalty;
}
