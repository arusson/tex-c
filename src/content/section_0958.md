# Section 958

When the whole trie has been allocated into the sequential table, we must go through it once again so that *trie* contains the correct information.
Null pointers in the linked trie will be represented by the value&nbsp;0, which properly implements an "empty" family.

```c << Move the data into |trie| >>=
hh_rh(h) = 0;
hh_b0(h) = MIN_QUARTERWORD;
hh_b1(h) = MIN_QUARTERWORD; // |trie_link = 0|, |trie_op = MIN_QUARTERWORD|, |trie_char = 0|
if (trie_root == 0) {
    // no patterns were given
    for(r = 0; r <= 256; r++) {
        trie[r] = h;
    }
    trie_max = 256;
}
else {
    trie_fix(trie_root); // this fixes the non-holes in |trie|
    r = 0; // now we will zero out all the holes
    do {
        s = trie_link(r);
        trie[r] = h;
        r = s;
    } while (r <= trie_max);
}
trie_char(0) = '?'; // make |trie_char(c) != c| for all |c|
```
