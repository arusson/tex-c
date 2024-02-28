# Section 1288

```c builder/independent.c
void shift_case() {
    pointer b;    // |lc_code_base| or |uc_code_base|
    pointer p;    // runs through the token list
    halfword t;   // token
    eight_bits c; // character code
    
    b = cur_chr;
    p = scan_toks(false, false);
    p = link(def_ref);
    while (p != null) {
        // << Change the case of the token in |p|, if a change is appropriate >>
        p = link(p);
    }
    back_list(link(def_ref));
    free_avail(def_ref); // omit reference count
}
```
