//to compile this program, a makefile has been made
//to run this program: ./project ./"protein searched" ./uniprot_sprot.fasta [MATRIX FILE] [GAP OPEN PENALTY] [GAP EXTENSION PENALTY]

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
	
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// New code 
	/*
	ifstream database("newE.fasta.psq", ios::binary | ios::ate);
	streampos database_size;
	
	database_size = database.tellg();
	
	int8_t *db = new int8_t[database_size];
	
	database.seekg(0, ios::beg);
	database.read((char*)db, sizeof(int8_t)*database_size); // on crée le tablea db de taille database_size et chaque élémenent correspond à "8 bits"
	
	int compteur = 0; 
	cout << database_size << endl;
	
	for ( int i = 0; i < database_size ; i++)
		compteur ++;
		
	cout << compteur << endl;
	
	database.close();
	*/
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	
	// je crée le fichier database, je prend ce qu il y a dedans et le fout dans le tableau "db", je ferme après ce fichier car il ne me sert plus a rien
	// pour accéder à chaque élémenent de ma database, il me suffit de faire db[indice]; je dois récuperer dans l'offset table les indice de chaque début de 
	// séquence
	
	
	
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
		int* res = algo.sequenceMatch(sequenceFile, seqOffset, sizeQueryProtein, proteinTab, sequenceSize, gapOpenPenalty, gapExtensionPenalty);
		//for(int i=0; i < seqOffset.size() -1; i++) {
			//cout << res[i] << endl;
		//}
		//int res = algo.sequenceMatch(db, seqOffset, sizeQueryProtein, proteinTab, sequenceSize, gapOpenPenalty, gapExtensionPenalty);
		algo.sequenceWithHighScore(res);
		int *off = algo.getOffsetMax();
		cout << off[0] << endl;
		head.header_name(headerFile, off, headOffset);
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
		result << "50 best matching prots :                                              Scores\n" << endl;
		for (int i = 0; i<50;i++){
			head.getNames(i);
			result << head.getNames(i) << "...   " << algo.getScoreMax()[i] << endl;
		}
	}
	
	cerr << "fin" << endl;
	
	return 0;
}



