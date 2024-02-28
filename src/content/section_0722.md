# Section 722

It is convenient to have a procedure that converts a *MATH_CHAR* field to an "unpacked" form.
The *fetch* routine sets *cur_f*, *cur_c*, and *cur_i* to the font code, character code, and character information bytes of a given noad field.
It also takes care of issuing error messages for nonexistent characters; in such cases, *char_exists(cur_i)* will be *false* after *fetch* has acted, and the field will also have been reset to *EMPTY*.

```c math/math_typesetting.c
// unpack the |MATH_CHAR| field |a|
void fetch(pointer a) {
    cur_c = character(a);
    cur_f = fam_fnt(fam(a) + cur_size);
    if (cur_f == NULL_FONT) {
        // << Complain about an undefined family and set |cur_i| null >>
    }
    else {
        if (cur_c >= font_bc[cur_f] && cur_c <= font_ec[cur_f]) {
            cur_i = char_info(cur_f, cur_c);
        }
        else {
            cur_i = null_character;
        }
        if (!char_exists(cur_i)) {
            char_warning(cur_f, cur_c);
            math_type(a) = EMPTY;
            cur_i = null_character;
        }
    }
}
```
