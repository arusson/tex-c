# Section 975

```c << Compute the badness, |b|, using |AWFUL_BAD| if the box is too full >>=
if (cur_height < h) {
    if (active_height[3] != 0
      || active_height[4] != 0
      || active_height[5] != 0)
    {
      b = 0;
    }
    else {
      b = badness(h - cur_height, active_height[2]);
    }
}
else if (cur_height - h > active_height[6]) {
    b = AWFUL_BAD;
}
else {
    b = badness(cur_height - h, active_height[6]);
}
```
