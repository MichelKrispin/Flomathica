# Flomathica
A student project to implement a very small custom interpreter language. This project is neither complete nor bug-free.

## Build
The project depends upon [llvm-12](https://releases.llvm.org/download.html#12.0.0) and `llvm-config`. Some earlier version of LLVM might work but were not tested. The same applies for Windows and Mac OS.

If everything is installed a `./build` directory is needed. Creating it and running a Makefile builds the interpreter.
```shell
mkdir build
make
```


## Usage
After building the interpreter it can be started with
```shell
./Flomathica
```

It is possible to write functions or operators beforehand in a file and load them into the interpreter.
```shell
./Flomathica demo.flo
```

The help command `? ""` lists all existent functions and their help. If no help string was provided it just shows the names of the expected arguments.


## Language

The language itself is rather simple. Everything is of type double and every function has one return value (marked with a `!`). Variables can't be defined so a constant value can only be defined using a constant function.
Operators are just functions which take in two arguments. Every statement inside a function starts with a `$` and loops have to be implemented recursively.

A simple constant function looks like
```
>>> def five() ! 5
>>> five()
5
```

while the same operator would be defined as
```
>>> operator op_five(x, y) ! 5
>>> 1 op_five 2
5
```

For more detailed information have a look at the `demo.flo` and `Demonstration.md` files.


## Demonstration 

In the `demo.flo` file are some predefined functions to show how functions and operators can be defined.

```
> ./Flomathica
====================================
===========> Flomathica <===========
====================================
-------Predefined functions---------
  exit()         to exit
  _toggle_ir()   to toggle LLVM IR
  _broom()       to clear the screen
  ? ""           to view the help
------------------------------------
>>> def incr(x) "Increment the argument by one" ! x + 1
>>> operator plus(x, y) "Simple addition"
...   $ result = x + y
...   ! result
>>> 1 plus 2
3
>>> incr(3) plus 3
7
>>> incr(3) plus 3 plus 3
10
>>> ? ""
? "<function-name>" to get specific help

 - %:  X % Y : What is X % of Y
 - _broom(): Sweep everything off the screen
 - _toggle_ir(): Toggle to show IR Code
 - exit(): Exit the interpeter ('#' also works)
 - incr: Increment the argument by one
 - plus: Simple addition
>>> ? "plus"
Simple addition
>>> ? "incr"
Increment the argument by one
>>> exit()
> ./Flomathica demo.flo
>>> ? ""
? "<function-name>" to get specific help

 - %:  X % Y : What is X % of Y
 - _broom(): Sweep everything off the screen
 - _toggle_ir(): Toggle to show IR Code
 - exit(): Exit the interpeter ('#' also works)
 - fib: Calculate the fibonacci numbers recursively
 - incr: Increment the argument by one
 - not_zero: Returns 1 if value is 0 and 0 otherwise
 - plus: Looks empty... Nobody knows what plus is doing
>>> fib(7)
 13
>>> exit()
```


