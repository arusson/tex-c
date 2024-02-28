# Section 86

Here the author of $\TeX$ apologizes for making use of the numerical relation between `'Q'`, `'R'`, `'S'`, and the desired interaction settings *BATCH_MODE*, *NONSTOP_MODE*, *SCROLL_MODE*.

```c << Change the interaction level and |return| >>=
error_count = 0;
interaction = BATCH_MODE + c - 'Q';
print("OK, entering ");
switch(c) {
case 'Q':
    print_esc("batchmode");
    decr(selector);
    break;

case 'R':
    print_esc("nonstopmode");
    break;

case 'S':
    print_esc("scrollmode");
    break;
} // there are no other cases
print("...");
print_ln();
update_terminal;
return;
```
