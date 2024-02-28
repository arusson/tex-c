# Section 1304

The user is not allowed to dump a format file unless *save_ptr = 0*.
This condition implies that *cur_level = LEVEL_ONE*, hence the *xeq_level* array is constant and it need not be dumped.

```c << If dumping is not allowed, abort >>=
if (save_ptr != 0) {
    print_err("You can't dump inside a group");
    help1("`{...\\dump}' is a no-no.");
    succumb();
}
```
