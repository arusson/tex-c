# Section 932

```c << Insert hyphens as specified in |hyph_list[h]| >>=
s = hyph_list[h];
while (s != null) {
    hyf[info(s)] = 1;
    s = link(s);
}
```
