# Section 1159

```c math/math_lists.c
void math_limit_switch() {
    if (head != tail && type(tail) == OP_NOAD) {
        subtype(tail) = cur_chr;
        return;
    }
    print_err("Limit controls must follow a math operator");
    help1("I'm ignoring this misplaced \\limits or \\nolimits command.");
    error();
}
```
