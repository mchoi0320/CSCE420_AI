# Project 2

Implementing A* to solve Blocksworld problems

## Running the Program

Run

```
make
```

to compile the program. You have two options when running this program:


1. If you wish to examine the result of a single test file, enter

```
./BlocksworldAstar BWCHP/<file name>
```

into the command line to see the result on the terminal *and* have an output file of the same name as the test file saved in the `OUTPUT/` subdirectory.


2. If you wish to see the collective result of all existing test files, enter

```
./BlocksworldAstar
```

into the command line to see successes with summary statistics and/or failures on the terminal and on the `STATISTICS.txt` file.


*If you wish to remove all object and executable files after using the program, type*

```
make clean
```

*into the command line.*

## Note

* Please be sure to modify the value of `NUM_TEST_FILES` in `BlocksworldAstar.cpp` to match that of the number of files in the `BWCHP/`subdirectory if files are added and/or removed.

```cpp
#define NUM_TEST_FILES 45
```

* The current limit for the maximum number of iterations is **100,000**. This can be changed by redefining `MAX_ITERS` in `BlocksworldAstar.cpp`.

```cpp
#define MAX_ITERS 100000 // sets the BFS iteration limit to 100,000
```

## To be Continued...

- [ ] Improve the heuristic function!

- [ ] Clean up the code?

- [ ] Fix memory leaks...