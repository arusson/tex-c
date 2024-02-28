# Section 128

```c << Allocate from the top of node |p| and |goto found| >>=
node_size(p) = r - p; // store the remaining size
rover = p; // start searching here next time
goto found;
```
