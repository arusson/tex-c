# Section 998

```c << Link node |p| into the current page and |goto done| >>=
link(page_tail) = p;
page_tail = p;
link(CONTRIB_HEAD) = link(p);
link(p) = null;
goto done;
```
