# Section 913

When the following code is performed, *hyf[0]* and *hyf[hn]* will be zero.

```c << Reconstitute nodes for the hyphenated word, inserting discretionary hyphens >>=
do {
    l = j;
    j = reconstitute(j, hn, bchar, hyf_char) + 1;
    if (hyphen_passed == 0) {
        link(s) = link(HOLD_HEAD);
        while (link(s) > null) {
            s = link(s);
        }
        if (odd(hyf[j - 1])) {
            l = j;
            hyphen_passed = j - 1;
            link(HOLD_HEAD) = null;
        }
    }
    if (hyphen_passed > 0) {
        // << Create and append a discretionary node as an alternative to the unhyphenated word, and continue to develop both branches until they become equivalent >>
    }
} while (j <= hn);
link(s) = q;
```
