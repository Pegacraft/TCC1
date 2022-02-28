import instructions

def io_instructions(word:str , val1: int, val2:int, address:int):
    if (word == "ioread"):
            return(instructions.create_opcodes("lio", val1, val2, 0, address))
    elif (word == "iowrite"):
            return(instructions.create_opcodes("sio", val1, val2, 0, address))
    elif (word == "print"):
            return(instructions.create_opcodes("sio", val1, val2, 0, 4))

def loop()
