### Lox Scripting Language Bytecode VM

A version of the Bytecode VM written in C.
Based on the book https://craftinginterpreters.com.

For a Tree-Walk Interpreter written in Go see [golox](https://github.com/Fiurgeist/golox).

#### Additions to Lox

* Lexer
  * C-style multiline comments `/* ... */`
  * `break` keyword
* Parser
  * `break` statement
* VM
  * ParseError: unused local variable
  * handle `break` statement in `for` and `while` loops
