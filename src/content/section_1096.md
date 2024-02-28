# Section 1096

```c builder/boxes_and_lists.c
void end_graf() {
    if (mode == HMODE) {
        if (head == tail) {
            pop_nest(); // null paragraphs are ignored
        }
        else {
            line_break(widow_penalty);
        }
        normal_paragraph();
        error_count = 0;
    }
}
```
