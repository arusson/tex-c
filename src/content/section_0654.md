# Section 654

The following code is part of $\TeX$'s inner loop; i.e., adding another character of text to the user's input will cause each of these instructions to be exercised one more time.

```c << Incorporate character dimensions into the dimensions of the hbox that will contain it, then move to the next node >>=
f = font(p);
i = char_info(f, character(p));
hd = height_depth(i);
x += char_width(f, i);
s = char_height(f, hd);
if (s > h) {
    h = s;
}
s = char_depth(f, hd);
if (s > d) {
    d = s;
}
p = link(p);
```
