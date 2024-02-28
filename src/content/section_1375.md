# Section 1375

The presence of '`\immediate`' causes the *do_extension* procedure to descend to one level of recursion.
Nothing happens unless `\immediate` is followed by '`\openout`', '`\write`', or '`\closeout`'.

```c << Implement \immediate >>=
get_x_token();
if (cur_cmd == EXTENSION && cur_chr <= CLOSE_NODE) {
    p = tail;
    do_extension(); // append a whatsit node
    out_what(tail); // do the action immediately
    flush_node_list(tail);
    tail = p;
    link(p) = null;
}
else {
    back_input();
}
```
