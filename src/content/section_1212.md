# Section 1212

```c << Discard erroneous prefixes and |return| >>=
print_err("You can't use a prefix with `");
print_cmd_chr(cur_cmd, cur_chr);
print_char('\'');
help1("I'll pretend you didn't say \\long or \\outer or \\global.");
back_error();
return;
```
