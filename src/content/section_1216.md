# Section 1216

> ![NOTE]
> String `"inaccessible"` must be added to the pool.

```c << Read the other strings >>+=
put_string("inaccessible"); // INACCESSIBLE_STRING: 268
```

```c << Internal strings numbers in the pool >>+=
#define INACCESSIBLE_STRING 268
```

```c << Initialize table entries (done by INITEX only) >>+=
text(FROZEN_PROTECTION) = INACCESSIBLE_STRING;
```
