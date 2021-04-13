# Project 4

Implementing the DPLL algorithm to solve the Australia Map-Coloring problem and the N-Queens problem

## Running the Program

Run

```
make
```

to compile two programs: `DPLL.cpp` and `queens.cpp`. You have two options when running `DPLL.cpp`, the main program:

1. If you wish to see the DPLL algorithm execute *with* the unit-clause heuristic, enter

```
./DPLL <KB file name>
```

into the command line.


2. If you wish to see the DPLL algorithm execute *without* the unit-clause heuristic, enter

```
./DPLL <KB filename> -unit
```

into the command line.

Using `queens.cpp`, you can generate KB files for the N-Queens problem by entering

```
./queens <number of queens>
```

into the command line.

*If you wish to remove all object and executable files after using the program, type*

```
make clean
```

*into the command line.*

## Note

* Currently, the propositional symbols in the output model are not in a nice, easy-to-read order. I would like to fix this to print the symbols in ascending order.

## To be Continued...

- [ ] Find a way to make the propositional symbols in the model print in a properly organized manner!

- [ ] Get rid of memory leaks?