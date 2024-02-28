# Section 1108

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case REMOVE_ITEM:
    if (chr_code == GLUE_NODE) {
        print_esc("unskip");
    }
    else if (chr_code == KERN_NODE) {
        print_esc("unkern");
    }
    else {
        print_esc("unpenalty");
    }
    break;

case UN_HBOX:
    if (chr_code == COPY_CODE) {
        print_esc("unhcopy");
    }
    else {
        print_esc("unhbox");
    }
    break;

case UN_VBOX:
    if (chr_code == COPY_CODE) {
        print_esc("unvcopy");
    }
    else {
        print_esc("unvbox");
    }
    break;
```
