# Section 1152

An active character that is an *OUTER_CALL* is allowed here.

```c << Treat |cur_chr| as an active character >>=
cur_cs = cur_chr + ACTIVE_BASE;
cur_cmd = eq_type(cur_cs);
cur_chr = equiv(cur_cs);
x_token();
back_input();
```
