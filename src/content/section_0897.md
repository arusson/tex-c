# Section 897

The word to be hyphenated is now moved to the *hu* and *hc* arrays.

```c << Skip to node |hb|, putting letters into |hu| and |hc| >>=
hn = 0;
while(true) {
    if (is_char_node(s)) {
        if (font(s) != hf) {
            goto done3;
        }
        hyf_bchar = character(s);
        c = hyf_bchar;
        if (lc_code(c) == 0 || hn == 63) {
            goto done3;
        }
        hb = s;
        incr(hn);
        hu[hn] = c;
        hc[hn] = lc_code(c);
        hyf_bchar = NON_CHAR;
    }
    else if (type(s) == LIGATURE_NODE) {
        // << Move the characters of a ligature node to |hu| and |hc|; but |goto done3| if they are not all letters >>
    }
    else if (type(s) == KERN_NODE && subtype(s) == NORMAL) {
        hb = s;
        hyf_bchar = font_bchar[hf];
    }
    else {
        goto done3;
    }
    s = link(s);
}
done3:
```
