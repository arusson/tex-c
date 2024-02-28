# Section 1066

```c << Drop current token and complain that it was unmatched >>=
print_err("Extra ");
print_cmd_chr(cur_cmd, cur_chr);
help1("Things are pretty mixed up, but I think the worst is over.");
error();
```
