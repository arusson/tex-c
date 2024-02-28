# Section 1325

Only "nonempty" parts of *op_start* need to be restored.

```c << Undump the hyphenation tables >>=
undump(0, HYPH_SIZE, hyph_count);
for(k = 1; k <= hyph_count; k++) {
    undump(0, HYPH_SIZE, j);
    undump(0, str_ptr, hyph_word[j]);
    undump(MIN_HALFWORD, MAX_HALFWORD, hyph_list[j]);
}
undump_size(0, TRIE_SIZE, "trie size", j);

#ifdef INIT
trie_max = j;
#endif

for(k = 0; k <= j; k++) {
    undump_hh(trie[k]);
}
undump_size(0, TRIE_OP_SIZE, "trie op size", j);

#ifdef INIT
trie_op_ptr = j;
#endif

for(k = 1; k <= j; k++) {
    undump(0, 63, hyf_distance[k]); // a |small_number|
    undump(0, 63, hyf_num[k]);
    undump(MIN_QUARTERWORD, MAX_QUARTERWORD, hyf_next[k]);
}

#ifdef INIT
for(k = 0; k <= 255; k++) {
    trie_used[k] = MIN_QUARTERWORD;
}
#endif

k = 256;
while (j > 0) {
    undump(0, k - 1, k);
    undump(1, j, x);

#ifdef INIT
    trie_used[k] = x;
#endif

    j -= x;
    op_start[k] = j;
}

#ifdef INIT
trie_not_ready = false;
#endif
```
