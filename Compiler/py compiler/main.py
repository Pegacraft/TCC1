import instructions

test: bytearray = instructions.create_opcodes("cpeq", 1, 2, 3, 4)

text: str = ""
for i in test:
    text += hex(i) + " "

print(text)
