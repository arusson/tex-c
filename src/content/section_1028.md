# Section 1028

```c << Ensure that box 255 is empty after output >>=
if (box(255) != null) {
    print_err("Output routine didn't use all of ");
    print_esc("box");
    print_int(255);
    help3("Your \\output commands should empty \\box255,")
        ("e.g., by saying `\\shipout\\box255'.")
        ("Proceed; I'll discard its present contents.");
    box_error(255);
}
```
