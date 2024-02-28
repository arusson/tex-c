# Section 697

```c << Display fraction noad |p| >>=
print_esc("fraction, thickness ");
if (thickness(p) == DEFAULT_CODE) {
    print("= default");
}
else {
    print_scaled(thickness(p));
}
if (small_fam(left_delimiter(p)) != 0
    || small_char(left_delimiter(p)) != MIN_QUARTERWORD
    || large_fam(left_delimiter(p)) != 0
    || large_char(left_delimiter(p)) != MIN_QUARTERWORD)
{
    print(", left-delimiter ");
    print_delimiter(left_delimiter(p));
}
if (small_fam(right_delimiter(p)) != 0
    || small_char(right_delimiter(p)) != MIN_QUARTERWORD
    || large_fam(right_delimiter(p)) != 0
    || large_char(right_delimiter(p)) != MIN_QUARTERWORD)
{
    print(", right-delimiter ");
    print_delimiter(right_delimiter(p));
}
print_subsidiary_data(numerator(p), '\\');
print_subsidiary_data(denominator(p), '/');
```
