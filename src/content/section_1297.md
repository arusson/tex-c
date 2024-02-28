# Section 1297

> ![NOTE]
> Originally, we have `p = the_toks();`, but *p* is unused.

```c << Show the current value of some parameter or register, then |goto common_ending| >>=
the_toks();
print_nl("> ");
token_show(TEMP_HEAD);
flush_list(link(TEMP_HEAD));
goto common_ending;
```
