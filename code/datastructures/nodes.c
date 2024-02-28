// ~~~ Section 136 ~~~
// ~~~ Start file |nodes.c|, 1382 ~~~
#include "datastructures.h"
#include "arithmetic.h"
// ~~~ End section 1382 ~~~

// creates a new box node
pointer new_null_box() {
    pointer p = get_node(BOX_NODE_SIZE); // the new node
    type(p) = HLIST_NODE;
    subtype(p) = MIN_QUARTERWORD;
    width(p) = 0;
    depth(p) = 0;
    height(p) = 0;
    shift_amount(p) = 0;
    list_ptr(p) = null;
    glue_sign(p) = NORMAL;
    glue_order(p) = NORMAL;
    set_glue_ratio_zero(glue_set(p));
    return p;
}
// ~~~ End section 136 ~~~

// ~~~ Section 139 ~~~
pointer new_rule() {
    pointer p = get_node(RULE_NODE_SIZE); // the new node
    type(p) = RULE_NODE;
    subtype(p) = 0; // the |subtype| is not used
    width(p) = NULL_FLAG;
    depth(p) = NULL_FLAG;
    height(p) = NULL_FLAG;
    return p;
}
// ~~~ End section 139 ~~~

// ~~~ Section 144 ~~~
pointer new_ligature(quarterword f, quarterword c, pointer q) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = LIGATURE_NODE;
    font(lig_char(p)) = f;
    character(lig_char(p)) = c;
    lig_ptr(p) = q;
    subtype(p) = 0;
    return p;
}

pointer new_lig_item(quarterword c) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    character(p) = c;
    lig_ptr(p) = null;
    return p;
}
// ~~~ End section 144 ~~~

// ~~~ Section 145 ~~~
pointer new_disc() {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = DISC_NODE;
    replace_count(p) = 0;
    pre_break(p) = null;
    post_break(p) = null;
    return p;
}
// ~~~ End section 145 ~~~

// ~~~ Section 147 ~~~
pointer new_math(scaled w, small_number s) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = MATH_NODE;
    subtype(p) = s;
    width(p) = w;
    return p;
}
// ~~~ End section 147 ~~~

// ~~~ Section 151 ~~~
// duplicates a glue specification
pointer new_spec(pointer p) {
    pointer q = get_node(GLUE_SPEC_SIZE); // the new spec
    mem[q] = mem[p];
    glue_ref_count(q) = null;
    width(q) = width(p);
    stretch(q) = stretch(p);
    shrink(q) = shrink(p);
    return q;
}
// ~~~ End section 151 ~~~

// ~~~ Section 152 ~~~
pointer new_param_glue(small_number n) {
    pointer p; // the new node
    pointer q; // the glue specification
    p = get_node(SMALL_NODE_SIZE);
    type(p) = GLUE_NODE;
    subtype(p) = n + 1;
    leader_ptr(p) = null;
    q = glue_par(n);
    glue_ptr(p) = q;
    incr(glue_ref_count(q));
    return p;
}
// ~~~ End section 152 ~~~

// ~~~ Section 153 ~~~
pointer new_glue(halfword q) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = GLUE_NODE;
    subtype(p) = NORMAL;
    leader_ptr(p) = null;
    glue_ptr(p) = q;
    incr(glue_ref_count(q));
    return p;
}
// ~~~ End section 153 ~~~

// ~~~ Section 154 ~~~
pointer new_skip_param(small_number n) {
    pointer p; // the new node
    temp_ptr = new_spec(glue_par(n));
    p = new_glue(temp_ptr);
    glue_ref_count(temp_ptr) = null;
    subtype(p) = n + 1;
    return p;
}
// ~~~ End section 154 ~~~

// ~~~ Section 156 ~~~
pointer new_kern(scaled w) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = KERN_NODE;
    subtype(p) = NORMAL;
    width(p) = w;
    return p;
}
// ~~~ End section 156 ~~~

// ~~~ Section 158 ~~~
pointer new_penalty(int m) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = PENALTY_NODE;
    subtype(p) = 0; // the |subtype| is not used
    penalty(p) = m;
    return p;
}
// ~~~ End section 158 ~~~
