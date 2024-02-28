# Section 1294

```c << Show the current meaning of a token, then |goto common_ending| >>=
get_token();
print_nl("> ");
if (cur_cs != 0) {
    sprint_cs(cur_cs);
    print_char('=');
}
print_meaning();
goto common_ending;
```
