# Section 497

Here's a procedure that changes the *if_limit* code corresponding to a given value of *cond_ptr*.

```c parser/conditional.c
void change_if_limit(small_number l, pointer p) {
    pointer q;
    if (p == cond_ptr) {
        if_limit = l; // that's the easy case
    }
    else {
        q = cond_ptr;
        while(true) {
            if (q == null) {
                confusion("if");
            }
            if (link(q) == p) {
                type(q) = l;
                return;
            }
            q = link(q);
        }
    }
}
```
