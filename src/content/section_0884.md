# Section 884

We move the post-break list from inside node *q* to the main list by reattaching it just before the present node *r*, then resetting *r*.

```c << Transplant the post-break list >>=
s = post_break(q);
while (link(s) != null) {
    s = link(s);
}
link(s) = r;
r = post_break(q);
post_break(q) = null;
post_disc_break = true;
```
