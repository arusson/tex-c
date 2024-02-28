# Section 1197

$\TeX$ gets to the following part of the program when the first '`$`' ending a display has been scanned.

```c << Check that another $ follows >>=
get_x_token();
if (cur_cmd != MATH_SHIFT) {
    print_err("Display math should end with $$");
    help2("The `$' that I just saw supposedly matches a previous `$$'.")
        ("So I shall assume that you typed `$$' both times.");
    back_error();
}
```
