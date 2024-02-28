# Section 1073

Constructions that require a box are started by calling *scan_box* with a specified context code.
The *scan_box* routine verifies that a *MAKE_BOX* command comes next and then it calls *begin_box*.

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + HMOVE:
case HMODE + VMOVE:
case MMODE + VMOVE:
    t = cur_chr;
    scan_normal_dimen;
    if (t == 0) {
        scan_box(cur_val);
    }
    else {
        scan_box(-cur_val);
    }
    break;

any_mode(LEADER_SHIP):
    scan_box(LEADER_FLAG - A_LEADERS + cur_chr);
    break;

any_mode(MAKE_BOX):
    begin_box(0);
    break;
```
