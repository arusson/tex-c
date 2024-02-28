# Section 1301

> ![NOTE]
> String `" (INITEX)"` must be added to the pool.

```c << Read the other strings >>+=
put_string(" (INITEX)"); // INITEX_IDENT_STRING: 270
```

```c << Internal strings numbers in the pool >>+=
#define INITEX_IDENT_STRING 270
```

```c << Initialize table entries (done by INITEX only) >>+=
format_ident = INITEX_IDENT_STRING; // " (INITEX)"
```
