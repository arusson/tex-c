# Section 735

```c << Declare math construction procedures >>+=
void make_under(pointer q) {
    pointer p, x, y; // temporary registers for box construction
    scaled delta;    // overall height plus depth
    x = clean_box(nucleus(q), cur_style);
    p = new_kern(3*default_rule_thickness);
    link(x) = p;
    link(p) = fraction_rule(default_rule_thickness);
    y = vpack(x, NATURAL);
    delta = height(y) + depth(y) + default_rule_thickness;
    height(y) = height(x);
    depth(y) = delta - height(y);
    info(nucleus(q)) = y;
    math_type(nucleus(q)) = SUB_BOX;
}
```
