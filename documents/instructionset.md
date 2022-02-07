# *64-bit instruction set in TuringComplete*
___
## Description format
___
Every instruction is described by a readable asm format like: `addi nptr,0xA6,0x01`   
and by a bit specific format like: `0x90-000001-000000A6`.  
The two `-` are just for readability and don't actually belong to the 64-bit instruction.
There are certain rules:
* The first byte *always* contains the operation code for the core processing unit
* The bytes 2 and 3 *typically* contain two addresses to read from the register
* Byte 4 *typically* contains an address to write to the register
* The last 4 bytes (32-bit) are used as immediate value if necessary
* If one section is not used, it can be written as `X` instead: `0x01-X-00000000` = `0x01-000000-00000000`
* To relate the arguments from the asm notation to the bitwise notation, 
they can have a namespace letter that doesnt belong to the hex representation.
* If there is any exception to this pattern, it is mentioned.

Furthermore, there are placeholders used in the asm style 
format to display possible values without further explaination:
* `[imm]` means you can use an immediate value for this parameter (typically 32-bit)
* `[reg]` means you can use a register address for this parameter (0 - last register)
* `[R:reg]` means you can relate the argument with the bit notation by looking where the R's are
___
### Jumping and branching
___
#### unconditional jump
An unconditional jump is used for jumping to a fixed pc 
by setting the program counter to a specific value.  
`jmp [J:adr]` `0x01-JJJJJJ-JJJJJJJJ` - the adr is defined by the last 7 bytes in the instruction 
and therefore you can jump by an 56-bit unsigned value
#### branches
Branch based on the current pc by a given distance if a specific condition is met.  
The conditions are checked based on signed values.
#### branch on equal
`beq [R:reg],[S:reg],[T:imm]` `0x02-RRSS00-TTTTTTTT`  
Branching to `T` if register contents match condition `R = S`.
#### branch on not equal
`bneq [R:reg],[S:reg],[T:imm]` `0x03-RRSS00-TTTTTTTT`  
Branching to `T` if register contents do **not** match condition `R = S`.
#### branch on less
`bl [R:reg],[S:reg],[T:imm]` `0x04-RRSS00-TTTTTTTT`  
Branching to `T` if register contents match condition `R < S`.
#### branch on less or equal
`bleq [R:reg],[S:reg],[T:imm]` `0x05-RRSS00-TTTTTTTT`  
Branching to `T` if register contents match condition `R <= S`.
#### branch on greater
`bg [R:reg],[S:reg],[T:imm]` `0x06-RRSS00-TTTTTTTT`  
Branching to `T` if register contents do **not** match condition `R <= S`.
#### branch on greater or equal
`bgeq [R:reg],[S:reg],[T:imm]` `0x07-RRSS00-TTTTTTTT`  
Branching to `T` if register contents do **not** match condition `R < S`.
#### branching with immediate values
To branch with an immediate value in the comparison part of the instruction, 
the immediate flag needs to be set ultimately changing the actual instruction.  
e.g. the immediate version `beq` would be:  
`beqi [R:reg],[S:imm],[T:imm]` `0x12-RRTTTT-SSSSSSSS`  
**Note**: The actual 32-bit immediate value is used for the comparison and a 16-bit value is used for branching.  
This means using this method, you cannot branch the same distance as without the immediate comparison.
___
### ALU operations
___
All ALU operations usually work by putting 2 values into the ALU 
and having it calculate a specific output with an operator.  
It usually uses all three arguments. 
Most operations do have an immediate equivalent as well, that replaces the second argument.
#### add
Adds two values and writes them to a target register `T = R + S`.  
`add [R:reg][S:reg][T:reg]` `0x80-RRSSTT-X`  
`addi [R:reg][S:imm][T:reg]` `0x90-RR00TT-SSSSSSSS`
#### sub
Subtracts two values and writes them to a target register `T = R - S`.  
`sub [R:reg][S:reg][T:reg]` `0x81-RRSSTT-X`  
`subi [R:reg][S:imm][T:reg]` `0x91-RR00TT-SSSSSSSS`
#### mul
Multiplies two values and writes them to a target register `T = R * S`.  
`mul [R:reg][S:reg][T:reg]` `0x82-RRSSTT-X`  
`muli [R:reg][S:imm][T:reg]` `0x92-RR00TT-SSSSSSSS`
#### and
Bitwise ands two values and writes them to a target register `T = R AND S`.  
`and [R:reg][S:reg][T:reg]` `0x83-RRSSTT-X`  
`andi [R:reg][S:imm][T:reg]` `0x93-RR00TT-SSSSSSSS`
#### or
Bitwise ors two values and writes them to a target register `T = R OR S`.  
`or [R:reg][S:reg][T:reg]` `0x84-RRSSTT-X`  
`ori [R:reg][S:imm][T:reg]` `0x94-RR00TT-SSSSSSSS`
#### not
Bitwise not a value and writes it to a target register `T = NOT R`.  
`not [R:reg][T:reg]` `0x85-RR00TT-X`  
There is no immediate mode for this instruction.
#### xor
Bitwise xors two values and writes them to a target register `T = R XOR S`.  
`xor [R:reg][S:reg][T:reg]` `0x86-RRSSTT-X`  
`xori [R:reg][S:imm][T:reg]` `0x96-RR00TT-SSSSSSSS`
#### xnor
Bitwise xnors two values and writes them to a target register `T = R XNOR S`.  
`xnor [R:reg][S:reg][T:reg]` `0x87-RRSSTT-X`  
`xnori [R:reg][S:imm][T:reg]` `0x97-RR00TT-SSSSSSSS`
#### nor
Bitwise nors two values and writes them to a target register `T = R NOR S`.  
`nor [R:reg][S:reg][T:reg]` `0x88-RRSSTT-X`  
`nori [R:reg][S:imm][T:reg]` `0x98-RR00TT-SSSSSSSS`
#### equals
Compares two signed values and writes the result (0 or 1; 1 is true) to a target register `T = R == S`.  
`ceq [R:reg][S:reg][T:reg]` `0x89-RRSSTT-X`  
`ceqi [R:reg][S:imm][T:reg]` `0x99-RR00TT-SSSSSSSS`
#### less than
Compares two signed values and writes the result (0 or 1; 1 is true) to a target register `T = R < S`.  
`clt [R:reg][S:reg][T:reg]` `0x8A-RRSSTT-X`  
`clti [R:reg][S:imm][T:reg]` `0x9A-RR00TT-SSSSSSSS`
#### less than or equals
Compares two signed values and writes the result (0 or 1; 1 is true) to a target register `T = R <= S`.  
`clte [R:reg][S:reg][T:reg]` `0x8B-RRSSTT-X`  
`cltei [R:reg][S:imm][T:reg]` `0x9B-RR00TT-SSSSSSSS`
#### shift right
Bitwise shifts a value to the right and writes the result to a target register `T = R >> S`.  
`shr [R:reg][S:reg][T:reg]` `0x8C-RRSSTT-X`  
`shri [R:reg][S:imm][T:reg]` `0x9C-RR00TT-000000SS`  
**NOTE**: the value for the shift is limited to one byte, 
therefore any bigger value will be cut down to the least significant byte.
#### shift left
Bitwise shifts a value to the left and writes the result to a target register `T = R << S`.  
`shl [R:reg][S:reg][T:reg]` `0x8D-RRSSTT-X`  
`shli [R:reg][S:imm][T:reg]` `0x9D-RR00TT-000000SS`  
**NOTE**: the value for the shift is limited to one byte,
therefore any bigger value will be cut down to the least significant byte.
#### rotate right
Bitwise rotates a value to the right and writes the result to a target register `T = R rr> S`.  
`rr [R:reg][S:reg][T:reg]` `0x8E-RRSSTT-X`  
`rri [R:reg][S:imm][T:reg]` `0x9E-RR00TT-000000SS`  
**NOTE**: the value for the rotation is limited to one byte,
therefore any bigger value will be cut down to the least significant byte.
#### rotate left
Bitwise rotates a value to the left and writes the result to a target register `T = R <rl S`.  
`rl [R:reg][S:reg][T:reg]` `0x8F-RRSSTT-X`  
`rli [R:reg][S:imm][T:reg]` `0x9F-RR00TT-000000SS`  
**NOTE**: the value for the rotation is limited to one byte,
therefore any bigger value will be cut down to the least significant byte.
___
### IO and memory
___
Writing to IO port and memory works pretty similar. 
It always requires an address calculated from an offset and an immediate value 
as well as some defined target to write or read.

#### load / load word from memory
Reads a 64-bit word from memory using the memory interface.  
The value `M` is located in a reserved register holding the dynamic data-segment pointer and the immediate value is effectively an offset starting at `M`.
The immediate version `lwi` actually loads using a direct memory address instead of using an offset.  
`lw {M:mem}[I:imm][R:reg]` `0x40-MM00RR-IIIIIIII`  
`lwi {0}[I:imm][R:reg]` `0x50-0000RR-IIIIIIII`
#### store / store word to memory
Writes a 64-bit word to memory using the memory interface.  
The value `M` is located in a reserved register holding the dynamic data-segment pointer and the immediate value is effectively an offset starting at `M`.
The immediate version `lwi` actually stores using a direct memory address instead of using an offset.  
`sw {M:mem}[I:imm][R:reg]` `0x41-MM00RR-IIIIIIII`  
`swi {0}[I:imm][R:reg]` `0x51-0000RR-IIIIIIII`
#### io read / read io port data
Reads a 64-bit word and a control bit from an IO device using the IO port interface.  
The 64-bit word will be stored in register `R` and the boolean value will be stored in `S`.  
The immediate value is used as direct address, meaning a value of 1 means targeting device 1.  
`lio [I:imm][R:reg][S:reg]` `0x44-00RRSS-IIIIIIII`  
`lioi [I:imm][R:reg][S:reg]` `0x54-00RRSS-IIIIIIII`
#### io write / write io port data
Writes a 64-bit word and a control bit to an IO device using the IO port interface.  
The 64-bit word will be taken from register `R` and the boolean value will be taken from `S`.  
The immediate value is used as direct address, meaning a value of 1 means targeting device 1.  
`sio {M:mem}[I:imm][R:reg]` `0x45-MM00RR-IIIIIIII`  
`sioi {0}[I:imm][R:reg]` `0x55-0000RR-IIIIIIII`
___
### Call and Return
___
Call and return are used to have function calls, which are essentially branches, that you can return to.  
Its implemented by using the memory and a reserved register holding the stack pointer, which tracks the calls to be able to return.
Both methods don't have an immediate version.
#### call
Calls a function and jumps to its address. The current pc will be saved to the function stack and the stack pointer will be updated (push).  
`call [I:imm]` `0x42-IIIIII-IIIIIIII`  
#### return
Returns from a function and jumps back to its call. The current pc will be overwritten by the top value on the function stack and the stack pointer will be updated (pop).  
`ret` `0x43-X-X`  