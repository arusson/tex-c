# Section 984

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case SET_PAGE_DIMEN:
    switch (chr_code) {
    case 0:
        print_esc("pagegoal");
        break;
    
    case 1:
        print_esc("pagetotal");
        break;

    case 2:
        print_esc("pagestretch");
        break;
    
    case 3:
        print_esc("pagefilstretch");
        break;

    case 4:
        print_esc("pagefillstretch");
        break;

    case 5:
        print_esc("pagefilllstretch");
        break;

    case 6:
        print_esc("pageshrink");
        break;
    
    default:
        print_esc("pagedepth");
    }

    break;
```
