# Section 557

Here are some macros that help process ligatures and kerns.
We write *char_kern(f)(j)* to find the amount of kerning specified by kerning command&nbsp;*j* in font&nbsp;*f*.
If *j* is the *char_info* for a character with a ligature/kern program, the first instruction of that program is either *i = font_info[lig_kern_start(f)(j)]* or *font_info[lig_kern_restart(f)(i)]*, depending on whether or not *skip_byte(i)* $\leq$ *STOP_FLAG*.

The constant *KERN_BASE_OFFSET* should be simplified, for Pascal compilers that do not do local optimization.

```c include/constants.h
#define KERN_BASE_OFFSET 256*(128 + MIN_QUARTERWORD)
```

```c include/font_metric.h
#define char_kern(X,Y)        (font_info[kern_base[X] + 256*op_byte((Y)) + rem_byte((Y))].sc)
// beginning of lig/kern program:
#define lig_kern_start(X,Y)   (lig_kern_base[(X)] + rem_byte((Y))) 
#define lig_kern_restart(X,Y) (lig_kern_base[(X)] + 256*op_byte((Y)) + rem_byte((Y)) + 32768 - KERN_BASE_OFFSET)
```
