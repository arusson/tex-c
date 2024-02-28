# Section 846

```c << Print a symbolic description of the new break node >>=
print_nl("@@");
print_int(serial(passive));
print(": line ");
print_int(line_number(q) - 1);
print_char('.');
print_int(fit_class);
if (break_type == HYPHENATED) {
    print_char('-');
}
print(" t=");
print_int(total_demerits(q));
print(" -> @@");
if (prev_break(passive) == null) {
    print_char('0');
}
else {
    print_int(serial(prev_break(passive)));
}
```
