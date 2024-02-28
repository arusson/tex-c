# Section 921

```c include/breaker.h
#define trie_link(X) hh_rh(trie[(X)]) // "downward" link in a trie
#define trie_char(X) hh_b1(trie[(X)]) // character matched at this trie location
#define trie_op(X)   hh_b0(trie[(X)]) // program for hyphenation at this trie location
```

```c << Global variables >>+=
// |trie_link|, |trie_char|, |trie_op|
memory_word trie[TRIE_SIZE + 1];

// position |k - j| of $n_j$
small_number hyf_distance0[TRIE_OP_SIZE];
small_number *hyf_distance = hyf_distance0 - 1; 

// value of $n_j$
small_number hyf_num0[TRIE_OP_SIZE];
small_number *hyf_num = hyf_num0 - 1;

// continuation code
quarterword hyf_next0[TRIE_OP_SIZE];
quarterword *hyf_next = hyf_next0 - 1;

// offset for current language
int op_start[256];
```

