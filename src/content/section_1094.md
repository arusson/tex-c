# Section 1094

A paragraph ends when a *PAR_END* command is sensed, or when we are in horizontal mode when reaching the right brace of vertical-mode routines like `\vbox`, `\insert`, or `\output`.

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + PAR_END:
    normal_paragraph();
    if (mode > 0) {
        build_page();
    }
    break;

case HMODE + PAR_END:
    if (align_state < 0) {
        off_save(); // this tries to recover from an alignment that didn't end properly
    }
    end_graf(); // this takes us to the enclosing mode, if |mode > 0|
    if (mode == VMODE) {
        build_page();
    }
    break;

case HMODE + STOP:
case HMODE + VSKIP:
case HMODE + HRULE:
case HMODE + UN_VBOX:
case HMODE + HALIGN:
    head_for_vmode();
    break;
```
