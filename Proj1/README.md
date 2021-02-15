# Project 1

CSCE 420 Artificial Intelligence Project 1: Implementing BFS to solve Blocksworld problems

## Running the Program

Run

```
make
```
to compile the program and enter

```
./BlocksworldBFS <file name>
```

into the command line to run it.

## Note

* The current limit for the maximum number of iterations is 1,000,000. This can be changed by redefining `MAX_ITERS` in `BlocksworldBFS.cpp`.

```cpp
#define MAX_ITERS 1e6 // sets the iteration limit to 1,000,000
```

* Memory leak is an issue in the current program design, which I was unable to fix.

## To be Continued...

1. Fix memory leaks!

2. Write outputs to files (maybe).

3. Create a templated version of `BFS()`?