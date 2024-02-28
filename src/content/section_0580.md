# Section 580

```c << Increase the number of parameters in the last font >>=
do {
    if (fmem_ptr == FONT_MEM_SIZE) {
        overflow("font memory", FONT_MEM_SIZE);
    }
    font_info[fmem_ptr].sc = 0;
    incr(fmem_ptr);
    incr(font_params[f]);
} while (n != font_params[f]);
cur_val = fmem_ptr - 1; // this equals |param_base[f] + font_params[f]|
```
