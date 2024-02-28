# Section 754

When we get to the following part of the program, we have "fallen through" from cases that did not lead to *check_dimensions* or *done_with_noad* or *done_with_node*.
Thus, *q*&nbsp;points to a noad whose nucleus may need to be converted to an hlist, and whose subscripts and superscripts need to be appended if they are present.

If *nucleus(q)* is not a *MATH_CHAR*, the variable *delta* is the amount by which a superscript  be moved right with respect to a subscript when both are present.

```c << Convert |nucleus(q)| to an hlist and attach the sub/superscripts >>=
switch (math_type(nucleus(q))) {
case MATH_CHAR:
case MATH_TEXT_CHAR:
    // << Create a character node |p| for |nucleus(q)|, possibly followed by a kern node for the italic correction, and set |delta| to the italic correction if a subscript is present >>
    break;

case EMPTY:
    p = null;
    break;

case SUB_BOX:
    p = info(nucleus(q));
    break;

case SUB_MLIST:
    cur_mlist = info(nucleus(q));
    save_style = cur_style;
    mlist_penalties = false;
    mlist_to_hlist(); // recursive call
    cur_style = save_style;
    // << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>
    p = hpack(link(TEMP_HEAD), NATURAL);
    break;

default:
    confusion("mlist2");
}
new_hlist(q) = p;
if (math_type(subscr(q)) == EMPTY && math_type(supscr(q)) == EMPTY) {
    goto check_dimensions;
}
make_scripts(q, delta);
```
