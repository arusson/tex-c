# Section 108

The next subroutine is used to compute the "badness" of glue, when a total *t* is supposed to be made from amounts that sum to *s*.
According to *The TeXbook*, the badness of this situation is $100(t/s)^3$;
however, badness is simply a heuristic, so we need not squeeze out the last drop of accuracy when computing it.
All we really want is an approximation that has similar properties.

The actual method used to compute the badness is easier to read from the program than to describe in words.
It produces an integer value that is a reasonably close approximation to $100(t/s)^3$, and all implementations of $\TeX$ should use precisely this method.
Any badness of $2^{13}$ or more is treated as infinitely bad, and represented by 10000.

It is not difficult to prove that

<div align="center">

*badness*(*t* + 1, *s*) $\geq$ *badness*(*t*, *s*) $\geq$ *badness*(*t*, *s* + 1).
</div>

The badness function defined here is capable of computing at most 1095 distinct values, but that is plenty.

```c include/constants.h
#define INF_BAD 10000 // infinitely bad value
```

```c arithmetic.c
// compute badness, given |t >= 0|
halfword badness(scaled t, scaled s) {
    int r; // approximation to \alpha*t/s, where alpha^3\approx 100*2^{18}
    halfword badness;
    if (t == 0) {
        badness = 0;
    }
    else if (s <= 0) {
        badness = INF_BAD;
    }
    else {
        if (t <= 7230584) {
            r = (t * 297) / s; // 297^3 = 99.94 * 2^{18}
        }
        else if (s >= 1663497) {
            r = t / (s / 297);
        }
        else {
            r = t;
        }

        if (r > 1290) {
            badness = INF_BAD; // 1290^3 < 2^{31} < 1291^3
        }
        else {
            badness = (r*r*r + 0x20000) / 0x40000;
        }
    } // that was r^3/2^{18}, rounded to the nearest integer
    return badness;
}
```
