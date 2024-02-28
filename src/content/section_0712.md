# Section 712

Another handy subroutine computes the height plus depth of a given character:

```c << Declare subprocedures for |var_delimiter| >>+=
scaled height_plus_depth(internal_font_number f, quarterword c) {
    memory_word q;
    eight_bits hd; // |height_depth| byte
    q = char_info(f, c);
    hd = height_depth(q);
    return char_height(f, hd) + char_depth(f, hd);
}
```
