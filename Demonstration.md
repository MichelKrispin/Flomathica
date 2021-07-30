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
>>> ? "werbung"
Hier koennte ihre Werbung stehen
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
