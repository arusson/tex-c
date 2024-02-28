# Section 610

```c << Generate a |DOWN| or |RIGHT| command for |w| and |return| >>=
info(q) = YZ_OK;
if (abs(w) >= 0x800000) {
    dvi_out(o + 3); // |DOWN4| or |RIGHT4|
    dvi_four(w);
    return;
}
if (abs(w) >= 0x8000 ) {
    dvi_out(o + 2); // |DOWN3| or |RIGHT3|
    if (w < 0) {
        w += 0x1000000;
    }
    dvi_out(w / 0x10000);
    w %= 0x10000;
    goto label_2;
}
if (abs(w) >= 128) {
    dvi_out(o + 1); // |DOWN2| or |RIGHT2|
    if (w < 0) {
        w += 0x10000;
    }
    goto label_2;
}
dvi_out(o); // |DOWN1| or |RIGHT1|
if (w < 0) {
    w += 256;
}
goto label_1;
label_2:
dvi_out(w / 256);
label_1:
dvi_out(w % 256);
return;
```
