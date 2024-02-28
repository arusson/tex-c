# Section 1015

```c << Ensure that box 255 is empty before output >>=
if (box(255) != null) {
    print_err("");
    print_esc("box");
    print("255 is not void");
    help2("You shouldn't use \\box255 except in \\output routines.")
        ("Proceed, and I'll discard its present contents.");
    box_error(255);
}
```
