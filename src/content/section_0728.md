# Section 728

One of the things we must do on the first pass is change a *BIN_NOAD* to an *ORD_NOAD* if the *BIN_NOAD* is not in the context of a binary operator.
The values of *r* and *r_type* make this fairly easy.

```c << Do first-pass processing based on |type(q)|; |goto done_with_noad| if a noad has been fully processed, |goto check_dimensions| if it has been translated into |new_hlist(q)|, or |goto done_with_node| if a node has been fully processed >>=
reswitch:
delta = 0;
switch (type(q)) {
case BIN_NOAD:
    switch (r_type) {
    case BIN_NOAD:
    case OP_NOAD:
    case REL_NOAD:
    case OPEN_NOAD:
    case PUNCT_NOAD:
    case LEFT_NOAD:
        type(q) = ORD_NOAD;
        goto reswitch;

    default:
        do_nothing;
    }
    break;

case REL_NOAD:
case CLOSE_NOAD:
case PUNCT_NOAD:
case RIGHT_NOAD:
    // << Convert a final |BIN_NOAD| to an |ORD_NOAD| >>
    if (type(q) == RIGHT_NOAD) {
        goto done_with_noad;
    }
    break;

// << Cases for noads that can follow a |BIN_NOAD| >>

// << Cases for nodes that can appear in an mlist, after which we |goto done_with_node| >>

default:
    confusion("mlist1");
}

// << Convert |nucleus(q)| to an hlist and attach the sub/superscripts >>
```
