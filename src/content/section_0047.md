# Section 47

The initial values of *str_pool*, *str_start*, *pool_ptr*, and *str_ptr* are computed by the `INITEX` program, based in part on the information that `WEB` has output while processing $\TeX$.

> ![NOTE]
> Most of the internal strings in the source code are treated as `char *` instead of using the `TEX.POOL` file that `WEB` creates while tangling.
> Though, some of them are still needed in *str_pool* which is taken care of in ⟨&nbsp;Read the other strings [51](./part04.md#section-51)&nbsp;⟩.

```c strings.c
#ifdef INIT
// initializes the string pool
void get_strings_started() {
    int k, l; // small indices or counters
    pool_ptr = 0;
    str_ptr = 0;
    str_start[0] = 0;
    // << Make the first 256 strings >>
    // << Read the other strings >>
}
#endif
```