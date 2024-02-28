# Section 689

Finally, the `\mathchoice` primitive creates a *CHOICE_NODE*, which has special subfields *display_mlist*, *text_mlist*, *script_mlist*, and *script_script_mlist* pointing to the mlists for each style.

```c include/constants.h
#define CHOICE_NODE (UNSET_NODE + 2) // |type| of a choice node
```

```c include/texmath.h
#define display_mlist(X)       info((X) + 1) // mlist to be used in display style
#define text_mlist(X)          link((X) + 1) // mlist to be used in text style
#define script_mlist(X)        info((X) + 2) // mlist to be used in script style
#define script_script_mlist(X) link((X) + 2) // mlist to be used in scriptscript style
```

```c math/math_structures.c
// create a choice node
pointer new_choice() {
    pointer p; // the new node
    p = get_node(STYLE_NODE_SIZE);
    type(p) = CHOICE_NODE;
    subtype(p) = 0; // the |subtype| is not used
    display_mlist(p) = null;
    text_mlist(p) = null;
    script_mlist(p) = null;
    script_script_mlist(p) = null;
    return p;
}
```
