# Section 686

The *new_noad* function creates an *ORD_NOAD* that is completely null.

```c math/math_structures.c
// << Start file |math_structures.c| >>

pointer new_noad() {
    pointer p;
    p = get_node(NOAD_SIZE);
    type(p) = ORD_NOAD;
    subtype(p) = NORMAL;
    mem[nucleus(p)] = empty_field;
    mem[subscr(p)] = empty_field;
    mem[supscr(p)] = empty_field;
    return p;
}
```
