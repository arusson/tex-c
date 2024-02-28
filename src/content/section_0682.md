# Section 682

Each portion of a formula is classified as Ord, Op, Bin, Rel, Open, Close, Punct, or Inner, for purposes of spacing and line breaking.
An *ORD_NOAD*, *OP_NOAD*, *BIN_NOAD*, *REL_NOAD*, *OPEN_NOAD*, *CLOSE_NOAD*, *PUNCT_NOAD*, or *INNER_NOAD* is used to represent portions of the various types.
For example, an '`=`' sign in a formula leads to the creation of a *REL_NOAD* whose *nucleus* field is a representation of an equals sign (usually *fam = 0*, *character = 61*).
A formula preceded by `\mathrel` also results in a *REL_NOAD*.
When a *REL_NOAD* is followed by an *OP_NOAD*, say, and possibly separated by one or more ordinary nodes (not noads), $\TeX$ will insert a penalty node (with the current *rel_penalty*) just after the formula that corresponds to the *REL_NOAD*, unless there already was a penalty immediately following; and a "thick space" will be inserted just before the formula that corresponds to the *OP_NOAD*.

A noad of type *ORD_NOAD*, *OP_NOAD*, $\ldots$, *INNER_NOAD* usually has a *subtype = NORMAL*.
The only exception is that an *OP_NOAD* might have *subtype = LIMITS* or *NO_LIMITS*, if the normal positioning of limits has been overridden for this operator.

```c include/constants.h
#define ORD_NOAD   (UNSET_NODE + 3) // |type| of a noad classified Ord
#define OP_NOAD    (ORD_NOAD + 1)   // |type| of a noad classified Op
#define BIN_NOAD   (ORD_NOAD + 2)   // |type| of a noad classified Bin
#define REL_NOAD   (ORD_NOAD + 3)   // |type| of a noad classified Rel
#define OPEN_NOAD  (ORD_NOAD + 4)   // |type| of a noad classified Open
#define CLOSE_NOAD (ORD_NOAD + 5)   // |type| of a noad classified Close
#define PUNCT_NOAD (ORD_NOAD + 6)   // |type| of a noad classified Punct
#define INNER_NOAD (ORD_NOAD + 7)   // |type| of a noad classified Inner
#define LIMITS     1                // |subtype| of |OP_NOAD| whose scripts are to be above, below
#define NO_LIMITS  2                // |subtype| of |OP_NOAD| whose scripts are to be normal
```
