# Section 1305

Format files consist of *memory_word* items, and we use the following macros to dump words of different types:

> ![NOTE]
> A *memory_word* is 8 bytes long and an integer is 4 bytes in this implementation.
> 
> *dump_hh* and *dump_qqqq* are equivalents to *dump_wd* since those are the same in this implementation (based on a `union`, see section [113](./part08.md#section-113)).

```c include/io.h
#define dump_wd(X)  fwrite(&X, 8, 1, fmt_file)
#define dump_int(X) putw((X), fmt_file)
#define dump_hh     dump_wd
#define dump_qqqq   dump_wd
```

```c << Global variables >>+=
word_file fmt_file; // for input or output of format information
```
