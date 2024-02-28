# Section 896

The first thing we need to do is find the node *ha* just before the first letter.

```c << Skip to node |ha|, or |goto done1| if no hyphenation should be attempted >>=
while(true) {
    if (is_char_node(s)) {
        c = character(s);
        hf = font(s);
    }
    else if (type(s) == LIGATURE_NODE) {
        if (lig_ptr(s) == null) {
            goto continue_lbl;
        }
        else {
            q = lig_ptr(s);
            c = character(q);
            hf = font(q);
        }
    }
    else if (type(s) == KERN_NODE && subtype(s) == NORMAL) {
        goto continue_lbl;
    }
    else if (type(s) == WHATSIT_NODE) {
        // << Advance past a whatsit node in the pre-hyphenation loop >>
        goto continue_lbl;
    }
    else {
        goto done1;
    }
    if (lc_code(c) != 0) {
        if (lc_code(c) == c || uc_hyph > 0) {
            goto done2;
        }
        else {
            goto done1;
        }
    }
continue_lbl:
    prev_s = s;
    s = link(prev_s);
}
done2:
hyf_char = hyphen_char[hf];
if (hyf_char < 0 || hyf_char > 255) {
    goto done1;
}
ha = prev_s;
```
