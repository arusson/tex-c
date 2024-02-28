# Section 259

Here is the subroutine that searches the hash table for an identifier that matches a given string of length *l* $>$ *1* appearing in *buffer[j .. (j + l − 1)]*.
If the identifier is found, the corresponding hash table address is returned.
Otherwise, if the global variable *no_new_control_sequence* is *true*, the dummy address *UNDEFINED_CONTROL_SEQUENCE* is returned.
Otherwise the identifier is inserted into the hash table and its location is returned.

```c datastructures/hash.c
// << Start file |hash.c| >>

// search the hash table
pointer id_lookup(int j, int l) {
    int h;     // hash code
    int d;     // number of characters in incomplete current string
    pointer p; // index in |hash| array
    pointer k; // index in |buffer| array

    // << Compute the hash code |h| >>
    p = h + HASH_BASE; // we start searching here; note that |0 <= h < HASH_PRIME|
    while (true) {
        if (text(p) > 0
            && length(text(p)) == l
            && str_eq_buf(text(p), j))
        {
            break; // Goto found
        }
        if (next(p) == 0) {
            if (no_new_control_sequence) {
                p = UNDEFINED_CONTROL_SEQUENCE;
            }
            else {
                // << Insert a new control sequence after |p|, then make |p| point to it >>
            }
            break; // Goto found
        }
        p = next(p);
    }
    // found:
    return p;
}
```
