all: DPLL queens

parser.o: parser.cpp parser.hpp
	g++ -std=c++11 -c parser.cpp

DPLL: DPLL.cpp parser.o
	g++ -std=c++11 -o DPLL DPLL.cpp parser.o

queens: queens.cpp
	g++ -std=c++11 -o queens queens.cpp

clean:
	rm *.o DPLL queens