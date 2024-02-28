# Section 948

Let us suppose that a linked trie has already been constructed.
Experience shows that we can often reduce its size by recognizing common subtries; therefore another hash table is introduced for this purpose, somewhat similar to *trie_op_hash*.
The new hash table will be initialized to zero.

The function *trie_node(p)* returns *p* if *p* is distinct from other that it has seen, otherwise it returns the number of the first equivalent node that it has seen.

Notice that we might make subtries equivalent even if they correspond to patterns for different languages, in which the trie ops might mean quite different things.
That's perfectly all right.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
// converts to a canonical form
int trie_node(trie_pointer p) {
    int h; // trial hash location
    int q; // trial trie node
    h = abs(trie_c[p] + 1009*trie_o[p] + 2718*trie_l[p] + 3142*trie_r[p]) % TRIE_SIZE;
    while(true) {
        q = trie_hash[h];
        if (q == 0) {
            trie_hash[h] = p;
            return p;
        }
        if (trie_c[q] == trie_c[p]
            && trie_o[q] == trie_o[p]
            && trie_l[q] == trie_l[p]
            && trie_r[q] == trie_r[p])
        {
            return q;
        }
        if (h > 0) {
            decr(h);
        }
        else {
            h = TRIE_SIZE;
        }
    }
}
```
