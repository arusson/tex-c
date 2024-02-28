# Section 957

To pack the entire linked trie, we use the following recursive procedure.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
// pack subtries of a family
void trie_pack(trie_pointer p) {
    int q; // a local variable that need not be saved on recursive calls
    do {
        q = trie_l[p];
        if (q > 0 && trie_ref[q] == 0) {
            first_fit(q);
            trie_pack(q);
        }
        p = trie_r[p];
    } while (p != 0);
}
```
