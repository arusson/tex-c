# Section 690

Let's consider now the previously unwritten part of *show_node_list* that displays the things that can only be present in mlists; this program illustrates how to access the data structures just defined.

In the context of the following program, *p* points to a node or noad that should be displayed, and the current string contains the "recursion history" that leads to this point.
The recursion history consists of a dot for each outer level in which *p* is subsidiary to some node, or in which *p* is subsidiary to the *nucleus* field of some noad; the dot is replaced by '`_`' or '`^`' or '`/`' or '`\`' if *p* is descended from the *subscr* or *supscr* or *denominator* or *numerator* fields of noads.
For example, the current string would be '`.^._/`' if *p* points to the *ORD_NOAD* for *x* in the (ridiculous) formula '`$\sqrt{a^{\mathinner{b_{c\over x+y}}}}$`'.

```c << Cases of |show_node_list| that arise in mlists only >>=
case STYLE_NODE:
    print_style(subtype(p));
    break;

case CHOICE_NODE:
    // << Display choice node |p| >>
    break;

case ORD_NOAD:
case OP_NOAD:
case BIN_NOAD:
case REL_NOAD:
case OPEN_NOAD:
case CLOSE_NOAD:
case PUNCT_NOAD:
case INNER_NOAD:
case RADICAL_NOAD:
case OVER_NOAD:
case UNDER_NOAD:
case VCENTER_NOAD:
case ACCENT_NOAD:
case LEFT_NOAD:
case RIGHT_NOAD:
    // << Display normal noad |p| >>
    break;

case FRACTION_NOAD:
    // << Display fraction noad |p| >>
    break;
```
