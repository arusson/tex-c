# Section 1176

```c math/math_lists.c
void sub_sup() {
    small_number t; // type of previous sub/superscript
    pointer p;      // field to be filled by |scan_math|
    t = EMPTY;
    p = null;
    if (tail != head && scripts_allowed(tail)) {
        p = supscr(tail) + cur_cmd - SUP_MARK; // |supscr| or |subscr|
        t = math_type(p);
    }
    if (p == null || t != EMPTY) {
        // << Insert a dummy noad to be sub/superscripted >>
    }
    scan_math(p);
}
```
