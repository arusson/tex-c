# Section 1183

```c << Ignore the fraction operation and complain about this ambiguous case >>=
if (c >= DELIMITED_CODE) {
    scan_delimiter(GARBAGE, false);
    scan_delimiter(GARBAGE, false);
}
if (c % DELIMITED_CODE == ABOVE_CODE) {
    scan_normal_dimen;
}
print_err("Ambiguous; you need another { and }");
help3("I'm ignoring this fraction specification, since I don't")
    ("know whether a construction like `x \\over y \\over z'")
    ("means `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
error();
```
