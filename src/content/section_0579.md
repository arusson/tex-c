# Section 579

```c << Issue an error message if |cur_val = fmem_ptr| >>=
if (cur_val == fmem_ptr) {
    print_err("Font ");
    print_esc_strnumber(font_id_text(f));
    print(" has only ");
    print_int(font_params[f]);
    print(" fontdimen parameters");
    help2("To increase the number of font parameters, you must")
        ("use \\fontdimen immediately after the \\font is loaded.");
    error();
}
```
