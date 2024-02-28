# Section 963

When the following code comes into play, the pattern $p_1\ldots p_k$ appears in *hc[1 .. k]*, and the corresponding sequence of numbers $n_0\ldots n_k$ appears in *hyf[0 .. k]*.

```c << Insert a new pattern into the linked trie >>=
// << Compute the trie op code, |v|, and set |l = 0| >>
q = 0;
hc[0] = cur_lang;
while (l <= k) {
    c = hc[l];
    incr(l);
    p = trie_l[q];
    first_child = true;
    while (p > 0 && c > trie_c[p]) {
        q = p;
        p = trie_r[q];
        first_child = false;
    }
    if (p == 0 || c < trie_c[p]) {
        // << Insert a new trie node between |q| and |p|, and make |p| point to it >>
    }
    q = p; // now node |q| represents $p_1\ldots p_{l - 1}$
}
if (trie_o[q] != MIN_QUARTERWORD) {
    print_err("Duplicate pattern");
    help1("(See Appendix H.)");
    error();
}
trie_o[q] = v;
```
