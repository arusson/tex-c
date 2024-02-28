# Section 859

```c << Compute the demerits, |d|, from |r| to |cur_p| >>=
d = line_penalty + b;
if (abs(d) >= 10000) {
    d = 100000000;
}
else {
    d *= d;
}
if (pi != 0) {
    if (pi > 0) {
        d += pi*pi;
    }
    else if (pi > EJECT_PENALTY) {
        d -= pi*pi;
    }
}
if (break_type == HYPHENATED && type(r) == HYPHENATED) {
    if (cur_p != null) {
        d += double_hyphen_demerits;
    }
    else {
        d += final_hyphen_demerits;
    }
}
if (abs(fit_class - fitness(r)) > 1) {
    d += adj_demerits;
}
```
