# Section 1031

When a new token has just been fetched at *big_switch*, we have an ideal place to monitor $\TeX$'s activity.

```c << Give diagnostic information, if requested >>=
if (interrupt != 0 && ok_to_interrupt) {
    back_input();
    check_interrupt;
    goto big_switch;
}
#ifdef DEBUG
if (panicking) {
    check_mem(false);
}
#endif
if (tracing_commands > 0) {
    show_cur_cmd_chr();
}
```
