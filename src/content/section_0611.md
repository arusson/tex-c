# Section 611

As we search through the stack, we are in one of three states, *Y_SEEN*, *Z_SEEN*, or *NONE_SEEN*, depending on whether we have encountered *Y_HERE* or *Z_HERE* nodes.
These states are encoded as multiples of 6, so that they can be added to the *info* fields for quick decision-making.

```c include/constants.h
#define NONE_SEEN 0  // no |Y_HERE| or |Z_HERE| nodes have been encountered yet
#define Y_SEEN    6  // we have seen |Y_HERE| but not |Z_HERE|
#define Z_SEEN    12 // we have seen |Z_HERE| but not |Y_HERE|
```

```c << Look at the other stack entries until deciding what sort of DVI command to generate; |goto found| if node |p| is a "hit" >>=
p = link(q);
mstate = NONE_SEEN;
while (p != null) {
    if (width(p) == w) {
        // << Consider a node with matching width; |goto found| if it's a hit >>
    }
    else {
        switch (mstate + info(p)) {
        case NONE_SEEN + Y_HERE:
            mstate = Y_SEEN;
            break;
        
        case NONE_SEEN + Z_HERE:
            mstate = Z_SEEN;
            break;
        
        case Y_SEEN + Z_HERE:
        case Z_SEEN + Y_HERE:
            goto not_found;
        
        default:
            do_nothing;
        }
    }
    p = link(p);
}
not_found:
```
