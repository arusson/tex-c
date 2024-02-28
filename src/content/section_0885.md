# Section 885

We move the pre-break list from inside node *q* to the main list by reattaching it just after the present node *q*, then resetting *q*.

```c << Transplant the pre-break list >>=
s = pre_break(q);
link(q) = s;
while (link(s) != null) {
    s = link(s);
}
pre_break(q) = null;
q = s;
```
