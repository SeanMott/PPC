# Stage 2 || IR

Now that we have a breakdown of every token. Now we can start to generate IR. This is the same way languages like C, C#, Rust, ect.
Convert their higher level language to Assembly. In our case, we're going backwards. Instead of unwrapping a statment like
```
int a = 43;
a += 232332;
float j = a / 2.0f;
```
into Assembly. We're taking it's Assembly and turning it back into that statment.

Like how lexing was split into sub-passes. So is our IR Generation.


## Subpass 1: Function and Struct Bound Checking

This subpass focuses is a simple sweep of the tokens. Converting them into the hard defined objects of Structs and Functions.

From Tower of Druga || auto_01_800056A0_text.s
```
.fn __save_gpr, global
# .text:0x1C3B4 | 0x80021A54 | size: 0x0
.sym _savegpr_14, global
/* 80021A54 0001EA54  91 CB FF B8 */	stw r14, -0x48(r11)
# .text:0x1C3B8 | 0x80021A58 | size: 0x0
.sym _savegpr_15, global
/* 80021A58 0001EA58  91 EB FF BC */	stw r15, -0x44(r11)
# .text:0x1C3BC | 0x80021A5C | size: 0x0
.sym _savegpr_16, global
/* 80021A5C 0001EA5C  92 0B FF C0 */	stw r16, -0x40(r11)
# .text:0x1C3C0 | 0x80021A60 | size: 0x0
.sym _savegpr_17, global
/* 80021A60 0001EA60  92 2B FF C4 */	stw r17, -0x3c(r11)
```

From Tower of Druga || auto_08_8004FAF0_sbss.s
```
.obj PauseFlag_8004FB1C, global
	.skip 0x4
.endobj PauseFlag_8004FB1C
```

.fn <name>, <scope>

and

.obj <name>, <scope>

Are condensed into a single Function Definition Node or Struct Definition Node. Everything between them and the end is made childeren of this node.

All the inside Line Expresstions are flagged using the starting Token.

.hidden are stripped out entirly

any jump labels are converted into Jump Labal Def Nodes. Turning any of their code inside them into their child Expresses.

Any .sym are turned into Sym Jump Address Tokens

Any Instructions turn their entire line into a Instruction Node

Any Datatypes are turned into Datatype Def Tokens

Anything else it can't parse is turned into a Unknown Express. Theses are later dumped into the C++ code as comments so we can debug.