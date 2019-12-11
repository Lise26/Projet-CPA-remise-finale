#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <map>
#include <string>
using namespace std;

#include "binary.h"

class sequence : public binary
{
	vector<int> sizeSeq;
	vector<int>* sizeSequence = &sizeSeq;
  
  public:
	int sequenceSize(vector<int> *tableauOffset);
    vector<int>* getSizeSequence();
};
