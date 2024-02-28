# Section 242

```c << Show equivalent |n|, in region 5 >>=
if (n < COUNT_BASE) {
    print_param(n - INT_BASE);
}
else if (n < DEL_CODE_BASE) {
    print_esc("count");
    print_int(n - COUNT_BASE);
}
else {
    print_esc("delcode");
    print_int(n - DEL_CODE_BASE);
}
print_char('=');
print_int(eqtb[n].integer);
```
