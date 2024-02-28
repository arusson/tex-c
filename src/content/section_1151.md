# Section 1151

Recall that the *nucleus*, *subscr*, and *supscr* fields in a noad are broken down into subfields called *math_type* and either *info* or *(fam, character)*.
The job of *scan_math* is to figure out what to place in one of these principal fields; it looks at the subformula that comes next in the input, and places an encoding of that subformula into a given word of *mem*.

```c include/texmath.h
#define fam_in_range (cur_fam >= 0 && cur_fam < 16)
```

```c math/math_lists.c
void scan_math(pointer p) {
    int c; // math character code

restart:
    // << Get the next non-blank non-relax non-call token >>

reswitch:
    switch (cur_cmd) {
    case LETTER:
    case OTHER_CHAR:
    case CHAR_GIVEN:
        c = ho(math_code(cur_chr));
        if (c == 0x8000) {
            // << Treat |cur_chr| as an active character >>
            goto restart;
        }
        break;
    
    case CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        cur_cmd = CHAR_GIVEN;
        goto reswitch;
    
    case MATH_CHAR_NUM:
        scan_fifteen_bit_int();
        c = cur_val;
        break;
    
    case MATH_GIVEN:
        c = cur_chr;
        break;
    
    case DELIM_NUM:
        scan_twenty_seven_bit_int();
        c = cur_val / 0x1000;
        break;
    
    default:
        // << Scan a subformula enclosed in braces and |return| >>
    }
    math_type(p) = MATH_CHAR;
    character(p) = c % 256;
    if (c >= VAR_CODE && fam_in_range) {
        fam(p) = cur_fam;
    }
    else {
        fam(p) = (c / 256) % 16;
    }
}
```
