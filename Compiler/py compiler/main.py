import instructions

test: bytearray = instructions.create_opcodes("cpeq", 1, 2, 3, 4)

text: str = ""
for i in test:
    text += hex(i) + " "
#with open('a.bin', 'w+b') as f:
    #f.write(test)
print(text)
