# Section 177

Then there is a subroutine that prints glue stretch and shrink, possibly followed by the name of finite units:

```c io/display_boxes.c
// prints a glue component
void print_glue(scaled d, int order, char *s) {
    print_scaled(d);
    if (order < NORMAL || order > FILLL) {
        print("foul");
    }
    else if (order > NORMAL) {
        print("fil");
        while (order > FIL) {
            print_char('l');
            decr(order);
        }
    }
    else if (strlen(s) != 0) {
        print(s);
    }
}
```
