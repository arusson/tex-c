# Section 1225

```c << Assignments >>+=
case READ_TO_CS:
    scan_int();
    n = cur_val;
    if (!scan_keyword("to")) {
        print_err("Missing `to' inserted");
        help2("You should have said `\\read<number> to \\cs'.")
            ("I'm going to look for the \\cs now.");
        error();
    }
    get_r_token();
    p = cur_cs;
    read_toks(n, p);
    define(p, CALL, cur_val);
    break;
```
