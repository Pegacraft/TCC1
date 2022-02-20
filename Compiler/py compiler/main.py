import instructions

test: bytearray = instructions.create_opcodes("jli", 1, 2, 3)

for i in test:
    print(hex(i))
