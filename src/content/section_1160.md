# Section 1160

Delimiter fields of noads are filled in by the *scan_delimiter* routine.
The first parameter of this procedure is the *mem* address where the delimiter is to be placed; the second tells if this delimiter follows `\radical` or not.

```c math/math_lists.c
void scan_delimiter(pointer p, bool r) {
    if (r) {
        scan_twenty_seven_bit_int();
    }
    else {
        // << Get the next non-blank non-relax non-call token >>
        switch (cur_cmd) {
        case LETTER:
        case OTHER_CHAR:
            cur_val = del_code(cur_chr);
            break;
        
        case DELIM_NUM:
            scan_twenty_seven_bit_int();
            break;
        
        default:
            cur_val = -1;
        }
    }
    if (cur_val < 0) {
        // << Report that an invalid delimiter code is being changed to null; set |cur_val = 0| >>
    }
    small_fam(p) = (cur_val / 0x100000) % 16;
    small_char(p) = (cur_val / 0x1000) % 256;
    large_fam(p) = (cur_val / 256) % 16;
    large_char(p) = cur_val % 256;
}
```
