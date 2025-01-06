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

## Subpass 1: Jump Label Resolving

Marking the jump labels in functions was the last step in the Lexing step. We are picking up from their and resolving them.
We are doing this by splitting functions into their sections.

So the file's token structure will be broken up as so
```
Whole File
 -functions
	- jump labels
		- instruction expresstions
```