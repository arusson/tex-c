# Section 550

Besides the arrays just enumerated, we have directory arrays that make it
easy to get at the individual entries in *font_info*.
For example, the *char_info* data for character *c* in font *f* will be in *font_info[CHAR_BASE[f] + c].qqqq*; and if *w* is the *width_index* part of this word (the *b0* field), the width of the character is *font_info[width_base[f] + w].sc*.
(These formulas assume that *MIN_QUARTERWORD* has already been added to *c* and to *w*, since $\TeX$ stores its quarterwords that way.)

```c << Global variables >>+=
int char_base[FONT_MAX+ 1];      // base addresses for |char_info|
int width_base[FONT_MAX + 1];    // base addresses for widths
int height_base[FONT_MAX + 1];   // base addresses for heights
int depth_base[FONT_MAX + 1];    // base addresses for depths
int italic_base[FONT_MAX + 1];   // base addresses for italic corrections
int lig_kern_base[FONT_MAX + 1]; // base addresses for ligature/kerning programs
int kern_base[FONT_MAX + 1];     // base addresses for kerns
int exten_base[FONT_MAX + 1];    // base addresses for extensible recipes
int param_base[FONT_MAX + 1];    // base addresses for font parameters
```
