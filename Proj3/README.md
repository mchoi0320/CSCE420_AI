# Project 3

Implementing Rules of Inference and proving the Sammy's Sport Shop Problem using Natural Deduction

## Running the Program

Run

```
make
```

to compile the program. You have two options when running this program:


1. If you wish to see tests of the ROI functions, enter

```
./sammys
```

into the command line to see the results.


2. If you wish to See the final KB created from the Natural Deduction proof for the Sammy's Sport Shop problem, enter

```
./sammys sammys.kb
```

into the command line to obtain the final KB file in the current working directory.


*If you wish to remove all object and executable files after using the program, type*

```
make clean
```

*into the command line.*

## Note

In the current version of my `NatDed.cpp`:

* the exception handling is not as thorough, detailed, nor efficient as I would like it to be, so the ROI functions may not detect some errors. :disappointed:

* some of the ROI functions assume that the arguments are passed in a fixed order or that the argument is formatted in a specific way. The method I currently use to somewhat check the order for the other functions seems far from efficient, which I want to better.

* case-insensitivity is not implemented yet.

## To be Continued...

- [ ] Modify functions to ensure that the order of arguments does not matter

- [ ] Implement case-insensitivity

- [ ] Improve exception handling

- [ ] Try to make the code more efficient!

- [ ] Memory leaks here, too...