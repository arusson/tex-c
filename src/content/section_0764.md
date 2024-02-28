# Section 764

The inter-element spacing in math formulas depends on an 8$\times$8 table that $\TeX$ preloads as a 64-digit string.
The elements of this string have the following significance:

<div align="center">
<div style="text-align: left; max-width: 80%; display: inline-block;">

`0` means no space;<br>
`1` means a conditional thin space (`\nonscript\mskip\thinmuskip`);<br>
`2` means a thin space (`\mskip\thinmuskip`);<br>
`3` means a conditional medium space (`\nonscript\mskip\medmuskip`);<br>
`4` means a conditional thick space (`\nonscript\mskip\thickmuskip`);<br>
`*` means an impossible case.
</div>
</div>

This is all pretty cryptic, but *The TeXbook* explains what is supposed to happen, and the string makes it happen.

A global variable *magic_offset* is computed so that if *a* and *b* are in the range *ORD_NOAD .. INNER_NOAD*, then *str_pool[a\*8 + b + magic_offset]* is the digit for spacing between noad types *a* and *b*.

If Pascal had provided a good way to preload constant arrays, this part of the program would not have been so strange.

> ![NOTE]
> We can define without any problem a constant array in C, so the *magic_offset* global variable is not needed.
> 
> Written in capital since it is a *const*, and not in `global.c` because it is used only in `math_typesetting.c`.

```c << Declare |MATH_SPACING| for |mlist_to_hlist| >>=
const char *MATH_SPACING = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";
```
