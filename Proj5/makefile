all: resolution wumpus

parser.o: parser.cpp parser.hpp
	g++ -std=c++11 -c parser.cpp

resolution: resolution.cpp parser.o
	g++ -std=c++11 -o resolution resolution.cpp parser.o

wumpus: wumpus.cpp
	g++ -std=c++11 -o wumpus wumpus.cpp

clean:
	rm *.o resolution wumpus