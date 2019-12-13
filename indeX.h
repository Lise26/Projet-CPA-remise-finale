#include <fstream>
#include <iostream>
#include <vector> 
#include <string>
#include <stdio.h>
using namespace std;

class indeX {
	vector<int> headOffset;
	vector<int> seqOffset;
	vector<char> title;
	vector<char> time;
	
	int version, nbSeq, lenMax, lenTitle, lenTime, type;
	int64_t residu;
	
	public :
		inline void littleBigEndian (int &x);
		int indexReader(ifstream& indexFile);	
		void readFile(ifstream& file, int& value, int multipe, int type);
		
		int getVersion() const;
		int getLenTitle() const;
		int getLenTime() const;
		int getNbSeq() const;
		int64_t getResidu() const;
		int getLenMax() const;
		
		//string getTitle() const;
		vector<int> const& getHeaderOffset();
		vector<int>const& getSeqOffset();
		vector<char> const& getTitle();
		vector<char>const& getTime();
};
