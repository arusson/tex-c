# Section 1003

```c << Make sure that |page_max_depth| is not exceeded >>=
if (page_depth > page_max_depth) {
    page_total += page_depth - page_max_depth;
    page_depth = page_max_depth;
}
```
