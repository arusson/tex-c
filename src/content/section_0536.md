# Section 536

> ![NOTE]
> Months name are stored in a `char *` (see above) instead of being stored in the string pool.

```c << Print the banner line, including the date and time >>=
wlog(BANNER);
slow_print(format_ident);
print("  ");
print_int(sys_day);
print_char(' ');
wlog("%s", months[sys_month - 1]);
print_char(' ');
print_int(sys_year);
print_char(' ');
print_two(sys_time / 60);
print_char(':');
print_two(sys_time % 60);
```
