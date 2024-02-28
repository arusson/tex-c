# Section 1165

```c math/math_lists.c
void math_ac() {
    if (cur_cmd == ACCENT) {
        // << Complain that the user should have said \mathaccent >>
    }
    tail_append(get_node(ACCENT_NOAD_SIZE));
    type(tail) = ACCENT_NOAD;
    subtype(tail) = NORMAL;
    mem[nucleus(tail)] = empty_field;
    mem[subscr(tail)] = empty_field;
    mem[supscr(tail)] = empty_field;
    math_type(accent_chr(tail)) = MATH_CHAR;
    scan_fifteen_bit_int();
    character(accent_chr(tail)) = cur_val % 256;
    if (cur_val >= VAR_CODE && fam_in_range) {
        fam(accent_chr(tail)) = cur_fam;
    }
    else {
        fam(accent_chr(tail)) = (cur_val / 256) % 16;
    }
    scan_math(nucleus(tail));
}
```
