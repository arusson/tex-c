# Section 1296

```c << Show the current contents of a box >>=
scan_eight_bit_int();
begin_diagnostic();
print_nl("> \\box");
print_int(cur_val);
print_char('=');
if (box(cur_val) == null) {
    print("void");
}
else {
    show_box(box(cur_val));
}
```
