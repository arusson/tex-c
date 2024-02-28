# Section 1155

The *set_math_char* procedure creates a new noad appropriate to a given math code, and appends it to the current mlist.
However, if the math code is sufficiently large, the *cur_chr* is treated as an active character and nothing is appended.

```c math/math_lists.c
void set_math_char(int c) {
    pointer p; // the new noad
    if (c >= 0x8000) {
        // << Treat |cur_chr| as an active character >>
    }
    else {
        p = new_noad();
        math_type(nucleus(p)) = MATH_CHAR;
        character(nucleus(p)) = c % 256;
        fam(nucleus(p)) = (c / 256) % 16;
        if (c >= VAR_CODE) {
            if (fam_in_range) {
                fam(nucleus(p)) = cur_fam;
            }
            type(p) = ORD_NOAD;
        }
        else {
            type(p) = ORD_NOAD + (c / 0x1000);
        }
        link(tail) = p;
        tail = p;
    }
}
```
