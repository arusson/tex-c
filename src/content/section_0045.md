# Section 45

The following subroutine compares string *s* with another string of the same length that appears in *buffer* starting at position *k*;
the result is *true* if and only if the strings are equal.
Empirical tests indicate that *str_eq_buf* is used in such a way that it tends to return *true* about 80 percent of the time.

```c strings.c
// test equality of strings
int str_eq_buf(str_number s, int k) {
    pool_pointer j;     // running index
    bool result = true; // result of comparison;
    j = str_start[s];
    while (j < str_start[s + 1]) {
        if (str_pool[j] != buffer[k]) {
            result = false;
            break; // Goto not_found
        }
        incr(j);
        incr(k);
    }
    // not_found:
    return result;
}
```