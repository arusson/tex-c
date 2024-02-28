# Section 661

In order to provide a decent indication of where an overfull or underfull box originated, we use a global variable *pack_begin_line* that is set nonzero only when *hpack* is being called by the paragraph builder or the alignment finishing routine.

```c << Global variables >>+=
int pack_begin_line; // source file line where the current paragraph or alignment began; a negative value denotes alignment
```
