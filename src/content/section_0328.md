# Section 328

The *begin_file_reading* procedure starts a new level of input for lines of characters to be read from a file, or as an insertion from the terminal.
It does not take care of opening the file, nor does it set *loc* or *limit* or *line*.

```c datastructures/stack.c
void begin_file_reading() {
    if (in_open == MAX_IN_OPEN) {
        overflow("text input levels", MAX_IN_OPEN);
    }
    if (first == BUF_SIZE) {
        overflow("buffer size", BUF_SIZE);
    }
    incr(in_open);
    push_input;
    index = in_open;
    line_stack[index] = line;
    start = first;
    state = MID_LINE;
    name = 0; // |terminal_input| is now |true|
}
```
