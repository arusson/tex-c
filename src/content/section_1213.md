# Section 1213

```c << Discard the prefixes \long and \outer if they are irrelevant >>=
if (cur_cmd != DEF && a % 4 != 0) {
    print_err("You can't use `");
    print_esc("long");
    print("' or `");
    print_esc("outer");
    print("' with `");
    print_cmd_chr(cur_cmd, cur_chr);
    print_char('\'');
    help1("I'll pretend you didn't say \\long or \\outer here.");
    error();
}
```
