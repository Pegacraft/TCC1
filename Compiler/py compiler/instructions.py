def create_opcodes(instruction: str, r: int, s: int, t: int):
    instructions: dict = {
        """
        DICT STRUCTURE
        [opcode name]: tuple
        The tuple can contain an int or an tuple:
           - int: gets appended directly onto the byte array
           - tuple: ([value], [size])
                value: the value that should be appended to the array
                size: how many bytes it will occupy
                example -> (0x01, 2) would return b'\x00\x01'
        """
        # Unconditional jmp/branch
        "jmp": (0x01, (r, 7)),
        "b": (0x09, (r, 7)),
        # Conditional jmp/branch
        "jeq": (0x02, (r, 1), (s, 1), 0x00, (t, 4)),
        "beq": (0x0A, (r, 1), (s, 1), 0x00, (t, 4)),
        "jneq": (0x03, (r, 1), (s, 1), 0x00, (t, 4)),
        "bneq": (0x0B, (r, 1), (s, 1), 0x00, (t, 4)),
        "jl": (0x04, (r, 1), (s, 1), 0x00, (t, 4)),
        "bl": (0x0C, (r, 1), (s, 1), 0x00, (t, 4)),
        "jleq": (0x05, (r, 1), (s, 1), 0x00, (t, 4)),
        "bleq": (0x0D, (r, 1), (s, 1), 0x00, (t, 4)),
        "jg": (0x06, (r, 1), (s, 1), 0x00, (t, 4)),
        "bg": (0x0E, (r, 1), (s, 1), 0x00, (t, 4)),
        "jgeq": (0x07, (r, 1), (s, 1), 0x00, (t, 4)),
        "bgeq": (0x0F, (r, 1), (s, 1), 0x00, (t, 4)),
        # With immediate:
        "jeqi": (0x12, (r, 1), (t, 2), (s, 4)),
        "beqi": (0x1A, (r, 1), (t, 2), (s, 4)),
        "jneqi": (0x13, (r, 1), (t, 2), (s, 4)),
        "bneqi": (0x1B, (r, 1), (t, 2), (s, 4)),
        "jli": (0x14, (r, 1), (t, 2), (s, 4)),
        "bli": (0x1C, (r, 1), (t, 2), (s, 4)),
        "jleqi": (0x15, (r, 1), (t, 2), (s, 4)),
        "bleqi": (0x1D, (r, 1), (t, 2), (s, 4)),
        "jgi": (0x16, (r, 1), (t, 2), (s, 4)),
        "bgi": (0x1E, (r, 1), (t, 2), (s, 4)),
        "jgeqi": (0x17, (r, 1), (t, 2), (s, 4)),
        "bgeqi": (0x1F, (r, 1), (t, 2), (s, 4)),

        # ALU operations
        "add": (0x80, (r, 1), (s, 1), (t, 1), (0, 4)),
        "addi": (0x90, (r, 1), 0x00, (t, 1), (s, 4)),
        "sub": (0x81, (r, 1), (s, 1), (t, 1), (0, 4)),
        "subi": (0x91, (r, 1), 0x00, (t, 1), (s, 4)),
        "mul": (0x82, (r, 1), (s, 1), (t, 1), (0, 4)),
        "muli": (0x92, (r, 1), 0x00, (t, 1), (s, 4)),
        "and": (0x83, (r, 1), (s, 1), (t, 1), (0, 4)),
        "andi": (0x93, (r, 1), 0x00, (t, 1), (s, 4)),
        "or": (0x84, (r, 1), (s, 1), (t, 1), (0, 4)),
        "ori": (0x94, (r, 1), 0x00, (t, 1), (s, 4)),
        "not": (0x85, (r, 1), 0x00, (t, 1), (0, 4)),
        "xor": (0x86, (r, 1), (s, 1), (t, 1), (0, 4)),
        "xori": (0x96, (r, 1), 0x00, (t, 1), (s, 4)),
        "xnor": (0x87, (r, 1), (s, 1), (t, 1), (0, 4)),
        "xnori": (0x97, (r, 1), 0x00, (t, 1), (s, 4)),
        "nor": (0x88, (r, 1), (s, 1), (t, 1), (0, 4)),
        "nori": (0x98, (r, 1), 0x00, (t, 1), (s, 4)),
        "ceq": (0x89, (r, 1), (s, 1), (t, 1), (0, 4)),
        "ceqi": (0x99, (r, 1), 0x00, (t, 1), (s, 4)),
        "clt": (0x8A, (r, 1), (s, 1), (t, 1), (0, 4)),
        "clti": (0x9A, (r, 1), 0x00, (t, 1), (s, 4)),
        "clte": (0x8B, (r, 1), (s, 1), (t, 1), (0, 4)),
        "cltei": (0x9B, (r, 1), 0x00, (t, 1), (s, 4)),
        "shr": (0x8C, (r, 1), (s, 1), (t, 1), (0, 4)),
        "shri": (0x9C, (r, 1), 0x00, (t, 1), (s, 4)),
        "shl": (0x8D, (r, 1), (s, 1), (t, 1), (0, 4)),
        "shli": (0x9D, (r, 1), 0x00, (t, 1), (s, 4)),
        "rr": (0x8E, (r, 1), (s, 1), (t, 1), (0, 4)),
        "rri": (0x9E, (r, 1), 0x00, (t, 1), (s, 4)),
        "rl": (0x8F, (r, 1), (s, 1), (t, 1), (0, 4)),
        "rli": (0x9F, (r, 1), 0x00, (t, 1), (s, 4)),
    }

    instruction_cmd: tuple = instructions.get(instruction)
    opcode: bytearray = bytearray(0)
    for index, item in enumerate(instruction_cmd):
        if type(item) is int:
            opcode.append(item)
        elif byte_len(item[0]) <= item[1]:
            opcode.extend(int.to_bytes(item[0], length=item[1], byteorder="big"))
        else:
            assert False, "Something went wrong"
    return opcode


def byte_len(num: int):
    return int(int.bit_length(num) / 8)


def str_count(t: tuple):
    amount: int = 0
    for item in t:
        amount += 1 if type(item) == str else 0
    return amount
