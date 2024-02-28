# Section 941

```c << If the string |hyph_word[h]| is less than or equal to |s|, interchange |(hyph_word[h],hyph_list[h])| with |(s,p)| >>=
k = hyph_word[h];
if (length(k) < length(s)) {
    goto found;
}
if (length(k) > length(s)) {
    goto not_found;
}
u = str_start[k];
v = str_start[s];
do {
    if (str_pool[u] < str_pool[v]) {
        goto found;
    }
    if (str_pool[u] > str_pool[v]) {
        goto not_found;
    }
    incr(u);
    incr(v);
} while (u != str_start[k + 1]);
found:
q = hyph_list[h];
hyph_list[h] = p;
p = q;
t = hyph_word[h];
hyph_word[h] = s;
s = t;
not_found:
```
