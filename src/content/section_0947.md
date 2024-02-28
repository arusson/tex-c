# Section 947

The linked trie that is used to preprocess hyphenation patterns appears in several global arrays.
Each node represents an instruction of the form "if you see character *c*, then perform operation *o*, move to the next character, and go to node *l*; otherwise go to node *r*".
The four quantities *c*, *o*, *l*, and *r* are stored in four arrays *trie_c*, *trie_o*, *trie_l*, and *trie_r*.
The root of the trie is *trie_l[0]*, and the number of nodes is *trie_ptr*.
Null trie pointers are represented by zero.
To initialize the trie, we simply set *trie_l[0]* and *trie_ptr* to zero.
We also set *trie_c[0]* to some arbitrary value, since the algorithm may access it.

The algorithms maintain the condition

<div align="center">

*trie_c[trie_r[z]]* $>$ *trie_c[z]* $\qquad$ whenever *z* $\ne$ *0* and *trie_r[z]* $\ne$ *0*;
</div>

in other words, sibling nodes are ordered by their *c* fields.

```c include/parser.h
#define trie_root trie_l[0] // root of the linked trie
```

```c << Global variables >>+=
#ifdef INIT
// characters to match
unsigned char trie_c[TRIE_SIZE + 1];

// operations to perform
quarterword trie_o[TRIE_SIZE + 1];

// left subtrie links
int trie_l[TRIE_SIZE + 1];

// right subtrie links
int trie_r[TRIE_SIZE + 1];

// the number of nodes in the trie
int trie_ptr; 

// used to identify equivalent subtries
int trie_hash[TRIE_SIZE + 1];
#endif
```
