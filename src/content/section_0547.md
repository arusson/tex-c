# Section 547

The final portion of a `TFM` file is the *param* array, which is another sequence of *fix_word* values.

- *param[1] = slant* is the amount of italic slant, which is used to help position accents.
  For example, *slant = .25* means that when you go up one unit, you also go .25 units to the right.
  The *slant* is a pure number; it's the only *fix_word* other than the design size itself that is not scaled by the design size.

- *param[2] = space* is the normal spacing between words in text.
  Note that character '␣' in the font need not have anything to do with
  blank spaces.

- *param[3] = space_stretch* is the amount of glue stretching between words.

- *param[4] = space_shrink* is the amount of glue shrinking between words.

- *param[5] = x_height* is the size of one ex in the font; it is also
  the height of letters for which accents don't have to be raised or lowered.

- *param[6] = quad* is the size of one em in the font.

- *param[7] = extra_space* is the amount added to *param[2]* at the
  ends of sentences.

If fewer than seven parameters are present, $\TeX$ sets the missing parameters to zero.
Fonts used for math symbols are required to have additional parameter information, which is explained later.

```c include/constants.h
#define SLANT_CODE         1
#define SPACE_CODE         2
#define SPACE_STRETCH_CODE 3
#define SPACE_SHRINK_CODE  4
#define X_HEIGHT_CODE      5
#define QUAD_CODE          6
#define EXTRA_SPACE_CODE   7
```
