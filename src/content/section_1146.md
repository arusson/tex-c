# Section 1146

```c << Calculate the natural width, |w|, by which the characters of the final line extend to the right of the reference point, plus two ems; or set |w = MAX_DIMEN| if the non-blank information on that line is affected by stretching or shrinking >>=
v = shift_amount(just_box) + 2 * quad(cur_font);
w = -MAX_DIMEN;
p = list_ptr(just_box);
while (p != null) {
    // << Let |d| be the natural width of node |p|; if the node is "visible," |goto found|; if the node is glue that stretches or shrinks, set |v = MAX_DIMEN| >>

    if (v < MAX_DIMEN) {
        v += d;
    }
    goto not_found;
found:
    if (v < MAX_DIMEN) {
        v += d;
        w = v;
    }
    else {
        w = MAX_DIMEN;
        break; // goto done
    }
not_found:
    p = link(p);
}
// done:
```
