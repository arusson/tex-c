# Section 691

Here are some simple routines used in the display of noads.

```c io/display_math.c
// << Start file |display_math.c| >>

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
```
