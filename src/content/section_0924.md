# Section 924

```c << Store maximum values in the |hyf| table >>=
v = trie_op(z);
do {
    v += op_start[cur_lang];
    i = l - hyf_distance[v];
    if (hyf_num[v] > hyf[i]) {
        hyf[i] = hyf_num[v];
    }
    v = hyf_next[v];
} while (v != MIN_QUARTERWORD);
```
