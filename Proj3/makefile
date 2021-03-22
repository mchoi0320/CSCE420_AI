all: sammys

parser.o: parser.cpp parser.hpp
	g++ -std=c++11 -c parser.cpp

NatDed.o: NatDed.cpp NatDed.hpp
	g++ -c NatDed.cpp

sammys: sammys.cpp parser.o NatDed.o
	g++ -o sammys sammys.cpp parser.o NatDed.o

clean:
	rm *.o sammys