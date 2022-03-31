import instructions
import os

def decode(word:str):
    word = word.replace("\n", "")
    dec_text :list = (word.split(" "))
    return(dec_text)

def is_int(s:str):
    try:
        int(s)
        return(True)
    except(ValueError):
        pass
    return(False)


file_path: str = "file.code"

jump_or_branch :tuple = ("jmp", "b", "jeq",
"beq", "jneq", "bneq", "jl", "bl", "jleq",
"bleq", "jg", "bg", "jgeq", "bgeq", "jeqi",
"beqi", "jneqi", "bneqi", "jli", "bli",
"jleqi", "bleqi", "jgi", "bgi", "jgeqi", "bgeqi")

with open(file_path, 'r') as input:
    with open('a.bin', 'w+b') as output:
        EOF :bool = False
        line_num :int = 0
        constants :dict = {}
        labels :dict = {}
        text :str = ""
        dec_text :list = []

        while(EOF == False):

            text = input.readline()
            if (text == ""):
                EOF = True
            elif (text[0] == "\n" or "#" in text):
                continue
            else:
                dec_text = decode(text)
                if (dec_text[0] == "constant" or dec_text[0] == "const"):
                    constants[dec_text[1]] = dec_text[2]
                elif (dec_text[0] == "label"):
                    labels[dec_text[1]] = line_num
                else:
                    #print(str(dec_text) + str(line_num))
                    line_num += 1
            
                l :bool = False
                line :list = []
                for i in dec_text:

                    if (l == True):
                        l = False                    
                        line.append(i)
                    elif (i in jump_or_branch):
                        l = True
                        line.append(i)
                    else:
                        line.append(i)
                print(line)

print("constants = " + str(constants))
print("labels = " + str(labels))