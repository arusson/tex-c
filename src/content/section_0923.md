# Section 923

Assuming that these auxiliary tables have been set up properly, the hyphenation algorithm is quite short.
In the following code we set *hc[hn + 2]* to the impossible value 256, in order to guarantee that *hc[hn + 3]* will never be fetched.

```c << Find hyphen locations for the word in |hc|, or |return| >>=
for(j = 0; j <= hn; j++) {
    hyf[j] = 0;
}
// << Look for the word |hc[1..hn]| in the exception table, and |goto found| (with |hyf| containing the hyphens) if an entry is found >>
if (trie_char(cur_lang + 1) != cur_lang) {
    return; // no patterns for |cur_lang|
}
hc[0] = 0;
hc[hn + 1] = 0;
hc[hn + 2] = 256; // insert delimiters
for(j = 0; j <= hn - r_hyf + 1; j++) {
    z = trie_link(cur_lang + 1) + hc[j];
    l = j;
    while (hc[l] == trie_char(z)) {
        if (trie_op(z) != MIN_QUARTERWORD) {
            // << Store maximum values in the |hyf| table >>
        }
        incr(l);
        z = trie_link(z) + hc[l];
    }
}
found:
for(j = 0; j <= l_hyf - 1; j++) {
    hyf[j] = 0;
}
for(j = 0; j <= r_hyf - 1; j++) {
    hyf[hn - j] = 0;
}
```
