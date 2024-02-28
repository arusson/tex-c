# Section 1218

When a *DEF* command has been scanned, *cur_chr* is odd if the definition is supposed to be global, and *cur_chr* $\geq$ *2* if the definition is supposed to be expanded.

```c << Assignments >>+=
case DEF:
    if (odd(cur_chr)
        && !global
        && global_defs >= 0)
    {
        a += 4;
    }
    e = (cur_chr >= 2);
    get_r_token();
    p = cur_cs;
    q = scan_toks(true, e);
    define(p, CALL + (a % 4), def_ref);
    break;
```
