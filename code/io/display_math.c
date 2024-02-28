// ~~~ Section 691 ~~~
// ~~~ Start file |display_math.c|, 1382 ~~~
#include "io.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

// prints family and character
void print_fam_and_char(pointer p) {
    print_esc("fam");
    print_int(fam(p));
    print_char(' ');
    print_strnumber(character(p));
}

// prints a delimiter as 24-bit hex value
void print_delimiter(pointer p) {
    int a; // accumulator
    a = small_fam(p)*256 + small_char(p);
    a = a*0x1000 + large_fam(p)*256 + large_char(p);
    if (a < 0) {
        print_int(a); // this should never happen
    }
    else {
        print_hex(a);
    }
}
// ~~~ End section 691 ~~~

// ~~~ Section 692 ~~~
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
// ~~~ End section 692 ~~~

// ~~~ Section 693 ~~~
// the reader will kindly forgive this
void show_info() {
    show_node_list(info(temp_ptr));
}
// ~~~ End section 693 ~~~

// ~~~ Section 694 ~~~
void print_style(int c) {
    switch (c / 2) {
    case 0:
        print_esc("displaystyle");
        break; // |DISPLAY_STYLE = 0|
    
    case 1:
        print_esc("textstyle");
        break; // |TEXT_STYLE = 2|
    
    case 2:
        print_esc("scriptstyle");
        break; // |SCRIPT_STYLE = 4|
    
    case 3:
        print_esc("scriptscriptstyle");
        break; // |SCRIPT_SCRIPT_STYLE = 6|
    
    default:
        print("Unknown style!");
    }
}
// ~~~ End section 694 ~~~

// ~~~ Section 699 ~~~
void print_size(int s) {
    if (s == TEXT_SIZE) {
        print_esc("textfont");
    }
    else if (s == SCRIPT_SIZE) {
        print_esc("scriptfont");
    }
    else {
        print_esc("scriptscriptfont");
    }
}
// ~~~ End section 699 ~~~
