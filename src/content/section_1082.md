# Section 1082

Here we deal with things like '`\vsplit 13 to 100pt`'.

```c << Split off part of a vertical box, make |cur_box| point to it >>=
scan_eight_bit_int();
n = cur_val;
if (!scan_keyword("to")) {
    print_err("Missing `to' inserted");
    help2("I'm working on `\\vsplit<box number> to <dimen>';")
        ("will look for the <dimen> next.");
    error();
}
scan_normal_dimen;
cur_box = vsplit(n, cur_val);
```
