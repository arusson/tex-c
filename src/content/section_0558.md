# Section 558

Font parameters are referred to as *slant(f)*, *space(f)*, etc.

```c include/font_metric.h
#define param(X,Y)       (font_info[(X) + param_base[(Y)]].sc)
#define slant(X)         param(SLANT_CODE,(X))         // slant to the right, per unit distance upward
#define space(X)         param(SPACE_CODE,(X))         // normal space between words
#define space_stretch(X) param(SPACE_STRETCH_CODE,(X)) // stretch between words
#define space_shrink(X)  param(SPACE_SHRINK_CODE,(X))  // shrink between words
#define x_height(X)      param(X_HEIGHT_CODE,(X))      // one ex
#define quad(X)          param(QUAD_CODE,(X))          // one em
#define extra_space(X)   param(EXTRA_SPACE_CODE,(X))   // additional space at end of sentence
```

> ![NOTE]
> The destination variable has been added, so the code corresponds to a full line of the final code.

```c << The em width for |cur_font| >>=
v = quad(cur_font);
```
