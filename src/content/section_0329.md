# Section 329

Conversely, the variables must be downdated when such a level of input is finished:

```c datastructures/stack.c
void end_file_reading() {
    first = start;
    line = line_stack[index];
    if (name > 17) {
        a_close(cur_file); // forget it
    }
    pop_input;
    decr(in_open);
}
```
