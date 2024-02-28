# Section 46

Here is a similar routine, but it compares two strings in the string pool, and it does not assume that they have the same length.

```c strings.c
// test equality of strings
int str_eq_str(str_number s, str_number t) {
    pool_pointer j, k;   // running indices
    bool result = false; // result of comparison
    if (length(s) != length(t)) {
        goto not_found;
    }
    j = str_start[s];
    k = str_start[t];
    while (j < str_start[s + 1]) {
        if (str_pool[j] != str_pool[k]) {
            goto not_found;
        }
        incr(j);
        incr(k);
    }
    result = true;
not_found:
    return result;
}
```
