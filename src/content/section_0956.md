# Section 956

```c << Pack the family into |trie| relative to |h| >>=
trie_taken[h] = true;
trie_ref[p] = h;
q = p;
do {
    z = h + trie_c[q];
    l = trie_back(z);
    r = trie_link(z);
    trie_back(r) = l;
    trie_link(l) = r;
    trie_link(z) = 0;
    if (l < 256) {
        if (z < 256) {
            ll = z;
        }
        else {
            ll = 256;
        }
        do {
            trie_min[l] = r;
            incr(l);
        } while (l != ll);
    }
    q = trie_r[q];
} while (q != 0);
```
