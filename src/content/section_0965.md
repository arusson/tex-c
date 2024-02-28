# Section 965

```c << Compute the trie op code, |v|, and set |l = 0| >>=
if (hc[1] == 0) {
    hyf[0] = 0;
}
if (hc[k] == 0) {
    hyf[k] = 0;
}
l = k;
v = MIN_QUARTERWORD;
while(true) {
    if (hyf[l] != 0) {
        v = new_trie_op(k - l, hyf[l], v);
    }
    if (l > 0) {
        decr(l);
    }
    else {
        break; // goto done1
    }
}
// done1:
```
