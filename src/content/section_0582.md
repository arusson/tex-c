# Section 582

Here is a function that returns a pointer to a character node for a given character in a given font.
If that character doesn't exist, *null* is returned instead.

```c font_metric.c
pointer new_character(internal_font_number f, eight_bits c) {
    pointer p; // newly allocated node
    if (font_bc[f] <= c && font_ec[f] >= c && char_exists(char_info(f, c))) {
        p = get_avail();
        font(p) = f;
        character(p) = c;
        return p;
    }
    char_warning(f, c);
    return null;
}
```
