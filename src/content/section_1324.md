# Section 1324

```c << Dump the hyphenation tables >>=
dump_int(hyph_count);
for(k = 0; k <= HYPH_SIZE; k++) {
    if (hyph_word[k] != 0) {
        dump_int(k);
        dump_int(hyph_word[k]);
        dump_int(hyph_list[k]);
    }
}
print_ln();
print_int(hyph_count);
print(" hyphenation exception");
if (hyph_count != 1) {
    print_char('s');
}
if (trie_not_ready) {
    init_trie();
}
dump_int(trie_max);
for(k = 0; k <= trie_max; k++) {
    dump_hh(trie[k]);
}
dump_int(trie_op_ptr);
for(k = 1; k <= trie_op_ptr; k++) {
    dump_int(hyf_distance[k]);
    dump_int(hyf_num[k]);
    dump_int(hyf_next[k]);
}
print_nl("Hyphenation trie of length ");
print_int(trie_max);
print(" has ");
print_int(trie_op_ptr);
print(" op");
if (trie_op_ptr != 1) {
    print_char('s');
}
print(" out of ");
print_int(TRIE_OP_SIZE);
for(k = 255; k>= 0; k--) {
    if (trie_used[k] > MIN_QUARTERWORD) {
        print_nl("  ");
        print_int(trie_used[k]);
        print(" for language ");
        print_int(k);
        dump_int(k);
        dump_int(trie_used[k]);
    }
}
```
