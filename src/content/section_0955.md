# Section 955

```c << If all characters of the family fit relative to |h|, then |goto found|, otherwise |goto not_found| >>=
q = trie_r[p];
while (q > 0) {
    if (trie_link(h + trie_c[q]) == 0) {
        goto not_found;
    }
    q = trie_r[q];
}
goto found;
```
