# Section 157

A *PENALTY_NODE* specifies the penalty associated with line or page breaking, in its *penalty* field.
This field is a fullword integer, but the full range of integer values is not used:
Any penalty $\geq$ *10000* is treated as infinity, and no break will be allowed for such high values.
Similarly, any penalty $\leq$ *−10000* is treated as negative infinity, and a break will be forced.

```c include/constants.h
#define PENALTY_NODE  12             // |type| of a penalty node
#define INF_PENALTY   INF_BAD        // "infinite" penalty value
#define EJECT_PENALTY (-INF_PENALTY) // "negatively infinite" penalty value
```

```c include/datastructures.h
#define penalty(X) mem[(X) + 1].integer // the added cost of breaking a list here
```
