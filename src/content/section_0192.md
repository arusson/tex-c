# Section 192

```c << Display math node |p| >>=
print_esc("math");
if (subtype(p) == BEFORE) {
    print("on");
}
else {
    print("off");
}
if (width(p) != 0) {
    print(", surrounded ");
    print_scaled(width(p));
}
```
