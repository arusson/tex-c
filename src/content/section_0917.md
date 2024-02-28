# Section 917

```c << Append characters of |hu[j..]| to |major_tail|, advancing |j| >>=
j = reconstitute(j, hn, bchar, NON_CHAR) + 1;
link(major_tail) = link(HOLD_HEAD);
while (link(major_tail) > null) {
    advance_major_tail;
}
```
