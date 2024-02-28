# Section 711

When we build an extensible character, it's handy to have the following subroutine, which puts a given character on top of the characters already in box *b*:

```c << Declare subprocedures for |var_delimiter| >>+=
void stack_into_box(pointer b, internal_font_number f, quarterword c) {
    pointer p; // new node placed into |b|
    p = char_box(f, c);
    link(p) = list_ptr(b);
    list_ptr(b) = p;
    height(b) = height(p);
}
```
