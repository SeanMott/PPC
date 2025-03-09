#removes @ symbols in a DTK symbols.txt so we don't deal with annoying "" names

import sys

symbolsFile = sys.argv[1]

with open(symbolsFile, 'r', encoding='utf-8') as file:
    lines = file.readlines()
    modified_lines = [line.replace('@', 'AT_', 1) if line.startswith('@') else line for line in lines]

with open(symbolsFile, 'w', encoding='utf-8') as file:
    file.writelines(modified_lines)