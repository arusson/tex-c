# Section 438

An integer number can be preceded by any number of spaces and '`+`' or '`-`' signs.
Then comes either a decimal constant (i.e., radix 10), an octal constant (i.e., radix 8, preceded by `'`), a hexadecimal constant (radix 16, preceded by `"`), an alphabetic constant (preceded by `` ` ``), or an internal variable.
After scanning is complete, *cur_val* will contain the answer, which must be at most $2^{31} - 1 = 2\,147\,483\,647$ in absolute value.
The value of *radix* is set to 10, 8, or 16 in the cases of decimal, octal, or hexadecimal constants, otherwise *radix* is set to zero.
An optional space follows a constant.

```c include/constants.h
#define OCTAL_TOKEN             (OTHER_TOKEN + '\'') // apostrophe, indicates an octal constant
#define HEX_TOKEN               (OTHER_TOKEN + '"')  // double quote, indicates a hex constant
#define ALPHA_TOKEN             (OTHER_TOKEN + '`')  // reverse apostrophe, precedes alpha constants
#define POINT_TOKEN             (OTHER_TOKEN + '.')  // decimal point
#define CONTINENTAL_POINT_TOKEN (OTHER_TOKEN + ',')  // decimal point, Eurostyle
```

```c << Global variables >>+=
small_number radix; // |scan_int| sets this to 8, 10, 16, or zero
```
