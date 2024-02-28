# Section 713

```c << Construct an extensible character in a new box |b|, using recipe |rem_byte(q)| and font |f| >>=
b = new_null_box();
type(b) = VLIST_NODE;
r = font_info[exten_base[f] + rem_byte(q)];
// << Compute the minimum suitable height, |w|, and the corresponding number of extension steps, |n|; also set |width(b)| >>
c = ext_bot(r);
if (c != MIN_QUARTERWORD) {
    stack_into_box(b, f, c);
}
c = ext_rep(r);
for(m = 1; m <= n; m++) {
    stack_into_box(b, f, c);
}
c = ext_mid(r);
if (c != MIN_QUARTERWORD) {
    stack_into_box(b, f, c);
    c = ext_rep(r);
    for(m = 1; m <= n; m++) {
        stack_into_box(b, f, c);
    }
}
c = ext_top(r);
if (c != MIN_QUARTERWORD) {
    stack_into_box(b, f, c);
}
depth(b) = w - height(b);
```
