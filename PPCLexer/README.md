# Stage 1

After the ROM has been split out into assembly and symbol data (See Stage 0). We can begin the process of converting it to C++.

Stage 1 is all about lexing the raw code into tokens we can later use to generate a accurate AST of the program.
Each Token tells a bit about the program. Using theses we can know how to assemble the C++.

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

For a full list of [Tokens]("TokenSpec.md") and the Token Source Code 
[header]("Token.hpp") || [source]("Token.cpp")

## Technical details

This goes into more details breaking down the "subpasses" inside the Stage 1 for lexing. 
As PPC may be a one pass transcompiler, internally, each stage breaks it down into passes to make it easier.

## Subpass 1: Genaric Token Splits

The first subpass breaks the entire file into Genaric Tokens. This skips any spaces and tabs not in comments or strings.
Theses tokens just store the raw text data and line count it was found one, and the char position value in the entire file that started the Genaric Token.
Go to the [header]("Token.hpp") to see the Token struct. This struct is re-used for theses Genaric Tokens and the special Tokens.

The total types of Tokens generated during this subpass is 
the Genaric Token, Single and Block Comments, Operators, New Line, String Literal, Func Start, Func End, Object Start, and Object End Token.

We sort out String Literals and Operators, since they're the easiest to define at this stage. Since we're not concerning ourselves on every keywords.

Single and Block Comments only hold data that would be useful to someone reading the code. So we can ignore them, the only useful one we need is the invalid comment generated.
The comments are not discarded though, we will bring them into the sudo-C and typed ASM stages. So some of the structure can be perserved.
But in the event we are doing a straight shot from ASM to C. We can ignore all the extra comments.

New Lines are handy in place of semi-colons and let us know the end of statments.

From Tower of Druga || auto_05_8002E140_data.s
```
# .data:0x18D8C | 0x80046ECC | size: 0x23
.obj "@74_80046ECC", global
	.string "FPU-unavailable handler installed\n"
.endobj "@74_80046ECC"
```
The "@74_80046ECC" has a comma after it.

From Tower of Druga || auto_01_800056A0_text.s
```
/* 8000597C 0000297C  39 8C 00 08 */	addi r12, r12, 0x8
```
The addi has a Register Comma Register Comma Hex_Literal in that order. We parse out the commas so we know it's a series of valid parameters.
We will use that later to generate the sudo-C when putting the parameters in the proper order.

From Tower of Druga || auto_04_8002DE60_rodata.s
```
# .rodata:0x8 | 0x8002DE68 | size: 0x10
.obj lbl_8002DE68, global
	.byte 0x1E, 0xB4, 0x0F, 0x48, 0x28, 0x0F, 0x3B, 0x1F
	.byte 0x38, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.endobj lbl_8002DE68
```
.byte 0x1E, 0xB4, 0x0F, 0x48, 0x28, 0x0F, 0x3B, 0x1F is going to be treated as a array. We mark the commas so we parse it as such later

The .obj denotes the start of the object and .endobj denotes the end. We define theses now alongside the other func keywords. So we can sort the tokens into groups.
Once grouped we can throw them into threads to speed up the trans pipeline.

## Subpass 2: Keywords and fine typing

After all the strings and operators are parsed out. We now mark all the keywords, datatypes, registers, instructions, digit literals. Anything else is a Identifier.

We do this now since we have weeded out the annoying types to parse if we had to deal with strings and comments. So now we apply the fine typing for each.
This retroactivly sets the types for what were initally the Genaric tokens to their specific typing.

## Subpass 3: Remove Invalid Instructions And Section Info

DTK generates the same line anytime it runs into something invalid

From Tower Of Druga || auto_00_80003100_init.s
```
/* 800052A8 000022A8  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052AC 000022AC  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052B0 000022B0  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052B4 000022B4  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052B8 000022B8  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052BC 000022BC  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052C0 000022C0  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052C4 000022C4  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052C8 000022C8  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052CC 000022CC  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052D0 000022D0  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052D4 000022D4  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052D8 000022D8  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052DC 000022DC  00 00 00 00 */	.4byte 0x00000000 /* invalid */
/* 800052E0 000022E0  00 00 00 00 */	.4byte 0x00000000 /* invalid */
```
Thanks to the earlier subpasses, we the format for this is always Block Comment, Datatype, Hex Literal, Block Comment, New Line.
We do a final check in the tree where groups of theses Tokens are checked. Always if the second Block Comment spelles out " invalid ".
If so, we strip it out.

We also strip out any of the extra section data we don't need. This is becues the compiler doesn't need to parse it from the file.

From Tower Of Druga || __init_cpp_exceptions.s
```
.include "macros.inc"
.file "__init_cpp_exceptions.cpp"

# 0x8002DE40..0x8002DE44 | size: 0x4
.section .dtors, "a"
.balign 4
```
All theses .sections and .file parts can be removed. The comments are a optional extra subpass we can remove.
The reason is when the DTK symbol file is processed, it provides us with all the section and size and type info we need.

## Subpass 4: Jump Labels

Now that everything has been marked and we have all the extra metadata we need.
We can retroactivly go back through the tree and specify jump labels.

Jump Labels are simple as they are just a Identifier followed by a :

From Tower Of Druga || auto_00_80003100_init.s
```
.L_800055D4:
/* 800055D4 000025D4  3C 80 80 00 */	lis r4, gTRKInterruptVectorTable@ha
```

The .L_800055D4: is a Jump Label definition. .L_800055D4 is our label that will be invoked in the function. 
While the : marks it as the start, going untill the next label, or end of function.

## Subpass 5: Comment Pruning

Now we prune any of the block and single line comments. Since they have fulfilled their usefulness. They are just tree bloat if we were to keep them.

## Subpass 6: Expresstion Splitting

Now that we have the metadata. We can now split every line into it's own expresstion list of tokens.
Each line will be treated as it's own self contained expresstion later on when converting to C++.

This also gets rid of the last of the bloating tokens found in newlines. All we care about is the stream of parsing.