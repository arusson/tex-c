# Section 1248

Paragraph shapes are set up in the obvious way.

```c << Assignments >>+=
case SET_SHAPE:
    scan_optional_equals();
    scan_int();
    n = cur_val;
    if (n <= 0) {
        p = null;
    }
    else {
        p = get_node(2*n + 1);
        info(p) = n;
        for(j = 1; j <= n; j++) {
            scan_normal_dimen;
            mem[p + 2*j - 1].sc = cur_val; // indentation
            scan_normal_dimen;
            mem[p + 2*j].sc = cur_val; // width
        }
    }
    define(PAR_SHAPE_LOC, SHAPE_REF, p);
    break;
```
