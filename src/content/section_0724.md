# Section 724

The outputs of *fetch* are placed in global variables.

```c << Global variables >>+=
internal_font_number cur_f; // the |font| field of a |MATH_CHAR|
quarterword cur_c;          // the |character| field of a |MATH_CHAR|
memory_word cur_i;          // the |char_info| of a |MATH_CHAR|, or a lig/kern instruction
```
