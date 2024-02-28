// ~~~ Section 686 ~~~
// ~~~ Start file |math_structures.c|, 1382 ~~~
#include "texmath.h"
// ~~~ End section 1382 ~~~

pointer new_noad() {
    pointer p;
    p = get_node(NOAD_SIZE);
    type(p) = ORD_NOAD;
    subtype(p) = NORMAL;
    mem[nucleus(p)] = empty_field;
    mem[subscr(p)] = empty_field;
    mem[supscr(p)] = empty_field;
    return p;
}
// ~~~ End section 686 ~~~

// ~~~ Section 688 ~~~
// create a style node
pointer new_style(small_number s) {
    pointer p; // the new node
    p = get_node(STYLE_NODE_SIZE);
    type(p) = STYLE_NODE;
    subtype(p) = s;
    width(p) = 0;
    depth(p) = 0; // the |width| and |depth| are not used
    return p;
}
// ~~~ End section 688 ~~~

// ~~~ Section 689 ~~~
// create a choice node
pointer new_choice() {
    pointer p; // the new node
    p = get_node(STYLE_NODE_SIZE);
    type(p) = CHOICE_NODE;
    subtype(p) = 0; // the |subtype| is not used
    display_mlist(p) = null;
    text_mlist(p) = null;
    script_mlist(p) = null;
    script_script_mlist(p) = null;
    return p;
}
// ~~~ End section 689 ~~~
