# Section 545

The *lig_kern* array contains instructions in a simple programming language that explains what to do for special letter pairs.
Each word in this array is a *lig_kern_command* of four bytes.

- first byte: *skip_byte*, indicates that this is the final program
  step if the byte is 128 or more, otherwise the next step is obtained by
  skipping this number of intervening steps.

- second byte: *next_char*, "if *next_char* follows the current character,
  then perform the operation and stop, otherwise continue.

- third byte: *op_byte*, indicates a ligature step if less than&nbsp;128,
  a kern step otherwise.

- fourth byte: *remainder*.

In a kern step, an additional space equal to *kern[256\*(op_byte − 128) + remainder]* is inserted between the current character and *next_char*.
This amount is often negative, so that the characters are brought closer together by kerning; but it might be positive.

There are eight kinds of ligature steps, having *op_byte* codes *4a + 2b + c* where *0* $\leq$ *a* $\leq$ *b + c* and *0* $\leq$ *b*,*c* $\leq$ *1*.
The character whose code is *remainder* is inserted between the current character and *next_char*;
then the current character is deleted if *b = 0*, and *next_char* is deleted if *c = 0*; then we pass over *a*&nbsp;characters to reach the next current character (which may have a ligature/kerning program of its own).

If the very first instruction of the *lig_kern* array has *skip_byte = 255*, the *next_char* byte is the so-called boundary character of this font;
the value of *next_char* need not lie between *bc* and&nbsp;*ec*.
If the very last instruction of the *lig_kern* array has *skip_byte = 255*, there is a special ligature/kerning program for a boundary character at the left, beginning at location *256\*op_byte + remainder*.
The interpretation is that $\TeX$ puts implicit boundary characters before and after each consecutive string of characters from the same font.
These implicit characters do not appear in the output, but they can affect ligatures and kerning.

If the very first instruction of a character's *lig_kern* program has *skip_byte* $>$ *128*, the program actually begins in location *256\*op_byte + remainder*.
This feature allows access to large *lig_kern* arrays, because the first instruction must otherwise appear in a location $\leq$ *255*.

Any instruction with *skip_byte* $>$ *128* in the *lig_kern* array must satisfy the condition

<div align="center">

256 \* *op_byte* + *remainder* $<$ *nl*.
</div>

If such an instruction is encountered during normal program execution, it denotes an  unconditional halt; no ligature or kerning command is performed.

```c include/constants.h
#define STOP_FLAG 128 // value indicating 'STOP' in a lig/kern program
#define KERN_FLAG 128 // op code for a kern step
```

```c include/font_metric.h
// << Start file |font_metric.h| >>

#define skip_byte(X) qqqq_b0((X))
#define next_char(X) qqqq_b1((X))
#define op_byte(X)   qqqq_b2((X))
#define rem_byte(X)  qqqq_b3((X))
```
