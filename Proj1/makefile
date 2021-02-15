all: BlocksworldBFS

BlocksworldBFS: BlocksworldBFS.o State.o Node.o
	g++ -o BlocksworldBFS BlocksworldBFS.o State.o Node.o

BlocksworldBFS.o: BlocksworldBFS.cpp State.h Node.h
	g++ -std=c++11 -c BlocksworldBFS.cpp

State: State.cpp State.h
	g++ -c State.cpp

Node: Node.cpp Node.h
	g++ -c Node.cpp
