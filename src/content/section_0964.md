# Section 964

```c << Insert a new trie node between |q| and |p|, and make |p| point to it >>=
if (trie_ptr == TRIE_SIZE) {
    overflow("pattern memory", TRIE_SIZE);
}
incr(trie_ptr);
trie_r[trie_ptr] = p;
p = trie_ptr;
trie_l[p] = 0;
if (first_child) {
    trie_l[q] = p;
}
else {
    trie_r[q] = p;
}
trie_c[p] = c;
trie_o[p] = MIN_QUARTERWORD;
```
