# Section 1154

The simplest math formula is, of course, '`$ $`', when no noads are generated.
The next simplest cases involve a single character, e.g., '`$x$`'.
Even though such cases may not seem to be very interesting, the reader can perhaps understand how happy the author was when '`$x$`' was first properly typeset by $\TeX$.
The code in this section was used.

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + LETTER:
case MMODE + OTHER_CHAR:
case MMODE + CHAR_GIVEN:
    set_math_char(ho(math_code(cur_chr)));
    break;

case MMODE + CHAR_NUM:
    scan_char_num();
    cur_chr = cur_val;
    set_math_char(ho(math_code(cur_chr)));
    break;

case MMODE + MATH_CHAR_NUM:
    scan_fifteen_bit_int();
    set_math_char(cur_val);
    break;

case MMODE + MATH_GIVEN:
    set_math_char(cur_chr);
    break;

case MMODE + DELIM_NUM:
    scan_twenty_seven_bit_int();
    set_math_char(cur_val / 0x1000);
    break;
```
