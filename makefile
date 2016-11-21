all: prog

prog: main.o EuroTranslator.o Utility.o
	g++ main.o EuroTranslator.o Utility.o -o prog 

main.o: main.cpp
	g++ -c main.cpp

EuroTranslator.o: EuroTranslator.cpp
	g++ -c EuroTranslator.cpp

Utility.o: Utility.cpp
	g++ -c Utility.cpp
