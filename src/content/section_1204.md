# Section 1204

```c << Append the display and perhaps also the equation number >>=
if (e != 0) {
    r = new_kern(z - w - e - d);
    if (l) {
        link(a) = r;
        link(r) = b;
        b = a;
        d = 0;
    }
    else {
        link(b) = r;
        link(r) = a;
    }
    b = hpack(b, NATURAL);
}
shift_amount(b) = s + d;
append_to_vlist(b);
```
