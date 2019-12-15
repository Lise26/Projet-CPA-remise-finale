project: parameters.o protein.o database.o indeX.o sequence.o header.o conversion.o algorithm.o main.o
	g++ -o project parameters.o protein.o database.o indeX.o sequence.o header.o conversion.o algorithm.o main.o
	
parameters.o: parameters.cpp
	g++ -o parameters.o -c parameters.cpp -Wall -O

protein.o: protein.cpp
	g++ -o protein.o -c protein.cpp -Wall -O

database.o: database.cpp
	g++ -o database.o -c database.cpp -Wall -O
	
indeX.o: indeX.cpp
	g++ -o indeX.o -c indeX.cpp -Wall -O
	
sequence.o: sequence.cpp
	g++ -o sequence.o -c sequence.cpp -Wall -O

header.o: header.cpp
	g++ -o header.o -c header.cpp -Wall -O
	
conversion.o: conversion.cpp
	g++ -o conversion.o -c conversion.cpp -Wall -O

algorithm.o: algorithm.cpp
	g++ -o algorithm.o -c algorithm.cpp -Wall -O
	
main.o: main.cpp parameters.h protein.h database.h indeX.h sequence.h header.h conversion.h algorithm.h
	g++ -o main.o -c main.cpp -Wall -O 
