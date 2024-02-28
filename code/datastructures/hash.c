// ~~~ Section 259 ~~~
// ~~~ Start file |hash.c|, 1382 ~~~
#ifdef INIT
#include <string.h>
#endif
#include "datastructures.h"
#include "texerror.h"
#include "strings.h"
// ~~~ End section 1382 ~~~

// search the hash table
pointer id_lookup(int j, int l) {
    int h;     // hash code
    int d;     // number of characters in incomplete current string
    pointer p; // index in |hash| array
    pointer k; // index in |buffer| array

    // ~~~ Compute the hash code |h|, 261 ~~~
    h = buffer[j];
    for(k = j + 1; k < j + l; k++) {
      h = (h + h + buffer[k]) % HASH_PRIME;
    }
    // ~~~ End section 261 ~~~
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
                // ~~~ Insert a new control sequence after |p|, then make |p| point to it, 260 ~~~
                if (text(p) > 0) {
                    do {
                        if (hash_is_full) {
                            overflow("hash size", HASH_SIZE);
                        }
                        decr(hash_used);
                    } while (text(hash_used) != 0); // search for an empty location in |hash|
                    next(p) = hash_used;
                    p = hash_used;
                }
                str_room(l);
                d = cur_length;
                while (pool_ptr > str_start[str_ptr]) {
                    decr(pool_ptr);
                    str_pool[pool_ptr + l] = str_pool[pool_ptr];
                } // move current string up to make room for another
                for(k = j; k < j + l; k++) {
                    append_char(buffer[k]);
                }
                text(p) = make_string();
                pool_ptr += d;
#ifdef STAT
                incr(cs_count);
#endif
                // ~~~ End section 260 ~~~
            }
            break; // Goto found
        }
        p = next(p);
    }
    // found:
    return p;
}
// ~~~ End section 259 ~~~

// ~~~ Section 264 ~~~
// We take a `char *` as input instead of a pool number
#ifdef INIT
void primitive(char *s, quarterword c, halfword o) {
    int l = strlen(s);
    if (l == 1) {
        cur_val = s[0] + SINGLE_BASE;
    }
    else {
        memcpy(buffer, s, l); // we move |s| into the (empty) |buffer|
        cur_val = id_lookup(0, l); // |no_new_control_sequence| is |false|
    }
    eq_level(cur_val) = LEVEL_ONE;
    eq_type(cur_val) = c;
    equiv(cur_val) = o;
}
#endif
// ~~~ End section 264 ~~~
