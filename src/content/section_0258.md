# Section 258

> ![NOTE]
> The `"notexpanded:"` string must be added in the string pool.

```c << Read the other strings >>+=
put_string("notexpanded:"); // NOTEXPANDED_STRING: 257
```

```c << Internal strings numbers in the pool >>+=
#define NOTEXPANDED_STRING 257
```

```c << Initialize table entries (done by INITEX only) >>+=
hash_used = FROZEN_CONTROL_SEQUENCE; // nothing is used
cs_count = 0;
eq_type(FROZEN_DONT_EXPAND) = DONT_EXPAND;
text(FROZEN_DONT_EXPAND) = NOTEXPANDED_STRING;
```
