# Section 1047

```c << Declare action procedures for use by |main_control| >>+=
void insert_dollar_sign() {
    back_input();
    cur_tok = MATH_SHIFT_TOKEN + '$';
    print_err("Missing $ inserted");
    help2("I've inserted a begin-math/end-math symbol since I think")
        ("you left one out. Proceed, with fingers crossed.");
    ins_error();
}
```
