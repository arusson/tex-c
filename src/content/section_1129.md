# Section 1129

The help messages here contain a little white lie, since `\noalign` and `\omit` are allowed also after '`\noalign{...}`'.

```c << Declare action procedures for use by |main_control| >>+=
void no_align_error() {
    print_err("Misplaced ");
    print_esc("noalign");
    help2("I expect to see \\noalign only after the \\cr of")
        ("an alignment. Proceed, and I'll ignore this case.");
    error();
}

void omit_error() {
    print_err("Misplaced ");
    print_esc("omit");
    help2("I expect to see \\omit only after tab marks or the \\cr of")
        ("an alignment. Proceed, and I'll ignore this case.");
    error();
}
```
