# Section 930

First we compute the hash code *h*, then we search until we either find the word or we don't.
Words from different languages are kept separate by appending the language code to the string.

```c << Look for the word |hc[1..hn]| in the exception table, and |goto found| (with |hyf| containing the hyphens) if an entry is found >>=
h = hc[1];
incr(hn);
hc[hn] = cur_lang;
for(j = 2; j <= hn; j++) {
    h = (h + h + hc[j]) % HYPH_SIZE;
}
while(true) {
    // << If the string |hyph_word[h]| is less than |hc[1..hn]|, |goto not_found|; but if the two strings are equal, set |hyf| to the hyphen positions and |goto found| >>
    if (h > 0) {
        decr(h);
    }
    else {
        h = HYPH_SIZE;
    }
}
not_found:
decr(hn);
```
