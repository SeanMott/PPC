# PPC
A Game Cube/Wii Power PC ASM to C/C++ Transcompiler

# How Does It Work

Stage 0 || PPC uses [DTK](https://github.com/encounter/decomp-toolkit) to generate the assembly, symbols, and splits.

Stage 1 || The assembly and symbols are analiysed and parsed into a tokens and AST.

Stage 2 || The AST is refined giving objects type data and defined functions.

Stage 3 || Objects are converted into single variables or structs.

Stage 4 || Memory Offsets are resolved and linked to objects and jump addresses.

Stage 5 || Instructions are converted into C code equivalants.

## More Details

For more specific technical specs for how each phase converts the code. Each Stage folder contains a read me holding a rough overview and then the larger break down. PPC is a bit of beast and in order to handle ASM to C. It takes a bit of elbow grease.