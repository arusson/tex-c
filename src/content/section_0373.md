# Section 373

```c << Complain about missing \endcsname >>=
print_err("Missing ");
print_esc("endcsname");
print(" inserted");
help2("The control sequence marked <to be read again> should")
    ("not appear between \\csname and \\endcsname.");
back_error();
```
