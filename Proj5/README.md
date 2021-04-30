# Project 5

Implementing Resolution to perform logical proofs on the Sammy's Sport Shop and the Wumpus World problems

## Running the Program

Run

```
make
```

to compile two programs: `resolution.cpp` and `wumpus.cpp`.

To see the algorithm at work, enter

```
./resolution <KB file name> <query>
```

into the command line.

Using `wumpus.cpp`, you can generate KB files for the Wumpus World problem by entering

```
./wumpus <side length of square grid>
```

into the command line.

*If you wish to remove all object and executable files after using the program, type*

```
make clean
```

*into the command line.*

## Note

* The program works Sammy's Sport Shop problem, but fails for the Wumpus World problem. I believe that the likely cause is an incorrect knowledge base.

  * I was able to output the correct results for where pits are located and where they are not, but my program falsely returns success for any tile when checking if it is safe, including those already proven to have a pit. Moreover, it is still failing to locate the wumpus. [4/28/20]

  * The error turned out to be a typo in line 31 of `wumpus.cpp`. Now the program works as it should! [4/30/20]

* The `wumpus.cpp` script is not very effective. For the constraint that only one wumpus exists across the entire board, I was not able to handle repetitive clauses through the code itself, so I manually removed them.

## To be Continued...

- [x] Improve the knowledge base `wumpus.cnf`
