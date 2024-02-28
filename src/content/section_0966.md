# Section 966

Finally we put everything together: Here is how the trie gets to its final, efficient form.
The following packing routine is rigged so that the root of the linked tree gets mapped into location 1 of *trie*, as required by the hyphenation algorithm.
This happens because the first call of *first_fit* will "take" location&nbsp;1.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
void init_trie() {
    int p;         // pointer for initialization
    int j, k, t;   // all-purpose registers for initialization
    int r, s;      // used to clean up the packed |trie|
    memory_word h; // template used to zero out |trie|'s holes
    
    // << Get ready to compress the trie >>
    if (trie_root != 0) {
        first_fit(trie_root);
        trie_pack(trie_root);
    }
    // << Move the data into |trie| >>
    trie_not_ready = false;
}
```
