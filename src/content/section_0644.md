# Section 644: Packaging

We're essentially done with the parts of $\TeX$ that are concerned with the input (*get_next*) and the output (*ship_out*).
So it's time to get heavily into the remaining part, which does the real work of typesetting.

After lists are constructed, $\TeX$ wraps them up and puts them into boxes.
Two major subroutines are given the responsibility for this task: *hpack* applies to horizontal lists (hlists) and *vpack* applies to vertical lists (vlists).
The main duty of *hpack* and *vpack* is to compute the dimensions of the resulting boxes, and to adjust the glue if one of those dimensions is pre-specified.
The computed sizes normally enclose all of the material inside the new box; but some items may stick out if negative glue is used, if the box is overfull, or if a `\vbox` includes other boxes that have
been shifted left.

The subroutine call *hpack(p, w, m)* returns a pointer to an *HLIST_NODE* for a box containing the hlist that starts at *p*.
Parameter *w* specifies a width; and parameter *m* is either *'EXACTLY'* or *'ADDITIONAL'*.
Thus, *hpack(p, w, EXACTLY)* produces a box whose width is exactly *w*, while *hpack(p, w, ADDITIONAL)* yields a box whose width is the natural width plus *w*.
It is convenient to define a macro called *'NATURAL'* to cover the most common case, so that we can say *hpack(p, NATURAL)* to get a box that has the natural width of list *p*.


Similarly, *vpack(p, w, m)* returns a pointer to a *VLIST_NODE* for a box containing the vlist that starts at *p*.
In this case *w* represents a height instead of a width; the parameter *m* is interpreted as in *hpack*.

> ![NOTE]
> *EXACTLY* AND *ADDITIONAL* are not in the file `constants.h`, and are kept alongside *NATURAL* in `builder.h`.

```c include/builder.h
// << Start file |builder.h| >>

#define EXACTLY    0             // a box dimension is pre-specified
#define ADDITIONAL 1             // a box dimension is increased from the natural one
#define NATURAL    0, ADDITIONAL // shorthand for parameters to |hpack| and |vpack|
```
