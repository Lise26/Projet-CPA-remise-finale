project: parameters.o indexSearch.o sequenceSearch.o check.o conversion.o headerSearch.o mapInit.o main.o
	g++ -o project parameters.o indexSearch.o sequenceSearch.o check.o conversion.o headerSearch.o mapInit.o main.o
	
parameters.o: parameters.cpp
	g++ -o parameters.o -c parameters.cpp -Wall -O
	
indexSearch.o: indexSearch.cpp
	g++ -o indexSearch.o -c indexSearch.cpp -Wall -O
	
sequenceSearch.o: sequenceSearch.cpp
	g++ -o sequenceSearch.o -c sequenceSearch.cpp -Wall -O
	
check.o: check.cpp
	g++ -o check.o -c check.cpp -Wall -O
	
conversion.o: conversion.cpp
	g++ -o conversion.o -c conversion.cpp -Wall -O
	
headerSearch.o: headerSearch.cpp
	g++ -o headerSearch.o -c headerSearch.cpp -Wall -O

mapInit.o: mapInit.cpp
	g++ -o mapInit.o -c mapInit.cpp -Wall -O
	
main.o: main.cpp parameters.h indexSearch.h sequenceSearch.h check.h conversion.h headerSearch.h mapInit.h
	g++ -o main.o -c main.cpp -Wall -O 
