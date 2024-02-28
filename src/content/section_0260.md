# Section 260

```c << Insert a new control sequence after |p|, then make |p| point to it >>=
if (text(p) > 0) {
    do {
        if (hash_is_full) {
            overflow("hash size", HASH_SIZE);
        }
        decr(hash_used);
    } while (text(hash_used) != 0); // search for an empty location in |hash|
    next(p) = hash_used;
    p = hash_used;
}
str_room(l);
d = cur_length;
while (pool_ptr > str_start[str_ptr]) {
    decr(pool_ptr);
    str_pool[pool_ptr + l] = str_pool[pool_ptr];
} // move current string up to make room for another
for(k = j; k < j + l; k++) {
    append_char(buffer[k]);
}
text(p) = make_string();
pool_ptr += d;
#ifdef STAT
incr(cs_count);
#endif
```
