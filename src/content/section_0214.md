# Section 214

Here is a common way to make the current list grow:

```c include/datastructures.h
#define tail_append(X) link(tail) = (X); tail = link(tail)
```
