# Section 403

The *scan_left_brace* routine is called when a left brace is supposed to be the next non-blank token.
(The term "left brace" means, more precisely, a character whose catcode is *LEFT_BRACE*.)
$\TeX$ allows `\relax` to appear before the *LEFT_BRACE*.

```c parser/subroutines.c
// << Start file |subroutines.c| >>

// reads a mandatory |LEFT_BRACE|
void scan_left_brace() {
    // << Get the next non-blank non-relax non-call token >>
    if (cur_cmd != LEFT_BRACE) {
        print_err("Missing { inserted");
        help4("A left brace was mandatory here, so I've put one in.")
            ("You might want to delete and/or insert some corrections")
            ("so that I will find a matching right brace soon.")
            ("(If you're confused by all this, try typing `I}' now.)");
        back_error();
        cur_tok = LEFT_BRACE_TOKEN + '{';
        cur_cmd = LEFT_BRACE;
        cur_chr = '{';
        incr(align_state);
    }
}
```
