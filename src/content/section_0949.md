# Section 949

A neat recursive procedure is now able to compress a trie by traversing it and applying *trie_node* to its nodes in "bottom up" fashion.
We will compress the entire trie by clearing *trie_hash* to zero and then saying *'trie_root* &larr; *compress_trie(trie_root)'*.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
int compress_trie(trie_pointer p) {
    if (p == 0) {
        return 0;
    }
    else {
        trie_l[p] = compress_trie(trie_l[p]);
        trie_r[p] = compress_trie(trie_r[p]);
        return trie_node(p);
    }
}
```
