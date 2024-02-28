# Section 929

The algorithm for exception lookup is quite simple, as soon as we have a few more local variables to work with.

```c << Local variables for hyphenation >>+=
int h;          // an index into |hyph_word| and |hyph_list|
str_number k;   // an index into |str_start|
pool_pointer u; // an index into |str_pool|
```
