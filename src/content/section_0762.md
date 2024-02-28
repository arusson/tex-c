# Section 762

The *make_left_right* function constructs a left or right delimiter of the required size and returns the value *OPEN_NOAD* or *CLOSE_NOAD*.
The *RIGHT_NOAD* and *LEFT_NOAD* will both be based on the original *style*, so they will have consistent sizes.

We use the fact that *RIGHT_NOAD − LEFT_NOAD = CLOSE_NOAD − OPEN_NOAD*.

```c << Declare math construction procedures >>+=
small_number make_left_right(pointer q, small_number style, scaled max_d, scaled max_h) {
    scaled delta, delta1, delta2; // dimensions used in the calculation
    if (style < SCRIPT_STYLE) {
        cur_size = TEXT_SIZE;
    }
    else {
        cur_size = 16 * ((style - TEXT_STYLE) / 2);
    }
    delta2 = max_d + axis_height(cur_size);
    delta1 = max_h + max_d - delta2;
    if (delta2 > delta1) {
        // |delta1| is max distance from axis
        delta1 = delta2;
    }
    delta = (delta1 / 500) * delimiter_factor;
    delta2 = delta1 + delta1 - delimiter_shortfall;
    if (delta < delta2) {
        delta = delta2;
    }
    new_hlist(q) = var_delimiter(delimiter(q), cur_size, delta);
    return type(q) - (LEFT_NOAD - OPEN_NOAD); // |OPEN_NOAD| or |CLOSE_NOAD|
}
```
