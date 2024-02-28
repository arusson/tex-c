# Section 720

The recursion in *mlist_to_hlist* is due primarily to a subroutine called *clean_box* that puts a given noad field into a box using a given math style; *mlist_to_hlist* can call *clean_box*, which can call *mlist_to_hlist*.

The box returned by *clean_box* is "clean" in the sense that its *shift_amount* is zero.

```c math/math_typesetting.c
// << Start file |math_typesetting.c| >>

pointer clean_box(pointer p, small_number s) {
    pointer q;               // beginning of a list to be boxed
    small_number save_style; // |cur_style| to be restored
    pointer x;               // box to be returned
    pointer r;               // temporary pointer
    
    switch (math_type(p)) {
    case MATH_CHAR:
        cur_mlist = new_noad();
        mem[nucleus(cur_mlist)] = mem[p];
        break;
    
    case SUB_BOX:
        q = info(p);
        goto found;
    
    case SUB_MLIST:
        cur_mlist = info(p);
        break;
    
    default:
        q = new_null_box();
        goto found;
    }
    save_style = cur_style;
    cur_style = s;
    mlist_penalties = false;
    mlist_to_hlist();
    q = link(TEMP_HEAD); // recursive call
    cur_style = save_style; // restore the style
    // << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>

found:
    if (is_char_node(q) || q == null) {
        x = hpack(q, NATURAL);
    }
    else if (link(q) == null
        && type(q) <= VLIST_NODE
        && shift_amount(q) == 0)
    {
        x = q; // it's already clean
    }
    else {
        x = hpack(q, NATURAL);
    }
    // << Simplify a trivial box >>
    return x;
}
```
