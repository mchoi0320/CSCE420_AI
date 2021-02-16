# Project 1

Implementing BFS to solve Blocksworld problems

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


*If you wish to remove all object and executable files after using the program, type*

```
make clean
```
*into the command line.*

## Note

* The current limit for the maximum number of iterations is **5,000,000**. This can be changed by redefining `MAX_ITERS` in `BlocksworldBFS.cpp`.

```cpp
#define MAX_ITERS 5e6 // sets the BFS iteration limit to 5,000,000
```

* Memory leak is an issue in the current program design, which I was unable to fix. [2/15/21]
  * Attempted multiple solutions—including the use of `shared_ptr`—but still failed. :cry: [2/16/21]

## To be Continued...

- [ ] Fix memory leaks!

- [ ] Write outputs to files (maybe).

- [ ] Create a templated version of `BFS()`?