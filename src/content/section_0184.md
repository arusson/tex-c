# Section 184

```c << Display box |p| >>=
if (type(p) == HLIST_NODE) {
    print_esc("h");
}
else if (type(p) == VLIST_NODE) {
    print_esc("v");
}
else {
    print_esc("unset");
}
print("box(");
print_scaled(height(p));
print_char('+');
print_scaled(depth(p));
print(")x");
print_scaled(width(p));
if (type(p) == UNSET_NODE) {
    // << Display special fields of the unset node |p| >>
}
else {
    // << Display the value of |glue_set(p)| >>
    if (shift_amount(p) != 0) {
        print(", shifted ");
        print_scaled(shift_amount(p));
    }
}
node_list_display(list_ptr(p)); // recursive call
```
