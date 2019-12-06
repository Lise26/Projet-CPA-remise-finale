#include "parameters.h"

int parameters::verifParameters(int argc, char **argv) {        
	if(argc != 3) {
		cout << "Le nombre de paramètres entrés n'est pas correct.\n" << endl;
		exit(0);
	}
	return(0);
}
