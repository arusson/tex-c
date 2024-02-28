# Section 681

Each noad is four or more words long.
The first word contains the *type* and *subtype* and *link* fields that are already so familiar to us;
the second, third, and fourth words are called the noad's *nucleus*, *subscr*, and *supscr* fields.

Consider, for example, the simple formula '`$x^2$`', which would be parsed into an mlist containing a single element called an *ORD_NOAD*.
The *nucleus* of this noad is a representation of '`x`', the *subscr* is empty, and the *supscr* is a representation of '`2`'.

The *nucleus*, *subscr*, and *supscr* fields are further broken into subfields.
If *p* points to a noad, and if *q* is one of its principal fields (e.g., *q = subscr(p)*), there are several possibilities for the subfields, depending on the *math_type* of *q*.

- *math_type(q) = MATH_CHAR* means that *fam(q)* refers to one of
  the sixteen font families, and *character(q)* is the number of a character
  within a font of that family, as in a character node.

- *math_type(q) = MATH_TEXT_CHAR* is similar, but the character is
  unsubscripted and unsuperscripted and it is followed immediately by another
  character from the same font. (This *math_type* setting appears only
  briefly during the processing; it is used to suppress unwanted italic
  corrections.)

- *math_type(q) = EMPTY* indicates a field with no value (the
  corresponding attribute of noad *p* is not present).

- *math_type(q) = SUB_BOX* means that *info(q)* points to a box
  node (either an *HLIST_NODE* or a *VLIST_NODE*) that should be used as the
  value of the field. The *shift_amount* in the subsidiary box node is the
  amount by which that box will be shifted downward.

- *math_type(q) = SUB_MLIST* means that *info(q)* points to
  an mlist; the mlist must be converted to an hlist in order to obtain
  the value of this field.

In the latter case, we might have *info(q) = null*.
This is not the same as *math_type(q) = EMPTY*; for example, '`$P_{}$`' and '`$P$`' produce different results (the former will not have the "italic correction" added to the width of *P*, but the "script skip" will be added).

The definitions of subfields given here are evidently wasteful of space, since a halfword is being used for the *math_type* although only three bits would be needed.
However, there are hardly ever many noads present at once, since they are soon converted to nodes that take up even more space, so we can afford to represent them in whatever way simplifies the programming.

```c include/constants.h
#define NOAD_SIZE      4 // number of words in a normal noad
#define MATH_CHAR      1 // |math_type| when the attribute is simple
#define SUB_BOX        2 // |math_type| when the attribute is a box
#define SUB_MLIST      3 // |math_type| when the attribute is a formula
#define MATH_TEXT_CHAR 4 // |math_type| when italic correction is dubious
```

```c include/texmath.h
// << Start file |texmath.h| >>

#define nucleus(X) ((X) + 1) // the |nucleus| field of a noad
#define supscr(X)  ((X) + 2) // the |supscr| field of a noad
#define subscr(X)  ((X) + 3) // the |subscr| field of a noad
#define math_type  link      // a |halfword| in |mem|
#define fam        font      // a |quarterword| in |mem|
```
