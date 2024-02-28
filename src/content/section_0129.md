# Section 129

Here we delete node *p* from the ring, and let *rover* rove around.

```c << Allocate entire node |p| and |goto found| >>=
rover = rlink(p);
t = llink(p);
llink(rover) = t;
rlink(t) = rover;
goto found;
```
