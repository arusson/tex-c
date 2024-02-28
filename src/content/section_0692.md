# Section 692

The next subroutine will descend to another level of recursion when a subsidiary mlist needs to be displayed.
The parameter *c* indicates what character is to become part of the recursion history.
An empty mlist is distinguished from a field with *math_type(p) = EMPTY*, because these are not equivalent (as explained above).

```c io/display_math.c
// display a noad field
void print_subsidiary_data(pointer p, ASCII_code c) {
    if (cur_length >= depth_threshold) {
        if (math_type(p) != EMPTY) {
            print(" []");
        }
    }
    else {
        append_char(c); // include |c| in the recursion history
        temp_ptr = p; // prepare for |show_info| if recursion is needed
        switch (math_type(p)) {
        case MATH_CHAR:
            print_ln();
            print_current_string();
            print_fam_and_char(p); 
            break;
        
        case SUB_BOX: show_info();
            break; // recursive call
        
        case SUB_MLIST:
            if (info(p) == null) {
                print_ln();
                print_current_string();
                print("{}");
            }
            else {
                show_info();
            }
            break; // recursive call
        
        default:
            do_nothing; //|EMPTY|
        }
        flush_char; // remove |c| from the recursion history
    }
}
```
