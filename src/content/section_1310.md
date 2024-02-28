# Section 1310

```c include/io.h
#define undump_four_ASCII         \
    undump_qqqq(w);               \
    str_pool[k] = qqqq_b0(w);     \
    str_pool[k + 1] = qqqq_b1(w); \
    str_pool[k + 2] = qqqq_b2(w); \
    str_pool[k + 3] = qqqq_b3(w)
```

```c << Undump the string pool >>=
undump_size(0, POOL_SIZE, "string pool size", pool_ptr);
undump_size(0, MAX_STRINGS, "max strings", str_ptr);
for(k = 0; k <= str_ptr; k++) {
    undump(0, pool_ptr, str_start[k]);
}
k = 0;
while (k + 4 < pool_ptr) {
    undump_four_ASCII;
    k += 4;
}
k = pool_ptr - 4;
undump_four_ASCII;
init_str_ptr = str_ptr;
init_pool_ptr = pool_ptr;
```
