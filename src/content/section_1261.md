# Section 1261

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case SET_FONT:
    print("select font ");
    slow_print(font_name[chr_code]);
    if (font_size[chr_code] != font_dsize[chr_code]) {
        print(" at ");
        print_scaled(font_size[chr_code]);
        print("pt");
    }
    break;
```
