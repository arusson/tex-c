# Section 1177

```c << Insert a dummy noad to be sub/superscripted >>=
tail_append(new_noad());
p = supscr(tail) + cur_cmd - SUP_MARK; // |supscr| or |subscr|
if (t != EMPTY) {
    if (cur_cmd == SUP_MARK) {
        print_err("Double superscript");
        help1("I treat `x^1^2' essentially like `x^1{}^2'.");
    }
    else {
        print_err("Double subscript");
        help1("I treat `x_1_2' essentially like `x_1{}_2'.");
    }
    error();
}
```
