# Section 215

We will see later that the vertical list at the bottom semantic level is split into two parts; the "current page" runs from *PAGE_HEAD* to *page_tail*, and the "contribution list" runs from *CONTRIB_HEAD* to *tail* of semantic level zero.
The idea is that contributions are first formed in vertical mode, then "contributed" to the current page (during which time the page-breaking decisions are made).
For now, we don't need to know any more details about the page-building process.

```c << Set initial values of key variables >>+=
nest_ptr = 0;
max_nest_stack = 0;
mode = VMODE;
head = CONTRIB_HEAD;
tail = CONTRIB_HEAD;
prev_depth = IGNORE_DEPTH;
mode_line = 0;
prev_graf = 0;
shown_mode = 0;
// << Start a new current page >>
```
