```
> ./Flomathica
==================================
==========> Flomathica <==========
==================================
Type 'exit()' to exit, '_toggle_ir()' to toggle LLVM IR and '? ""' for help
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

 - incr: Increment the argument by one
 - plus: Simple addition
 - werbung: Hier koennte ihre Werbung stehen
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

 - fib: Calculate the fibonacci numbers recursively
 - incr: Increment the argument by one
 - not_zero: Returns 1 if value is 0 and 0 otherwise
 - plus: Simple addition operator
 - werbung: Hier koennte ihre Werbung stehen
>>> fib(7)
 13
>>> exit()
```
