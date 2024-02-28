# Section 909

We may want to look at the lig/kern program twice, once for a hyphen and once for a normal letter.
(The hyphen might appear after the letter in the program, so we'd better not try to look for both at once.)

```c << If there's a ligature or kern at the cursor position, update the data structures, possibly advancing |j|; continue until the cursor moves >>=
if (cur_l == NON_CHAR) {
    k = bchar_label[hf];
    if (k == NON_ADDRESS) {
        goto done;
    }
    else {
        q = font_info[k];
    }
}
else {
    q = char_info(hf, cur_l);
    if (char_tag(q) != LIG_TAG) {
        goto done;
    }
    k = lig_kern_start(hf, q);
    q = font_info[k];
    if (skip_byte(q) > STOP_FLAG) {
        k = lig_kern_restart(hf, q);
        q = font_info[k];
    }
} // now |k| is the starting address of the lig/kern program
if (cur_rh < NON_CHAR) {
    test_char = cur_rh;
}
else {
    test_char = cur_r;
}
while(true) {
    if (next_char(q) == test_char && skip_byte(q) <= STOP_FLAG) {
        if (cur_rh < NON_CHAR) {
            hyphen_passed = j;
            hchar = NON_CHAR;
            cur_rh = NON_CHAR;
            goto continue_lbl;
        }
        else {
            if (hchar < NON_CHAR && odd(hyf[j])) {
                hyphen_passed = j;
                hchar = NON_CHAR;
            }
            if (op_byte(q) < KERN_FLAG) {
                // << Carry out a ligature replacement, updating the cursor structure and possibly advancing |j|; |goto continue| if the cursor doesn't advance, otherwise |goto done| >>
            }
            w = char_kern(hf, q);
            goto done; // this kern will be inserted below
        }
    }
    if (skip_byte(q) >= STOP_FLAG) {
        if (cur_rh == NON_CHAR) {
            goto done;
        }
        else {
            cur_rh = NON_CHAR;
            goto continue_lbl;
        }
    }
    k += skip_byte(q) + 1;
    q = font_info[k];
}
done:
```
