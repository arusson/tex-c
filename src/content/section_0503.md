# Section 503

Here we use the fact that `'<'`, `'='`, and `'>'` are consecutive ASCII codes.

```c << Test relation between integers or dimensions >>=
if (this_if == IF_INT_CODE) {
    scan_int();
}
else {
    scan_normal_dimen;
}
n = cur_val;
// << Get the next non-blank non-call token >>
if (cur_tok >= OTHER_TOKEN + '<' && cur_tok <= OTHER_TOKEN + '>') {
    r = cur_tok - OTHER_TOKEN;
}
else {
    print_err("Missing = inserted for ");
    print_cmd_chr(IF_TEST, this_if);
    help1("I was expecting to see `<', `=', or `>'. Didn't.");
    back_error();
    r = '=';
}
if (this_if == IF_INT_CODE) {
    scan_int();
}
else {
    scan_normal_dimen;
}
switch (r) {
case '<':
    b = (n < cur_val);
    break;

case '=':
    b = (n == cur_val);
    break;

case '>':
    b = (n > cur_val);
}
```
