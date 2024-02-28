# Section 1202

We try first to center the display without regard to the existence of the equation number.
If that would make it too close (where "too close" means that the space between display and equation number is less than the width of the equation number), we either center it in the remaining space or move it as far from the equation number as possible.
The latter alternative is taken only if the display begins with glue, since we assume that the user put glue there to control the spacing precisely.

```c << Determine the displacement, |d|, of the left edge of the equation, with respect to the line size |z|, assuming that |l = false| >>=
d = half(z - w);
if (e > 0 && d < 2*e) {
    // too close
    d = half(z - w - e);
    if (p != null
        && !is_char_node(p)
        && type(p) == GLUE_NODE)
    {
        d = 0;
    }
}
```
