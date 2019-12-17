#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <map>
#include <string>
using namespace std;

class sequence {
	vector<int> sizeSequence;
  
  public:
	int fillSequenceSize(vector<int> tableauOffset);
    vector<int>const& getSizeSequence();
};
