# Section 578

The following routine is used to implement '`\fontdimen` *n f'*.
The boolean parameter *writing* is set *true* if the calling program intends to change the parameter value.

```c << Declare procedures that scan font-related stuff >>+=
// sets |cur_val| to |font_info| location
void find_font_dimen(bool writing) {
    internal_font_number f;
    int n; // the parameter number
    scan_int();
    n = cur_val;
    scan_font_ident();
    f = cur_val;
    if (n <= 0) {
        cur_val = fmem_ptr;
    }
    else {
        if (writing && n <= SPACE_SHRINK_CODE && n >= SPACE_CODE && font_glue[f] != null) {
            delete_glue_ref(font_glue[f]);
            font_glue[f] = null;
        }
        if (n > font_params[f]) {
            if (f < font_ptr) {
                cur_val = fmem_ptr;
            }
            else {
                // << Increase the number of parameters in the last font >>
            }
        }
        else {
            cur_val = n + param_base[f];
        }
    }
    // << Issue an error message if |cur_val = fmem_ptr| >>
}
```
