# Section 1167

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + VCENTER:
    scan_spec(VCENTER_GROUP, false);
    normal_paragraph();
    push_nest();
    mode = -VMODE;
    prev_depth = IGNORE_DEPTH;
    if (every_vbox != null) {
        begin_token_list(every_vbox, EVERY_VBOX_TEXT);
    }
    break;
```
