# Section 1250

New hyphenation data is loaded by the *HYPH_DATA* command.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("hyphenation", HYPH_DATA, 0);
primitive("patterns", HYPH_DATA, 1);
```
