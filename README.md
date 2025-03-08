# PPC
A Game Cube/Wii Power PC ASM to C/C++ Transcompiler/Static Recompiler.

## What Makes This Different From Decompiling?

Decompiling takes a ROM and splits it out into Assembly, then people convert it back into the C/C++. The end goal being a byte for byte accurate ROM.

PPC also takes a ROM and converts it to Assembly (even using the same tools they do [DTK]()). But then converts that Assembly into C++ that can be compiled into a native binary for other platforms.

## How Does This Work?

Taking inspiration from the [N64 Static Recompiler]() and wanting to initally make a tool to name DTK Assembly automatically. It first splits the ROM into assembly using DTK. Parses the Assembly and Symbols outputted by DTK. It then goes instruction by instruction and emitts C++ that emulates the functionality. Akin to a emulator by done ahead of time.

This outputted code still requires a library to fill in the functionality. This is the [PPCRuntime](). If other runtimes are developed (likly for the other SDK versions), they can used instead.

## Who Has Used This?

While this tool is developed, Tower of Druga and Kirby Air Ride are used as the test cases. Their recomps and PPC assisted decomps are a work in progress.

- [Tower Of Druga Recomp]()
- [Tower Of Druga PPC Assisted Decomp]()

<br/>

- [Kirby Air Ride Recomp]()
- [Kirby Air Ride PPC Assisted Decomp]()

## How Can I Use This In My Own Project?

1. Grab the latest [Release]()

... Add more here.

## What If I Want **ALL** The Details?

Every header in a Stage will have a breakdown of how it works. So in PPCAnalyse, the ASM/Stage1/Stage1_Defining.hpp will have a massive comment describing the stage. And so will the others.

A mark down file will also be inside the folder giving the same explanation but with source code examples.