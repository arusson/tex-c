# Section 1068

```c builder/boxes_and_lists.c
void handle_right_brace() {
    pointer p, q; // for short - term use
    scaled d;     // holds |split_max_depth| in |insert_group|
    int f;        // holds |floating_penalty| in |insert_group|
    switch (cur_group) {
    case SIMPLE_GROUP:
        unsave();
        break;
    
    case BOTTOM_LEVEL:
        print_err("Too many }'s");
        help2("You've closed more groups than you opened.")
            ("Such booboos are generally harmless, so keep going.");
        error();
        break;
    
    case SEMI_SIMPLE_GROUP:
    case MATH_SHIFT_GROUP:
    case MATH_LEFT_GROUP:
        extra_right_brace();
        break;
    
    // << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>

    default:
        confusion("rightbrace");
    }
}
```
