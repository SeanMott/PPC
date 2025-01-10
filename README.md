# PPC
A Game Cube/Wii Power PC ASM to C/C++ Transcompiler

# How Does It Work

Phase 0 || PPC uses [DTK](https://github.com/encounter/decomp-toolkit) to generate the assembly, symbols, and splits.

Phase 1 || Each Assembly file is lexed and a token stream of every Object and Function is generated

Phase 2 || Objects are typed and resolved into either Struct, Skip_Reserves, String or Digit Literals.

Phase 3 || Memeory offsets into Objects are resolved.

Phase 4 || C/C++ Code is emitted into files.

## More Details

For more specific technical specs for how each phase converts the code. Each Stage and Phase folder contains a read me holding a rough overview and then the larger break down. PPC is a bit of beast and in order to handle ASM to C. It takes a bit of elbow grease.