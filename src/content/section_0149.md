# Section 149

 A *GLUE_NODE* represents glue in a list.
 However, it is really only a pointer to a separate glue specification, since $\TeX$ makes use of the fact that many essentially identical nodes of glue are usually present.
If *p* points to a *GLUE_NODE*, *glue_ptr(p)* points to another packet of words that specify the stretch and shrink components, etc.

Glue nodes also serve to represent leaders; the *subtype* is used to distinguish between ordinary glue (which is called *NORMAL*) and the three kinds of leaders (which are called *A_LEADERS*, *C_LEADERS*, and *X_LEADERS*).
The *leader_ptr* field points to a rule node or to a box node containing the leaders; it is set to *null* in ordinary glue nodes.

Many kinds of glue are computed from $\TeX$'s "skip" parameters, and it is helpful to know which parameter has led to a particular glue node.
Therefore the *subtype* is set to indicate the source of glue, whenever it originated as a parameter.
We will be defining symbolic names for the parameter numbers later (e.g., *LINE_SKIP_CODE = 0*, *BASELINE_SKIP_CODE = 1*, etc.); it suffices for now to say that the *subtype* of parametric glue will be the same as the parameter number, plus one.

In math formulas there are two more possibilities for the *subtype* in a glue node: *MU_GLUE* denotes an `\mskip` (where the units are scaled `mu` instead of scaled `pt`);
and *COND_MATH_GLUE* denotes the '`\nonscript`' feature that cancels the glue node immediately following if it appears in a subscript.

```c include/constants.h
#define GLUE_NODE      10  // |type| of node that points to a glue specification
#define COND_MATH_GLUE 98  // special |subtype| to suppress glue in the next node
#define MU_GLUE        99  // |subtype| for math glue
#define A_LEADERS      100 // |subtype| for aligned leaders
#define C_LEADERS      101 // |subtype| for centered leaders
#define X_LEADERS      102 // |subtype| for expanded leaders
```

```c include/datastructures.h
#define glue_ptr   llink // pointer to a glue specification
#define leader_ptr rlink // pointer to box or rule node for leaders
```
