# Section 940

```c << Insert the pair |(s,p)| into the exception table >>=
if (hyph_count == HYPH_SIZE) {
    overflow("exception dictionary", HYPH_SIZE);
}
incr(hyph_count);
while (hyph_word[h] != 0) {
    // << If the string |hyph_word[h]| is less than or equal to |s|, interchange |(hyph_word[h],hyph_list[h])| with |(s,p)| >>
    if (h > 0) {
        decr(h);
    }
    else {
        h = HYPH_SIZE;
    }
}
hyph_word[h] = s;
hyph_list[h] = p;
```
