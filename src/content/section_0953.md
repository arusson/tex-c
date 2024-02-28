# Section 953

The *first_fit* procedure finds the smallest hole *z* in *trie* such that a trie family starting at a given node *p* will fit into vacant positions starting at *z*.
If *c = trie_c[p]*, this means that location *z - c* must not already be taken by some other family, and that *z − c + c'* must be vacant for all characters *c'* in the family.
The procedure sets *trie_ref[p]* to *z − c* when the first fit has been found.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
// packs a family into |trie|
void first_fit(trie_pointer p) {
    int h;        // candidate for |trie_ref[p]|
    int z;        // runs through holes
    int q;        // runs through the family starting at |p|
    ASCII_code c; // smallest character in the family
    int l, r;     // left and right neighbors
    int ll;       // upper limit of |trie_min| updating
    c = trie_c[p];
    z = trie_min[c]; // get the first conceivably good hole
    while(true) {
        h = z - c;
        // << Ensure that |trie_max >= h + 256| >>
        if (trie_taken[h]) {
            goto not_found;
        }
        // << If all characters of the family fit relative to |h|, then |goto found|, otherwise |goto not_found| >>
not_found:
        z = trie_link(z); // move to the next hole
    }
found:
    // << Pack the family into |trie| relative to |h| >>
}
```
