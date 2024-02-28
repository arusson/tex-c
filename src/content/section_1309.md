# Section 1309

```c include/io.h
#define dump_four_ASCII           \
    qqqq_b0(w) = str_pool[k];     \
    qqqq_b1(w) = str_pool[k + 1]; \
    qqqq_b2(w) = str_pool[k + 2]; \
    qqqq_b3(w) = str_pool[k + 3]; \
    dump_qqqq(w)
```

```c << Dump the string pool >>=
dump_int(pool_ptr);
dump_int(str_ptr);
for(k = 0; k <= str_ptr; k++) {
    dump_int(str_start[k]);
}
k = 0;
while (k + 4 < pool_ptr) {
    dump_four_ASCII;
    k += 4;
}
k = pool_ptr - 4;
dump_four_ASCII;
print_ln();
print_int(str_ptr);
print(" strings of total length ");
print_int(pool_ptr);
```
