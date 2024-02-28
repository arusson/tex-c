# Section 374

```c << Look up the characters of list |r| in the hash table, and set |cur_cs| >>=
j = first;
p = link(r);
while (p != null) {
    if (j >= max_buf_stack) {
        max_buf_stack = j + 1;
        if (max_buf_stack == BUF_SIZE) {
            overflow("buffer size", BUF_SIZE);
        }
    }
    buffer[j] = info(p) % 256;
    incr(j);
    p = link(p);
}
if (j > first + 1) {
    no_new_control_sequence = false;
    cur_cs = id_lookup(first, j - first);
    no_new_control_sequence = true;
}
else if (j == first) {
    cur_cs = NULL_CS; // the list is empty
}
else {
    cur_cs = SINGLE_BASE + buffer[first]; // the list has length one
}
```
