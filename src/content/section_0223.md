# Section 223

Here is a routine that displays the current meaning of an *eqtb* entry in region 1 or 2.
(Similar routines for the other regions will appear below.)

```c << Show equivalent |n|, in region 1 or 2 >>=
sprint_cs(n);
print_char('=');
print_cmd_chr(eq_type(n), equiv(n));
if (eq_type(n) >= CALL) {
    print_char(':');
    show_token_list(link(equiv(n)), null, 32);
}
```
