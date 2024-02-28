# Section 991

The page builder is ready to start a fresh page if we initialize the following state variables.
(However, the page insertion list is initialized elsewhere.)

```c << Start a new current page >>=
page_contents = EMPTY;
page_tail = PAGE_HEAD;
link(PAGE_HEAD) = null;
last_glue = MAX_HALFWORD;
last_penalty = 0;
last_kern = 0;
page_depth = 0;
page_max_depth = 0;
```
