# Section 996

```c << Update the values of |last_glue|, |last_penalty|, and |last_kern| >>=
if (last_glue != MAX_HALFWORD) {
    delete_glue_ref(last_glue);
}
last_penalty = 0;
last_kern = 0;
if (type(p) == GLUE_NODE) {
    last_glue = glue_ptr(p);
    add_glue_ref(last_glue);
}
else {
    last_glue = MAX_HALFWORD;
    if (type(p) == PENALTY_NODE) {
        last_penalty = penalty(p);
    }
    else if (type(p) == KERN_NODE) {
        last_kern = width(p);
    }
}
```
