# Section 703

When the style changes, the following piece of program computes associated information:

```c << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>=
if (cur_style < SCRIPT_STYLE) {
    cur_size = TEXT_SIZE;
}
else {
    cur_size = 16*((cur_style - TEXT_STYLE) / 2);
}
cur_mu = x_over_n(math_quad(cur_size), 18);
```
