# Section 1103

```c builder/boxes_and_lists.c
void append_penalty() {
    scan_int();
    tail_append(new_penalty(cur_val));
    if (mode == VMODE) {
        build_page();
    }
}
```
