# Section 1303

Corresponding to the procedure that dumps a format file, we have a function that reads one in.
The function returns *false* if the dumped format is incompatible with the present $\TeX$ table sizes, etc.

```c include/io.h
#define too_small(X)                            \
    printf("---! Must increase the %s\n", (X)); \
    goto bad_fmt
```

```c io/dumping.c
bool load_fmt_file() {
    int j, k;      // all-purpose indices
    pointer p, q;  // all-purpose pointers
    int x;         // something undumped
    memory_word w; // four ASCII codes
    // << Undump constants for consistency check >>
    // << Undump the string pool >>
    // << Undump the dynamic memory >>
    // << Undump the table of equivalents >>
    // << Undump the font information >>
    // << Undump the hyphenation tables >>
    // << Undump a couple more things and the closing check word >>
    return true; // it worked!
bad_fmt:
    wterm_ln("(Fatal format file error; I'm stymied)");
    return false;
}
```
