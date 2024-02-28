# Section 1232

The different types of code values have different legal ranges; the following program is careful to check each case properly.

```c << Assignments >>+=
case DEF_CODE:
    // << Let |n| be the largest legal code value, based on |cur_chr| >>
    p = cur_chr;
    scan_char_num();
    p += cur_val;
    scan_optional_equals();
    scan_int();
    if ((cur_val < 0 && p < DEL_CODE_BASE) || cur_val > n) {
        print_err("Invalid code (");
        print_int(cur_val);
        if (p < DEL_CODE_BASE) {
            print("), should be in the range 0..");
        }
        else {
            print("), should be at most ");
        }
        print_int(n);
        help1("I'm going to use 0 instead of that illegal code value.");
        error();
        cur_val = 0;
    }
    if (p < MATH_CODE_BASE) {
        define(p, DATA, cur_val);
    }
    else if (p < DEL_CODE_BASE) {
        define(p, DATA, hi(cur_val));
    }
    else {
        word_define(p, cur_val);
    }
    break;
```
