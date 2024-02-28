# Section 132

The following `while` loop is guaranteed to terminate, since the list that starts at *rover* ends with *MAX_HALFWORD* during the sorting procedure.

```c << Sort |p| into the list starting at |rover| and advance |p| to |rlink(p)| >>=
if (p < rover) {
    q = p;
    p = rlink(q);
    rlink(q) = rover;
    rover = q;
}
else {
    q = rover;
    while (rlink(q) < p) {
        q = rlink(q);
    }
    r = rlink(p);
    rlink(p) = rlink(q);
    rlink(q) = p;
    p = r;
}
```
