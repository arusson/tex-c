# Section 554

Of course we want to define macros that suppress the detail of how font information is actually packed, so that we don't have to write things like

<div align="center">

*font_info[width_base[f] + font_info[char_base[f] + c].qqqq.b0].sc*
</div>

too often.
The `WEB` definitions here make *char_info(f)(c)* the *four_quarters* word of font information corresponding to character *c* of font *f*.
If *q* is such a word, *char_width(f)(q)* will be the character's width; hence the long formula above is at least abbreviated to

<div align="center">

*char_width(f)(char_info(f)(c))*.
</div>

Usually, of course, we will fetch *q* first and look at several of its fields at the same time.

The italic correction of a character will be denoted by *char_italic(f)(q)*, so it is analogous to *char_width*.
But we will get at the height and depth in a slightly different way, since we usually want to compute both height and depth if we want either one.
The value of *height_depth(q)* will be the 8-bit quantity

<div align="center">

*b = height_index* $\times$ *16 + depth_index*,
</div>

and if *b* is such a byte we will write *char_height(f)(b)* and *char_depth(f)(b)* for the height and depth of the character *c* for which *q = char_info(f)(c)*.
Got that?

The tag field will be called *char_tag(q)*; the remainder byte will be called *rem_byte(q)*, using a macro that we have already defined above.

Access to a character's *width*, *height*, *depth*, and *tag* fields is part of $\TeX$'s inner loop, so we want these macros to produce code that is as fast as possible under the circumstances.

> ![NOTE]
> *char_height*, etc., are defined with a macro that takes several arguments, so *char_height(f)(b)* will be used as *char_height(f, b)*.

```c include/font_metric.h
#define char_info(X,Y)   font_info[char_base[(X)] + (Y)]
#define char_width(X,Y)  font_info[width_base[(X)] + qqqq_b0((Y))].sc
#define char_exists(X)   (qqqq_b0((X)) > MIN_QUARTERWORD)
#define char_italic(X,Y) font_info[italic_base[(X)] + qqqq_b2((Y))/4].sc
#define height_depth(X)  qqqq_b1((X))
#define char_height(X,Y) font_info[height_base[(X)] + (Y) / 16].sc
#define char_depth(X,Y)  font_info[depth_base[(X)] + (Y) % 16].sc
#define char_tag(X)      (qqqq_b2((X)) % 4)
```
