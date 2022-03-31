# *"Higher" level language for our 64-bit processor in Turing Complete*
___
## Definitions
- It is a procedural programming language.  
- C-like brackets `{ }` are used to define a program block.
- Callable procedures are defined by naming a program block and must not be nested into other blocks: `foo{ }`
- Arguments or parameters of a procedure should be defined in normal brackets after the name: `foo(bar){ }`
- Every line containing a command, that is not part of a block definition, must be terminated with a `;`
- Declaring a variable works by setting a name and assign a value to it - assignment uses `=` as operator: `foo=5;`
- Between any symbol or qualifier may be an unlimited amount of spaces or linebreaks.
- To use procedures from another file, put `use([file])` at the start of your code. The specified file should contain source code as well.

## Loops and goto
There are `while`, `for` and `loop` loops.

`while([condition]) { }` defines a while loop, that repeats its block until the condition is no longer met. 
More about conditions is written below.
`for([name],[start],[end],[inc])` defines a for loop, that repeats its block for the amount of times `n` to make `start+inc*n >= end` true.  
`loop([amount])` defines a loop, that repeats its block the given amount of times.

## Math
Arithmetic operations are integrated into the assigment: `foo = 5 + 9` and may include: `( ) + - * `.  
Division and modulo might be implemented on software-side.
Further logic operations are done by `| & ~ ^` (or, and, not, xor) and can be combined with arithmetic ones.  
Shifting uses `<<` and `>>` as well as rotation uses `<<<` and `>>>`.

## Conditions
Conditions are generally based on unsigned values and use the commonly accepted symbols: `=, !=, <, >, <=, >=`.  
Conditional blocks start with `if([condition]) { }` and might be chained by using `else{ }` or `else([condition]){ }`.  
A condition might include arithmetic and logical operations as well as boolean logic using `|| &&`.

## Arrays
Arrays are used for having more than one value inside a variable and can be used to iterate through data in an ordered list fashion.
They are declared directly using values `array = (1,2,3);` or with a length `array = [5];`.  
The values of an array can be accessed using a similar syntax `foo[0] = foo[1];`  
The length of an array is readable by using `bar = length(foo)`, where `foo` is the array and `bar` the variable to store the length to.

## Inbuilt functions
There are some inbuilt function that are exclusive to the processor, the game Turing Complete or the compiler itself.

- `ioread([val1],[val2],[port])` reads data from an IO port in the game.
- `iowrite([val1],[val2],[port])` writes data to an IO port in the game.
- `print([mode],[A],[B],[C])` writes data to the console. the mode is identical to the mode in the game
- `ascii([character])` converts a  constant character expression into in-game ascii if available.

## Keywords
Some keywords are defined to reduce boilerplate definitions and should not be overwritten:
- `false` represents the negative result of a boolean operation, it's defined as number `0`
- `true` represents the positive result of a boolean operation, it's defined as number `1`
- `console` represents the port of the console output in the game, its defined as number `4`
- `keyboard` represents the port of the keyboard output in the game, its defined as number `6`

## Example
Writing every letter A-Z to the console:
```
for(char,65-91){
    print(0,0,0,char);
}
```
Bubblesort:
```
array = (6,1,4,2,9,5);
len = length(array);
for(i,1,len,1) {
    if(array[i-1] > array[i]) {
        val = array[i];
        array[i] = array[i-1];
        array[i-1] = val;
    }
}
```
