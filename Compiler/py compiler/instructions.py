def create_opcodes(instruction: str, param1: int, param2: int, param3: int):
    instructions: dict = {
        # Unconditional jmp/branch
        "jmp": (0x01, (param1, 7)),
        "b": (0x09, (param1, 7)),
        # Conditional jmp/branch
        "jeq": (0x02, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "beq": (0x0A, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "jneq": (0x03, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "bneq": (0x0B, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "jl": (0x04, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "bl": (0x0C, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "jleq": (0x05, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "bleq": (0x0D, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "jg": (0x06, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "bg": (0x0E, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "jgeq": (0x07, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        "bgeq": (0x0F, (param1, 1), (param2, 1), 0x00, (param3, 4)),
        # With immediate:
        "jeqi": (0x12, (param1, 1), (param3, 2), (param2, 4)),
        "beqi": (0x1A, (param1, 1), (param3, 2), (param2, 4)),
        "jneqi": (0x13, (param1, 1), (param3, 2), (param2, 4)),
        "bneqi": (0x1B, (param1, 1), (param3, 2), (param2, 4)),
        "jli": (0x14, (param1, 1), (param3, 2), (param2, 4)),
        "bli": (0x1C, (param1, 1), (param3, 2), (param2, 4)),
        "jleqi": (0x15, (param1, 1), (param3, 2), (param2, 4)),
        "bleqi": (0x1D, (param1, 1), (param3, 2), (param2, 4)),
        "jgi": (0x16, (param1, 1), (param3, 2), (param2, 4)),
        "bgi": (0x1E, (param1, 1), (param3, 2), (param2, 4)),
        "jgeqi": (0x17, (param1, 1), (param3, 2), (param2, 4)),
        "bgeqi": (0x1F, (param1, 1), (param3, 2), (param2, 4)),

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
