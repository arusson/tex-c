# Section 959

The fixing-up procedure is, of course, recursive.
Since the linked trie usually has overlapping subtries, the same data may be moved several times; but that causes no harm, and at most as much work is done as it took to build the uncompressed trie.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
// moves |p| and its siblings into |trie|
void trie_fix(trie_pointer p) {
    int q;        // a local variable that need not be saved on recursive calls
    ASCII_code c; // another one that need not be saved
    int z;        // |trie| reference; this local variable must be saved
    z = trie_ref[p];
    do {
        q = trie_l[p];
        c = trie_c[p];
        trie_link(z + c) = trie_ref[q];
        trie_char(z + c) = c;
        trie_op(z + c) = trie_o[p];
        if (q > 0) {
            trie_fix(q);
        }
        p = trie_r[p];
    } while (p != 0);
}
```
