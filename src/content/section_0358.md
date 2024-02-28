# Section 358

The present point in the program is reached only when the *expand* routine has inserted a special marker into the input.
In this special case, *info(loc)* is known to be a control sequence token, and *link(loc) = null*.

```c include/constants.h
#define NO_EXPAND_FLAG 257 // this characterizes a special variant of |RELAX|
```

```c << Get the next token, suppressing expansion >>=
cur_cs = info(loc) - CS_TOKEN_FLAG;
loc = null;
cur_cmd = eq_type(cur_cs);
cur_chr = equiv(cur_cs);
if (cur_cmd > MAX_COMMAND) {
    cur_cmd = RELAX;
    cur_chr = NO_EXPAND_FLAG;
}
```
