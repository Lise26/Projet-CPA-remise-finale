#include "headerSearch.h"

void headerSearch::header_name(ifstream& headerFile, int indice, vector<int> headerOffset, vector<char> *name, int *size){ // Init values of parameters by reading the header file
	int stock = 0;									//Each byte will be stored there
	string previous = "0";								//Keep the previous byte
	string before_last = "0";							//Keep the before last byte
	
	for(int i = headerOffset[indice]; i < headerOffset[indice+1];i++){
		headerFile.seekg(i);
		headerFile.read((char *)&stock, 1);	
		string res = conv.decToHex(stock);
		
		if(before_last == "80" && previous == "1a"){ 
			if (stock <= 128){					//Read next bytes as string if current byte <= 128
				char* title = new char[stock+2];
				headerFile.read((char *)&*title, stock+2);
				i+= (stock+2);
				if(title[0] == 's' && title[1] == 'p'){
					for(int i = 0; i < stock+2; i++){
						(*size) = i-1;
						(*name).push_back(title[i]);
					}
				}		
			}
			else if(stock > 128){					//Read next bytes as int if current byte > 128, then as string
				int byte = stock - 128;				//How many bytes it shall read for the length of the following string
				headerFile.read((char *)&stock, byte);
				i+= byte;
				char* title = new char[stock+2];
				headerFile.read((char *)&*title, stock+2);
				i+= (stock+2);
				if(title[0] == 's' && title[1] == 'p'){
					for(int i = 0; i < stock+2; i++){
						(*size) = i-1;
						(*name).push_back(title[i]);
					}
				}	
			}
		}
		
		before_last = previous;
		previous = res;
	}
}
