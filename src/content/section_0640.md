# Section 640

```c << Ship box |p| out >>=
// << Update the values of |max_h| and |max_v|; but if the page is too large, |goto done| >>
// << Initialize variables as |ship_out| begins >>
page_loc = dvi_offset + dvi_ptr;
dvi_out(BOP);
for(k = 0; k <= 9; k++) {
    dvi_four(count(k));
}
dvi_four(last_bop);
last_bop = page_loc;
cur_v = height(p) + v_offset;
temp_ptr = p;
if (type(p) == VLIST_NODE) {
    vlist_out();
}
else {
    hlist_out();
}
dvi_out(EOP);
incr(total_pages);
cur_s = -1;
done:
```
