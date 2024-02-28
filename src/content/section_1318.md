# Section 1318

A different scheme is used to compress the hash table, since its lower
region is usually sparse.
When *text(p)* $\ne$ 0 for *p* $\leq$ *hash_used*, we output two words, *p* and *hash[p]*.
The hash table is, of course, densely packed for *p* $\geq$ *hash_used*, so the remaining entries are output in a block.

```c << Dump the hash table >>=
dump_int(hash_used);
cs_count = FROZEN_CONTROL_SEQUENCE - 1 - hash_used;
for(p = HASH_BASE; p <= hash_used; p++) {
    if (text(p) != 0) {
        dump_int(p);
        dump_hh(hash[p]);
        incr(cs_count);
    }
}
for(p = hash_used + 1; p <= UNDEFINED_CONTROL_SEQUENCE - 1; p++) {
    dump_hh(hash[p]);
}
dump_int(cs_count);
print_ln();
print_int(cs_count);
print(" multiletter control sequences");
```
