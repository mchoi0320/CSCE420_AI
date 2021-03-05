all: BlocksworldAstar

BlocksworldAstar: BlocksworldAstar.o State.o Node.o
	g++ -o BlocksworldAstar BlocksworldAstar.o State.o Node.o

BlocksworldAstar.o: BlocksworldAstar.cpp State.h Node.h
	g++ -std=c++11 -O -c BlocksworldAstar.cpp

State: State.cpp State.h
	g++ -c State.cpp

Node: Node.cpp Node.h
	g++ -c Node.cpp

clean:
	rm *.o BlocksworldAstar
