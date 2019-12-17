#include "database.h"

int database::attributes(int* score, vector<char> title, vector<char> time, int lenTitle, int lenTime, int64_t residu, int numbSeq, int lenMax, string* names) {
	
	string p(lenTitle,0);
	conv.charToString(p, title, lenTitle);					//conversion : char to string
			
	string d(lenTime-7,0);
	conv.charToString(d, time, lenTime-7);					//conversion : char to string

	ofstream result("./result.txt");						//return the result of the research into a file : result.txt (in the directory where the fonction has been called)
	if(result){															
		result << "Database title : ";
		result << p << endl;
		result << "Database time : ";
		result << d << endl;
		result << "Database size : ";
		result << residu << " residues in " << numbSeq << " sequences"<< endl;
		result << "Longeset db sequence : ";
		result << lenMax << endl;
		result << "\n\n" << endl;
		result << "50 best matching prots :                                        Scores\n" << endl;
		for (int i = 0; i<50;i++){
			result << names[i] << "...   " << score[i] << endl;
		}
	}
	
	return 0;
}
