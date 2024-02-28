# Section 1172

The routine that scans the four mlists of a `\mathchoice` is very much like the routine that builds discretionary nodes.

```c math/math_lists.c
void append_choices() {
    tail_append(new_choice());
    incr(save_ptr);
    saved(-1) = 0;
    push_math(MATH_CHOICE_GROUP);
    scan_left_brace();
}
```
