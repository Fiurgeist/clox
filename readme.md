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
* Resolver
  * ParseError: unused local variable
* Interpreter
  * handle `break` statement in `for` and `while` loops
  * handle return statement via state instead of with exception handling (~4 times faster)
