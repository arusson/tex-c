# Section 575

We check to see that the `TFM` file doesn't end prematurely;
but no error message is given for files having more than *lf* words.

> ![NOTE]
> Check removed.

```c << Read font parameters >>=
for(k = 1; k <= np; k++) {
    if (k == 1) {
        // the |slant| parameter is a pure number
        fget(sw);
        if (sw > 127) {
            sw -= 256;
        }
        fget(temp);
        sw = sw*256 + temp;
        fget(temp);
        sw = sw*256 + temp;
        fget(temp);
        font_info[param_base[f]].sc = sw*16 + temp/16;
    }
    else {
        store_scaled(font_info[param_base[f] + k - 1].sc);
    }
}
// if (eof(tmf_file)) then abort;
for(k = np + 1; k <= 7; k++) {
    font_info[param_base[f] + k - 1].sc = 0;
}
```
