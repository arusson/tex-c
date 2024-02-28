# Section 443

```c << Scan an optional space >>=
get_x_token();
if (cur_cmd != SPACER) {
    back_input();
}
```
