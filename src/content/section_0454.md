# Section 454

A specification like '`filllll`' or '`fill L L L`' will lead to two error messages (one for each additional keyword `"l"`).

```c << Scan for |fil| units; |goto attach_fraction| if found >>=
if (scan_keyword("fil")) {
    cur_order = FIL;
    while (scan_keyword("l")) {
        if (cur_order == FILLL) {
            print_err("Illegal unit of measure (");
            print("replaced by filll)");
            help1("I dddon't go any higher than filll.");
            error();
        }
        else {
            incr(cur_order);
        }
    }
    goto attach_fraction;
}
```
