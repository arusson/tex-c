# Section 744

```c << Create equal-width boxes |x| and |z| for the numerator and denominator, and compute the default amounts |shift_up| and |shift_down| by which they are displaced from the baseline >>=
x = clean_box(numerator(q), num_style(cur_style));
z = clean_box(denominator(q), denom_style(cur_style));
if (width(x) < width(z)) {
    x = rebox(x, width(z));
}
else {
    z = rebox(z, width(x));
}
if (cur_style < TEXT_STYLE) {
    // display style
    shift_up = num1(cur_size);
    shift_down = denom1(cur_size);
}
else {
    shift_down = denom2(cur_size);
    if (thickness(q) != 0) {
        shift_up = num2(cur_size);
    }
    else {
        shift_up = num3(cur_size);
    }
}
```
