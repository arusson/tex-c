# Section 1174

```c math/math_lists.c
// << Declare the function called |fin_mlist| >>

void build_choices() {
    pointer p; // the current mlist
    unsave();
    p = fin_mlist(null);
    switch (saved(-1)) {
    case 0:
        display_mlist(tail) = p;
        break;
    
    case 1:
        text_mlist(tail) = p;
        break;
    
    case 2:
        script_mlist(tail) = p;
        break;
    
    case 3:
        script_script_mlist(tail) = p;
        decr(save_ptr);
        return;
    } // there are no other cases
    incr(saved(-1));
    push_math(MATH_CHOICE_GROUP);
    scan_left_brace();
}
```
