# Section 563

> ![NOTE]
> String `".tfm"` is added to the pool.

```c << Read the other strings >>+=
put_string(".tfm"); // TFM_EXT: 266
```

```c << Internal strings numbers in the pool >>+=
#define TFM_EXT 266
```

```c << Open |tfm_file| for input >>=
file_opened = false;
if (aire == EMPTY_STRING) {
    pack_file_name(nom, TEX_FONT_AREA, TFM_EXT);
}
else {
    pack_file_name(nom, aire, TFM_EXT);
}
if (!b_open_in(&tfm_file)) {
    abort;
}
file_opened = true;
```
