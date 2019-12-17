#include "database.h"

int database::attributes(ofstream &result, vector<char> title, vector<char> time, int lenTitle, int lenTime, int64_t residu, int numbSeq, int lenMax) {
															//displays information about the database in the results file
	
	string p(lenTitle,0);
	conv.charToString(p, title, lenTitle);					//conversion : char to string
			
	string d(lenTime-7,0);
	conv.charToString(d, time, lenTime-7);					//conversion : char to string 

	if(result){	
		result << "Protein Sequence Alignement using the Smith-Waterman Algorithm\n\n" << endl;  														
		result << "Database title : ";
		result << p << endl;
		result << "Database time : ";
		result << d << endl;
		result << "Database size : ";
		result << residu << " residues in " << numbSeq << " sequences"<< endl;
		result << "Longeset db sequence : ";
		result << lenMax << endl;
	}
	
	return 0;
}
