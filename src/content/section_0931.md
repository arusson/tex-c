# Section 931

```c << If the string |hyph_word[h]| is less than |hc[1..hn]|, |goto not_found|; but if the two strings are equal, set |hyf| to the hyphen positions and |goto found| >>=
k = hyph_word[h];
if (k == 0 || length(k) < hn) {
    goto not_found;
}
if (length(k) == hn) {
    j = 1;
    u = str_start[k];
    do {
        if (str_pool[u] < hc[j]) {
            goto not_found;
        }
        if (str_pool[u] > hc[j]) {
            goto done;
        }
        incr(j);
        incr(u);
    } while (j <= hn);
    // << Insert hyphens as specified in |hyph_list[h]| >>
    decr(hn);
    goto found;
}
done:
```
