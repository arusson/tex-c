# Section 950

The compressed trie will be packed into the *trie* array using a "top-down first-fit" procedure.
This is a little tricky, so the reader should pay close attention: The *trie_hash* array is cleared to zero again and renamed *trie_ref* for this phase of the operation; later on, *trie_ref[p]* will be nonzero only if the linked trie node *p* is the smallest character in a family and if the characters *c* of that family have been allocated to locations *trie_ref[p] + c* in the *trie* array.
Locations of *trie* that are in use will have *trie_link = 0*, while the unused holes in *trie* will be doubly linked with *trie_link* pointing to the next larger vacant location and *trie_back* pointing to the next smaller one.
This double linking will have been carried out only as far as *trie_max*, where *trie_max* is the largest index of *trie* that will be needed.
To save time at the low end of the trie, we maintain array entries *trie_min[c]* pointing to the smallest hole that is greater than&nbsp;*c*.
Another array *trie_taken* tells whether or not a given location is equal to *trie_ref[p]* for some *p*; this array is used to ensure that distinct nodes in the compressed trie will have distinct *trie_ref* entries.

```c include/parser.h
#define trie_ref     trie_hash      // where linked trie families go into |trie|
#define trie_back(X) hh_lh(trie[X]) // backward links in |trie| holes
```

```c << Global variables >>+=
#ifdef INIT
// does a family start here?
bool trie_taken0[TRIE_SIZE];
bool *trie_taken = trie_taken0 - 1;
int trie_min[256];   // the first possible slot for each character
int trie_max;        // largest location used in |trie|
bool trie_not_ready; // is the trie still in linked form?
#endif
```
