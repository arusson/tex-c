# Section 952

Here is how the trie-compression data structures are initialized.
If storage is tight, it would be possible to overlap *trie_op_hash*, *trie_op_lang*, and *trie_op_val* with *trie*, *trie_hash*, and *trie_taken*, because we finish with the former just before we need the latter.

```c << Get ready to compress the trie >>=
// << Sort the hyphenation op tables into proper order >>
for(p = 0; p <= TRIE_SIZE; p++) {
    trie_hash[p] = 0;
}
trie_root = compress_trie(trie_root); // identify equivalent subtries
for(p = 0; p <= trie_ptr; p++) {
    trie_ref[p] = 0;
}
for(p = 0; p <= 255; p++) {
    trie_min[p] = p + 1;
}
trie_link(0) = 1;
trie_max = 0;
```
