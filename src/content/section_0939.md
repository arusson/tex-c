# Section 939

```c << Enter a hyphenation exception >>=
incr(n);
hc[n] = cur_lang;
str_room(n);
h = 0;
for(j = 1; j <= n; j++) {
    h = (h + h + hc[j]) % HYPH_SIZE;
    append_char(hc[j]);
}
s = make_string();
// << Insert the pair |(s,p)| into the exception table >>
```
