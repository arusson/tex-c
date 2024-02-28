# Section 421

Inside an `\output` routine, a user may wish to look at the page totals that were present at the moment when output was triggered.

```c include/constants.h
#define MAX_DIMEN 0x3fffffff // 2^{30} - 1
```

```c << Fetch something on the |page_so_far| >>=
if (page_contents == EMPTY && !output_active) {
    if (m == 0) {
        cur_val = MAX_DIMEN;
    }
    else {
        cur_val = 0;
    }
}
else {
    cur_val = page_so_far[m];
}
cur_val_level = DIMEN_VAL;
```
