# Section 117

In order to study the memory requirements of particular applications, it is possible to prepare a version of $\TeX$ that keeps track of current and maximum memory usage.
When code between the delimiters **stat .. tats**. is not "commented out", $\TeX$ will run a bit slower but it will report these statistics when *tracing_stats* is sufficiently large.

```c << Global variables >>+=
int var_used, dyn_used; // how much memory is in use
```
