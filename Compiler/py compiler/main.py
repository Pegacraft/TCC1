import instructions

test: bytearray = instructions.create_opcodes("clti", 1, 2, 3)

text: str = ""
for i in test:
    text += hex(i) + " "

print(text)
