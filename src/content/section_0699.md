# Section 699: Subroutines for math mode

In order to convert mlists to hlists, i.e., noads to nodes, we need several subroutines that are conveniently dealt with now.

Let us first introduce the macros that make it easy to get at the parameters and other font information.
A size code, which is a multiple of 16, is added to a family number to get an index into the table of internal font numbers for each combination of family and size.
(Be alert: Size codes get larger as the type gets smaller.)

```c include/constants.h
#define TEXT_SIZE          0  // size code for the largest size in a family
#define SCRIPT_SIZE        16 // size code for the medium size in a family
#define SCRIPT_SCRIPT_SIZE 32 // size code for the smallest size in a family
```

```c io/display_math.c
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
```
