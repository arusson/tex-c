# Section 938

```c << Append the value |n| to list |p| >>=
if (n < 63) {
    q = get_avail();
    link(q) = p;
    info(q) = n;
    p = q;
}
```
