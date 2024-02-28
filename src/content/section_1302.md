# Section 1302

```c io/dumping.c
#ifdef INIT
void store_fmt_file() {
    int j, k, l;   // all-purpose indices
    pointer p, q;  // all-purpose pointers
    int x;         // something to dump
    memory_word w; // four ASCII codes
    // << If dumping is not allowed, abort >>
    // << Create the |format_ident|, open the format file, and inform the user that dumping has begun >>
    // << Dump constants for consistency check >>
    // << Dump the string pool >>
    // << Dump the dynamic memory >>
    // << Dump the table of equivalents >>
    // << Dump the font information >>
    // << Dump the hyphenation tables >>
    // << Dump a couple more things and the closing check word >>
    // << Close the format file >>
}
#endif
```
