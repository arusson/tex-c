# Section 1166

```c << Complain that the user should have said \mathaccent >>=
print_err("Please use ");
print_esc("mathaccent");
print(" for accents in math mode");
help2("I'm changing \\accent to \\mathaccent here; wish me luck.")
    ("(Accents are not the same in formulas as they are in text.)");
error();
```
