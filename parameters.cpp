#include "parameters.h"

int parameters::verifParameters(int argc, char **argv) {        
	if(argc > 6 or argc < 3) {								//the user must at least give two parameters and no more than six
		cout << "Le nombre de paramètres entrés n'est pas correct, le format est : ./project query.fasta database.fasta [BLOSUM] [GAP OPEN PENALTY] [GAP EXTENSION PENALTY].\n" << endl;
		exit(0);
	}
	
	if(argc > 3) {
		if(argc == 4){										//one optional parameter (the Blosum matrix) is given by the user
			initParameters(argc, argv);
			nameMatrix = argv[3];
			gapOpenPenalty = 11;
			gapExtensionPenalty = 1;
		}
		else if(argc == 5){									//two optional parameters (the Blosum matrix and the gap open penalty) are given by the user
			initParameters(argc, argv);
			nameMatrix = argv[3];
			string gapOpen = argv[4];
			gapOpenPenalty = stoi(gapOpen);					//conversion : char to int
			gapExtensionPenalty = 1;
		}
		else {												//all the optional parameters are given by the user
			initParameters(argc, argv);
			initOptionalParametersAll(argc, argv);
		}
	}
	else {													//no optional parameters is given by the user
		initParameters(argc, argv);
		initOptionalParametersDefault(argc, argv);			//optional parameters are initialised with their default values
	}
	
	return(0);
}

int parameters::initParameters(int argc, char **argv) {		//initialise the mandatory parameters
	nameSequence = argv[2];
	nameSequence.append(".psq");							//construction of the sequence file name in the database
	
	nameIndex = argv[2];
	nameIndex.append(".pin");								//construction of the index file name in the database
	
	nameHeader = argv[2];
	nameHeader.append(".phr");								//construction of the header file name in the database
	
	return 0;
}

int parameters::initOptionalParametersDefault(int argc, char **argv) {	//initialise the optional parameters if none is given (default values)
	
	nameMatrix = "NULL";									//the default matrix is coded in the class "algorithm" and is not in a file (thus no file name)
	
	gapOpenPenalty = 11;
	
	gapExtensionPenalty = 1;
	
	return 0;
}

int parameters::initOptionalParametersAll(int argc, char **argv) {		//initialise the optional parameters if they are all given
	nameMatrix = argv[3];
	
	string gapOpen = argv[4];
	gapOpenPenalty = stoi(gapOpen);							//conversion : char to int
	
	string gapExtension = argv[5];
	gapExtensionPenalty = stoi(gapExtension);				//conversion : char to int
	
	return 0;
}

//GETTERS

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
