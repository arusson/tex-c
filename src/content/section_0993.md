# Section 993

The following procedure guarantees that a given box register does not contain an `\hbox`.

```c builder/page_builder.c
void ensure_vbox(eight_bits n) {
    pointer p; // the box register contents
    p = box(n);
    if (p != null && type(p) == HLIST_NODE) {
        print_err("Insertions can only be added to a vbox");
        help3("Tut tut: You're trying to \\insert into a")
            ("\\box register that now contains an \\hbox.")
            ("Proceed, and I'll discard its present contents.");
        box_error(n);
    }
}
```
