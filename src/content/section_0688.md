# Section 688

Math formulas can also contain instructions like `\textstyle` that override $\TeX$'s normal style rules.
A *STYLE_NODE* is inserted into the data structure to record such instructions;
it is three words long, so it is considered a node instead of a noad.
The *subtype* is either *DISPLAY_STYLE* or *TEXT_STYLE* or *SCRIPT_STYLE* or *SCRIPT_SCRIPT_STYLE*.
The second and third words of a *STYLE_NODE* are not used, but they are present because a *CHOICE_NODE* is converted to a *STYLE_NODE*.

$\TeX$ uses even numbers 0, 2, 4, 6 to encode the basic styles *DISPLAY_STYLE*, $\dots$, *SCRIPT_SCRIPT_STYLE*, and adds&nbsp;1 to get the "cramped" versions of these styles.
This gives a numerical order that is backwards from the convention of Appendix&nbsp;G in *The TeXbook*;
i.e., a smaller style has a larger numerical value.

```c include/constants.h
#define STYLE_NODE          (UNSET_NODE + 1) // |type| of a style node
#define STYLE_NODE_SIZE     3                // number of words in a style node
#define DISPLAY_STYLE       0                // |subtype| for \displaystyle
#define TEXT_STYLE          2                // |subtype| for \textstyle
#define SCRIPT_STYLE        4                // |subtype| for \scriptstyle
#define SCRIPT_SCRIPT_STYLE 6                // |subtype| for \scriptscriptstyle
#define CRAMPED             1                // add this to an uncramped style if you want to cramp it
```

```c math/math_structures.c
// create a style node
pointer new_style(small_number s) {
    pointer p; // the new node
    p = get_node(STYLE_NODE_SIZE);
    type(p) = STYLE_NODE;
    subtype(p) = s;
    width(p) = 0;
    depth(p) = 0; // the |width| and |depth| are not used
    return p;
}
```
