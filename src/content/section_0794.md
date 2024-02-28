# Section 794

```c << Copy the templates from node |cur_loop| into node |p| >>=
q = HOLD_HEAD;
r = u_part(cur_loop);
while (r != null) {
    link(q) = get_avail();
    q = link(q);
    info(q) = info(r);
    r = link(r);
}
link(q) = null;
u_part(p) = link(HOLD_HEAD);
q = HOLD_HEAD;
r = v_part(cur_loop);
while (r != null) {
    link(q) = get_avail();
    q = link(q);
    info(q) = info(r);
    r = link(r);
}
link(q) = null;
v_part(p) = link(HOLD_HEAD);
```
