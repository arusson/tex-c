# Section 191

An "explicit" kern value is indicated implicitly by an explicit space.

```c << Display kern |p| >>=
if (subtype(p) != MU_GLUE) {
    print_esc("kern");
    if (subtype(p) != NORMAL) {
        print_char(' ');
    }
    print_scaled(width(p));
    if (subtype(p) == ACC_KERN) {
        print(" (for accent)");
    }
}
else {
    print_esc("mkern");
    print_scaled(width(p));
    print("mu");
}
```
