# Section 954


By making sure that *trie_max* is at least *h + 256*, we can be sure that *trie_max* $>$ *z*, since *h = z − c*.
It follows that location *trie_max* will never be occupied in *trie*, and we will have *trie_max* $\geq$ *trie_link(z)*.

```c << Ensure that |trie_max >= h + 256| >>=
if (trie_max < h + 256) {
    if (TRIE_SIZE <= h + 256) {
        overflow("pattern memory", TRIE_SIZE);
    }
    do {
        incr(trie_max);
        trie_taken[trie_max] = false;
        trie_link(trie_max) = trie_max + 1;
        trie_back(trie_max) = trie_max - 1;
    } while (trie_max != h + 256);
}
```
