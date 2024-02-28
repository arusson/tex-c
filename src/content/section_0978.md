# Section 978

```c << Dispense with trivial cases of void or bad boxes >>=
if (v == null) {
    return null;
}
if (type(v) != VLIST_NODE) {
    print_err("");
    print_esc("vsplit");
    print(" needs a ");
    print_esc("vbox");
    help2("The box you are trying to split is an \\hbox.")
        ("I can't split such a box, so I'll leave it alone.");
    error();
    return null;
}
```
