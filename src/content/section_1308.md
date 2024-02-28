# Section 1308

Sections of a `WEB` program that are "commented out" still contribute strings to the string pool; therefore `INITEX` and $\TeX$ will have the same strings.
(And it is, of course, a good thing that they do.)

```c << Undump constants for consistency check >>=
undump_int(x);
if (x != 0) {
    goto bad_fmt; // check that strings are the same
}
undump_int(x);
if (x != MEM_BOT) {
    goto bad_fmt;
}
undump_int(x);
if (x != MEM_TOP) {
    goto bad_fmt;
}
undump_int(x);
if (x != EQTB_SIZE) {
    goto bad_fmt;
}
undump_int(x);
if (x != HASH_PRIME) {
    goto bad_fmt;
}
undump_int(x);
if (x != HYPH_SIZE) {
    goto bad_fmt;
}
```
