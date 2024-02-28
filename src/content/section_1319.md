# Section 1319

```c << Undump the hash table >>=
undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, hash_used);
p = HASH_BASE - 1;
do {
    undump(p + 1, hash_used, p);
    undump_hh(hash[p]);
} while (p != hash_used);
for(p = hash_used + 1; p <= UNDEFINED_CONTROL_SEQUENCE - 1; p++) {
    undump_hh(hash[p]);
}
undump_int(cs_count);
```
