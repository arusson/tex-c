# Section 1006

```c << Display the page break cost >>=
begin_diagnostic();
print_nl("\%");
print(" t=");
print_totals();
print(" g=");
print_scaled(page_goal);
print(" b=");
if (b == AWFUL_BAD) {
    print_char('*');
}
else {
    print_int(b);
}
print(" p=");
print_int(pi);
print(" c=");
if (c == AWFUL_BAD) {
    print_char('*');
}
else {
    print_int(c);
}
if (c <= least_page_cost) {
    print_char('#');
}
end_diagnostic(false);
```
