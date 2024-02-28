# Section 740

```c << Switch to a larger accent if available and appropriate >>=
while(true) {
    if (char_tag(i) != LIST_TAG) {
        break; // goto done
    }
    y = rem_byte(i);
    i = char_info(f, y);
    if (!char_exists(i) || char_width(f, i) > w) {
        break; // goto done
    }
    c = y;
}
// done:
```
