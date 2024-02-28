# Section 739

```c << Make the height of box |y| equal to |h| >>=
p = new_kern(h - height(y));
link(p) = list_ptr(y);
list_ptr(y) = p;
height(y) = h;
```
