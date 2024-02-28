# Section 1163

```c math/math_lists.c
void math_radical() {
    tail_append(get_node(RADICAL_NOAD_SIZE));
    type(tail) = RADICAL_NOAD;
    subtype(tail) = NORMAL;
    mem[nucleus(tail)] = empty_field;
    mem[subscr(tail)] = empty_field;
    mem[supscr(tail)] = empty_field;
    scan_delimiter(left_delimiter(tail), true);
    scan_math(nucleus(tail));
}
```
