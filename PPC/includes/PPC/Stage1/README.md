# Stage 1

This is the first stage of converting a ROM into C++. Taking the assembly and breaking it down into tokens and making sense of all the text.

The most common file DTK generates is the C++ init exception file. This file is used for initalizing exceptions in C++ on the Game Cube.

__init_cpp_exceptions.s taken from Tower Of Druga
```
.include "macros.inc"
.file "__init_cpp_exceptions.cpp"

# 0x8002DE40..0x8002DE44 | size: 0x4
.section .dtors, "a"
.balign 4

# .dtors:0x0 | 0x8002DE40 | size: 0x4
.obj __destroy_global_chain_reference, global
	.4byte __destroy_global_chain
.endobj __destroy_global_chain_reference
```

breaking this down by what tokens we get.

```
.include "macros.inc"
```
.include is a Keyword token
"macros.inc" is a String Literal token

`# 0x8002DE40..0x8002DE44 | size: 0x4` is a MetaData Comment, theses are differant from normal comments or Block Comments (/**/)
Since we keep it around for readability and the end user having data, not for any specific token parsing

```
.balign 4
```
.balign is a Keyword
4 is a Digit Literal

And so on and so on, breaking each of the words into token types and building our understanding of the file.
Each Keyword is has a more specific type of keyword as well. We use that for type generation and eventually building the C code.

```
.4byte __destroy_global_chain
```
.4byte is a Keyword but is a Datatype. We then know that inside the __destroy_global_chain_reference Object. We have a single datatype.
In this case it is a pointer, but as far as the compiler is concerned, right now it is just a Anything Datatype.
We will make this a void* later when we give it more context and processing.

For a full list of [Tokens]("TokenSpec.md") and the [Token Source Code]("Token.hpp")