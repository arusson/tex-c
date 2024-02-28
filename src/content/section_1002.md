# Section 1002

```c << Prepare to move a box or rule node to the current page, then |goto contribute| >>=
page_total += page_depth + height(p);
page_depth = depth(p);
goto contribute;
```
