# Section 694

```c io/display_math.c
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
```
