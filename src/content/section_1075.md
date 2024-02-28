# Section 1075

The *box_end* procedure does the right thing with *cur_box*, if *box_context* represents the context as explained above.

```c builder/boxes_and_lists.c
void box_end(int box_context) {
    pointer p; // |ORD_NOAD| for new box in math mode
    if (box_context < BOX_FLAG) {
        // << Append box |cur_box| to the current list, shifted by |box_context| >>
    }
    else if (box_context < SHIP_OUT_FLAG) {
        // << Store |cur_box| in a box register >>
    }
    else if (cur_box != null) {
        if (box_context > SHIP_OUT_FLAG) {
            // << Append a new leader node that uses |cur_box| >>
        }
        else {
            ship_out(cur_box);
        }
    }
}
```
