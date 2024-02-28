# Section 652

```c << Make node |p| look like a |CHAR_NODE| and |goto reswitch| >>=
mem[LIG_TRICK] = mem[lig_char(p)];
link(LIG_TRICK) = link(p);
p = LIG_TRICK;
goto reswitch;
```
