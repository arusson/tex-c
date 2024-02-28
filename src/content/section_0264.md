# Section 264

We need to put $\TeX$'s "primitive" control sequences into the hash table, together with their command code (which will be the *eq_type*) and an operand (which will be the *equiv*).
The *primitive* procedure does this, in a way that no $\TeX$ user can.
The global value *cur_val* contains the new *eqtb* pointer after *primitive* has acted.

> ![NOTE]
> *id_lookup* inserts in *str_pool* the control sequence.
> Since `TEX.POOL` file is not used, it is the first and only insertion in the pool, so *flush_string* is not needed here.

```c datastructures/hash.c
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
```
