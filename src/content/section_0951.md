# Section 951

Each time `\patterns` appears, it contributes further patterns to the future trie, which will be built only when hyphenation is attempted or when a format file is dumped.
The boolean variable *trie_not_ready* will change to *false* when the trie is compressed; this will disable further patterns.

```c << Initialize table entries (done by INITEX only) >>+=
trie_not_ready = true;
trie_root = 0;
trie_c[0] = 0;
trie_ptr = 0;
```
