# Section 708

```c << Look at the list of characters starting with |x| in font |g|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered >>=
y = x;
if (y >= font_bc[g] && y <= font_ec[g]) {
continue_lbl:
    q = char_info(g, y);
    if (char_exists(q)) {
        if (char_tag(q) == EXT_TAG) {
            f = g;
            c = y;
            goto found;
        }
        hd = height_depth(q);
        u = char_height(g, hd) + char_depth(g, hd);
        if (u > w) {
            f = g;
            c = y;
            w = u;
            if (u >= v) {
                goto found;
            }
        }
        if (char_tag(q) == LIST_TAG) {
            y = rem_byte(q);
            goto continue_lbl;
        }
    }
}
```
