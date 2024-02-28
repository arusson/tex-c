# Section 900: Post-hyphenation

If a hyphen may be inserted between *hc[j]* and *hc[j + 1]*, the hyphenation procedure will set *hyf[j]* to some small odd number.
But before we look at $\TeX$'s hyphenation procedure, which is independent of the rest of the line-breaking algorithm, let us consider what we will do with the hyphens it finds, since it is better to work on this part of the program before forgetting what *ha* and *hb*, etc., are all about.

```c << Global variables >>+=
quarterword hyf[65]; // odd values indicate discretionary hyphens
pointer init_list;   // list of punctuation characters preceding the word
bool init_lig;       // does |init_list| represent a ligature?
bool init_lft;       // if so, did the ligature involve a left boundary?
```
