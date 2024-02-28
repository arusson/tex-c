# Section 1087

The height of a '`\vtop`' box is inherited from the first item on its list, if that item is an *HLIST_NODE*, *VLIST_NODE*, or *RULE_NODE*;
otherwise the `\vtop` height is zero.

```c << Readjust the height and depth of |cur_box|, for \vtop >>=
h = 0;
p = list_ptr(cur_box);
if (p != null && type(p) <= RULE_NODE) {
    h = height(p);
}
depth(cur_box) += (-h + height(cur_box));
height(cur_box) = h;
```
