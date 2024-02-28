# Section 428

```c << Complain that \the can't do this; give zero result >>=
print_err("You can't use `");
print_cmd_chr(cur_cmd, cur_chr);
print("' after ");
print_esc("the");
help1("I'm forgetting what you said and using zero instead.");
error();
if (level != TOK_VAL) {
    scanned_result(0, DIMEN_VAL);
}
else {
    scanned_result(0, INT_VAL);
}
```
