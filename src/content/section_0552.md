# Section 552

$\TeX$ always knows at least one font, namely the null font.
It has no characters, and its seven parameters are all equal to zero.

> ![NOTE]
> String `"nullfont"` is added to the pool.

```c << Read the other strings >>+=
put_string("nullfont"); // NULLFONT_STRING: 265
```

```c << Internal strings numbers in the pool >>+=
#define NULLFONT_STRING 265
```

```c << Initialize table entries (done by INITEX only) >>+=
font_ptr = NULL_FONT;
fmem_ptr = 7;
font_name[NULL_FONT] = NULLFONT_STRING;
font_area[NULL_FONT] = EMPTY_STRING;
hyphen_char[NULL_FONT] = '-';
skew_char[NULL_FONT] = -1;
bchar_label[NULL_FONT] = NON_ADDRESS;
font_bchar[NULL_FONT] = NON_CHAR;
font_false_bchar[NULL_FONT] = NON_CHAR;
font_bc[NULL_FONT] = 1;
font_ec[NULL_FONT] = 0;
font_size[NULL_FONT] = 0;
font_dsize[NULL_FONT] = 0;
char_base[NULL_FONT] = 0;
width_base[NULL_FONT] = 0;
height_base[NULL_FONT] = 0;
depth_base[NULL_FONT] = 0;
italic_base[NULL_FONT] = 0;
lig_kern_base[NULL_FONT] = 0;
kern_base[NULL_FONT] = 0;
exten_base[NULL_FONT] = 0;
font_glue[NULL_FONT] = null;
font_params[NULL_FONT] = 7;
param_base[NULL_FONT] = -1;
for(k = 0; k <= 6; k++) {
    font_info[k].sc = 0;
}
```
