# Section 1120

```c << Attach list |p| to the current list, and record its length; then finish up and |return| >>=
if (n > 0 && abs(mode) == MMODE) {
    print_err("Illegal math ");
    print_esc("discretionary");
    help2("Sorry: The third part of a discretionary break must be")
        ("empty, in math formulas. I had to delete your third part.");
    flush_node_list(p);
    n = 0;
    error();
}
else {
    link(tail) = p;
}
if (n <= MAX_QUARTERWORD) {
    replace_count(tail) = n;
}
else {
    print_err("Discretionary list is too long");
    help2("Wow---I never thought anybody would tweak me here.")
        ("You can't seriously need such a huge discretionary list?");
    error();
}
if (n > 0) {
    tail = q;
}
decr(save_ptr);
return;
```
