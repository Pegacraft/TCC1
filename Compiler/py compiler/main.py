import array
import instructions
import lexer

file_path: str = 'file.code'
with open(file_path, 'r') as input:
    with open('a.bin', 'w+b') as output:
        if_statements: list = ()
        loops: list = ()
        word: str = "ioread"
        output.write(lexer.io_instructions(word,2,3,4))