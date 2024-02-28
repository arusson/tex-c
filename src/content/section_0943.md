# Section 943

Before we discuss trie building in detail, let's consider the simpler problem of creating the *hyf_distance*, *hyf_num*, and *hyf_next* arrays.

Suppose, for example, that $\TeX$ reads the pattern '`ab2cde1`'.
This is a pattern of length 5, with $n_0\ldots n_5 = 0\,0\,2\,0\,0\,1$ in the notation above.
We want the corresponding *trie_op* code *v* to have *hyf_distance[v] = 3*, *hyf_num[v] = 2*, and *hyf_next[v] = v'*, where the auxiliary *trie_op* code *v'* has *hyf_distance[v'] = 0*, *hyf_num[v'] = 1*, and *hyf_next[v'] = MIN_QUARTERWORD*.

$\TeX$ computes an appropriate value *v* with the *new_trie_op*  subroutine below, by setting

<div align="center">

*v'* &larr; *new_trie_op(0, 1, MIN_QUARTERWORD)*,$\qquad$ *v* &larr; *new_trie_op(3, 2,v')*.
</div>
 
This subroutine looks up its three parameters in a special hash table, assigning a new value only if these three have not appeared before for the current language.

The hash table is called *trie_op_hash*, and the number of entries it contains is *trie_op_ptr*.

```c << Global variables >>+=
#ifdef INIT
// trie op codes for quadruples
int trie_op_hash0[2*TRIE_OP_SIZE + 1];
int *trie_op_hash = trie_op_hash0 + TRIE_OP_SIZE;

// largest opcode used so far for this language
quarterword trie_used[256];

// language part of a hashed quadruple
ASCII_code trie_op_lang0[TRIE_OP_SIZE];
ASCII_code *trie_op_lang = trie_op_lang0 - 1;

// opcode corresponding to a hashed quadruple
quarterword trie_op_val0[TRIE_OP_SIZE];
quarterword *trie_op_val = trie_op_val0 - 1;

// number of stored ops so far
int trie_op_ptr;
#endif
```
