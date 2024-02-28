# Section 113

The reader should study the following definitions closely:

> ![NOTE]
> 
> *quarterword* is 16 bits, *halfword* is 32 bits, and a full *memory_word* is 64 bits.
> The `.int` accessor is renamed `.integer` for obvious reason.
> (Note that *integer* and *sc* are only 32 bits long, so it does not use the full 64 bits of a *memory_word*.)
>
> Instead of using different types of structures (*two_choices*, *four_choices*, *two_halves*, and *four_quarters*), some members directly through macros *qqqq_b0*, etc.

```c << Types in the outer block >>+=
typedef uint16_t quarterword; // 1/4 of a word
typedef int32_t halfword;     // 1/2 of a word

typedef union {
    int         integer;
    scaled      sc;
    glue_ratio  gr;
    halfword    hh[2];
    quarterword qqqq[4];
} memory_word;

typedef FILE* word_file;
```

```c include/datastructures.h
// << Start file |datastructures.h| >>

#define qqqq_b0(W) (W).qqqq[0]
#define qqqq_b1(W) (W).qqqq[1]
#define qqqq_b2(W) (W).qqqq[2]
#define qqqq_b3(W) (W).qqqq[3]
#define hh_b0(W)   qqqq_b0((W))
#define hh_b1(W)   qqqq_b1((W))
#define hh_lh(W)   (W).hh[0]
#define hh_rh(W)   (W).hh[1]
```
