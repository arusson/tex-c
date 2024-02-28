# Section 1240

```c << Compute result of |MULTIPLY| or |DIVIDE|, put it in |cur_val| >>=
scan_int();
if (p < GLUE_VAL) {
    if (q == MULTIPLY) {
        if (p == INT_VAL) {
            cur_val = mult_integers(eqtb[l].integer, cur_val);
        }
        else {
            cur_val = nx_plus_y(eqtb[l].integer, cur_val, 0);
        }
    }
    else {
        cur_val = x_over_n(eqtb[l].integer, cur_val);
    }
}
else {
    s = equiv(l);
    r = new_spec(s);
    if (q == MULTIPLY) {
        width(r) = nx_plus_y(width(s), cur_val, 0);
        stretch(r) = nx_plus_y(stretch(s), cur_val, 0);
        shrink(r) = nx_plus_y(shrink(s), cur_val, 0);
    }
    else {
        width(r) = x_over_n(width(s), cur_val);
        stretch(r) = x_over_n(stretch(s), cur_val);
        shrink(r) = x_over_n(shrink(s), cur_val);
    }
    cur_val = r;
}
```
