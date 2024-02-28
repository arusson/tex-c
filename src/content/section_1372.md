# Section 1372

```c << Recover from an unbalanced write command >>=
print_err("Unbalanced write command");
help2("On this page there's a \\write with fewer real {'s than }'s.")
    ("I can't handle that very well; good luck.");
error();
do {
    get_token();
} while (cur_tok != END_WRITE_TOKEN);
```
