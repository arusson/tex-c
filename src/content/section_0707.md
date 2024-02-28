# Section 707

The search process is complicated slightly by the facts that some of the characters might not be present in some of the fonts, and they might not be probed in increasing order of height.

```c << Look at the variants of |(z, x)|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered >>
if (z != 0 || x != MIN_QUARTERWORD) {
    z += s + 16;
    do {
        z -= 16;
        g = fam_fnt(z);
        if (g != NULL_FONT) {
            // << Look at the list of characters starting with |x| in font |g|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered >>
        }
    } while (z >= 16);
}
```
