# Section 1100

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case INSERT_GROUP:
    end_graf();
    q = split_top_skip;
    add_glue_ref(q);
    d = split_max_depth;
    f = floating_penalty;
    unsave();
    decr(save_ptr);
    // now |saved(0)| is the insertion number, or 255 for |vadjust|
    p = vpack(link(head), NATURAL);
    pop_nest();
    if (saved(0) < 255) {
        tail_append(get_node(INS_NODE_SIZE));
        type(tail) = INS_NODE;
        subtype(tail) = saved(0);
        height(tail) = height(p) + depth(p);
        ins_ptr(tail) = list_ptr(p);
        split_top_ptr(tail) = q;
        depth(tail) = d;
        float_cost(tail) = f;
    }
    else {
        tail_append(get_node(SMALL_NODE_SIZE));
        type(tail) = ADJUST_NODE;
        subtype(tail) = 0; // the |subtype| is not used
        adjust_ptr(tail) = list_ptr(p);
        delete_glue_ref(q);
    }
    free_node(p, BOX_NODE_SIZE);
    if (nest_ptr == 0) {
        build_page();
    }
    break;

case OUTPUT_GROUP:
    // << Resume the page builder after an output routine has come to an end >>
    break;
```
