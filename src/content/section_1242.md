# Section 1242

The *space_factor* or *prev_depth* settings are changed when a *SET_AUX* command is sensed.
Similarly, *prev_graf* is changed in the presence of *SET_PREV_GRAF*, and *dead_cycles* or *insert_penalties* in the presence of *SET_PAGE_INT*.
These definitions are always global.

When some dimension of a box register is changed, the change isn't exactly global; but $\TeX$ does not look at the `\global` switch.

```c << Assignments >>+=
case SET_AUX:
    alter_aux();
    break;

case SET_PREV_GRAF:
    alter_prev_graf();
    break;

case SET_PAGE_DIMEN:
    alter_page_so_far();
    break;

case SET_PAGE_INT:
    alter_integer();
    break;

case SET_BOX_DIMEN:
    alter_box_dimen();
    break;
```
