# Section 881

At the end of the following code, *q* will point to the final node on the list about to be justified.

```c << Modify the end of the line to reflect the nature of the break and to include \rightskip; also set the proper value of |disc_break| >>=
q = cur_break(cur_p);
disc_break = false;
post_disc_break = false;
if (q != null) {
    // |q| cannot be a |CHAR_NODE|
    if (type(q) == GLUE_NODE) {
        delete_glue_ref(glue_ptr(q));
        glue_ptr(q) = right_skip;
        subtype(q) = RIGHT_SKIP_CODE + 1;
        add_glue_ref(right_skip);
        goto done;
    }
    else {
        if (type(q) == DISC_NODE) {
            // << Change discretionary to compulsory and set |disc_break = true| >>
        }
        else if (type(q) == MATH_NODE || type(q) == KERN_NODE) {
            width(q) = 0;
        }
    }
}
else {
    q = TEMP_HEAD;
    while (link(q) != null) {
        q = link(q);
    }
}
// << Put the \rightskip glue after node |q| >>
done:
```
