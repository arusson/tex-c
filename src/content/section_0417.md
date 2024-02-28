# Section 417

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case SET_AUX:
    if (chr_code == VMODE) {
        print_esc("prevdepth");
    }
    else {
        print_esc("spacefactor");
    }
    break;

case SET_PAGE_INT:
    if (chr_code == 0) {
        print_esc("deadcycles");
    }
    else {
        print_esc("insertpenalties");
    }
    break;

case SET_BOX_DIMEN:
    if (chr_code == WIDTH_OFFSET) {
        print_esc("wd");
    }
    else if (chr_code == HEIGHT_OFFSET) {
        print_esc("ht");
    }
    else {
        print_esc("dp");
    }
    break;

case LAST_ITEM:
    switch (chr_code) {
    case INT_VAL:
        print_esc("lastpenalty");
        break;
    
    case DIMEN_VAL:
        print_esc("lastkern");
        break;
    
    case GLUE_VAL:
        print_esc("lastskip");
        break;
    
    case INPUT_LINE_NO_CODE:
        print_esc("inputlineno");
        break;
    
    default:
        print_esc("badness");
    }
    break;
```
