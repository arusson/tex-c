# Section 398

```c << Report an improper use of the macro and abort >>=
print_err("Use of ");
sprint_cs(warning_index);
print(" doesn't match its definition");
help4("If you say, e.g., `\\def\\a1{...}', then you must always")
    ("put `1' after `\\a', since control sequence names are")
    ("made up of letters only. The macro here has not been")
    ("followed by the required stuff, so I'm ignoring it.");
error();
goto end;
```
