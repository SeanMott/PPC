# PPC
A Game Cube/Wii Power PC ASM to C/C++ Transcompiler

# How Does It Work

Stage 0 || PPC uses [DTK]() to generate the assembly, symbols, and splits.

Stage 1 || The assembly and symbols are analiysed and parsed into a tokens and AST.

Stage 2 || The AST is refined giving objects type data and defined functions.

Stage 3 || Objects are converted into single variables or structs.

Stage 4 || Memory Offsets are resolved and linked to objects and jump addresses.

Stage 5 || Instructions are converted into C code equivalants.