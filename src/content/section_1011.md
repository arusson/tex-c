# Section 1011

```c << Display the insertion split cost >>=
begin_diagnostic();
print_nl("\% split");
print_int(n);
print(" to ");
print_scaled(w);
print_char(',');
print_scaled(best_height_plus_depth);
print(" p=");
if (q == null) {
    print_int(EJECT_PENALTY);
}
else if (type(q) == PENALTY_NODE) {
    print_int(penalty(q));
}
else {
    print_char('0');
}
end_diagnostic(false);
```
