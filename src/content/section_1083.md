# Section 1083

Here is where we enter restricted horizontal mode or internal vertical mode, in order to make a box.

```c << Initiate the construction of an hbox or vbox, then |return| >>=
k = cur_chr - VTOP_CODE;
saved(0) = box_context;
if (k == HMODE) {
    if (box_context < BOX_FLAG && abs(mode) == VMODE) {
        scan_spec(ADJUSTED_HBOX_GROUP, true);
    }
    else {
        scan_spec(HBOX_GROUP, true);
    }
}
else {
    if (k == VMODE) {
        scan_spec(VBOX_GROUP, true);
    }
    else {
        scan_spec(VTOP_GROUP, true);
        k = VMODE;
    }
    normal_paragraph();
}
push_nest();
mode = -k;
if (k == VMODE) {
    prev_depth = IGNORE_DEPTH;
    if (every_vbox != null) {
        begin_token_list(every_vbox, EVERY_VBOX_TEXT);
    }
}
else {
    space_factor = 1000;
    if (every_hbox != null) {
        begin_token_list(every_hbox, EVERY_HBOX_TEXT);
    }
}
return;
```
