# Section 607

Here is a subroutine that produces a `DVI` command for some specified downward or rightward motion.
It has two parameters: *w* is the amount
of motion, and *o* is either *DOWN1* or *RIGHT1*.
We use the fact that the command codes have convenient arithmetic properties: *Y1 − DOWN1 = W1 − RIGHT1* and *Z1 − DOWN1 = X1 − RIGHT1*.

```c dvi.c
void movement(scaled w, eight_bits o) {
    small_number mstate; // have we seen a |y| or |z|?
    pointer p, q; // current and top nodes on the stack
    int k; // index into |dvi_buf|, modulo |DVI_BUF_SIZE|

    q = get_node(MOVEMENT_NODE_SIZE); // new node for the top of the stack
    width(q) = w;
    location(q) = dvi_offset + dvi_ptr;
    if (o == DOWN1) {
        link(q) = down_ptr;
        down_ptr = q;
    }
    else {
        link(q) = right_ptr;
        right_ptr = q;
    }
    
    // << Look at the other stack entries until deciding what sort of DVI command to generate; |goto found| if node |p| is a "hit" >>
    
    // << Generate a |DOWN| or |RIGHT| command for |w| and |return| >>

found:
    // << Generate a |Y0| or |Z0| command in order to reuse a previous appearance of |w| >>
}
```
