# *"Higher" level language for our 64-bit processor in Turing Complete*
___
## Definitions
- It is a procedural programming language.  
- C-like brackets `{ }` are used to define a program block.
- Callable procedures are defined by naming a program block and must not be nested into other blocks: `foo{ }`
- Arguments or parameters of a procedure should be defined in normal brackets after the name: `foo(bar){ }`
- Every line containing a command, that is not part of a block definition, must be terminated with a `;`
- Declaring a variable works by setting a name and assign a value to it - assignment uses `=` as operator: `foo=5;`
- Declaring constants is similar to variables, it requires a `#` in front of it and cannot be used inside of a block: `#const=42;`
- Between any symbol or qualifier may be an unlimited amount of spaces or linebreaks.
## Loops and goto
There are `while`, `for` and `loop` loops. `label` and `goto` are available as well.

`while([condition]) { }` defines a while loop, that repeats its block until the condition is no longer met. 
More about conditions is written below.  
`for([name],[range])` defines a for loop, that repeats its block for all values in the defined range using the set variable.  
An example for a range could be `0-5`. 
**Note:** The range has in inclusive start and an exclusive end, that means the block gets called for `0, 1, 2, 3 and 4`. The range requires constant values.   
`for([name],[start],[end],[inc])` defines a for loop, that repeats its block for the amount of times `n` to make `start+inc*n >= end` true.  
`loop([amount])` defines a loop, that repeats its block the given amount of times.  
`label([name])` defines a label with a name at the given position in the code.  
`goto([name])` continues to execute code from the label with the given name.

## Math
Arithmetic operations are integrated into the assigment: `foo = 5 + 9` and may include: `( ) + - *`.  
Division and modulo might be implemented on software-side.
Further logic operations are done by `| & ~` (or, and, not) and can be combined with arithmetic ones.  
Shifting uses `<<` and `>>` as well as rotation uses `<<<` and `>>>`.

## Inbuilt functions
There are some inbuilt function that are exclusive to the processor and the game Turing Complete.

- `ioread([name1],[name2],[port])` which reads data from an IO port in the game.
- `iowrite([name1],[name2],[port])` which writes data to an IO port in the game.