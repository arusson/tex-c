// ~~~ Section 968 ~~~
// ~~~ Start file |page_break.c|, 1382 ~~~
#include "breaker.h"
#include "builder.h"
#include "texerror.h"
#include "parser.h"
#include "arithmetic.h"
// ~~~ End section 1382 ~~~

// adjust top after page break
pointer prune_page_top(pointer p) {
    pointer prev_p; // lags one step behind |p|
    pointer q;      // temporary variable for list manipulation
    prev_p = TEMP_HEAD;
    link(TEMP_HEAD) = p;
    while (p != null) {
        switch (type(p)) {
        case HLIST_NODE:
        case VLIST_NODE:
        case RULE_NODE:
            // ~~~ Insert glue for |split_top_skip| and set |p = null|, 969 ~~~
            q = new_skip_param(SPLIT_TOP_SKIP_CODE);
            link(prev_p) = q;
            link(q) = p;
            // now |temp_ptr = glue_ptr(q)|
            if (width(temp_ptr) > height(p)) {
                width(temp_ptr) -= height(p);
            }
            else {
                width(temp_ptr) = 0;
            }
            p = null;
            // ~~~ End section 969 ~~~
            break;
        
        case WHATSIT_NODE:
        case MARK_NODE:
        case INS_NODE:
            prev_p = p;
            p = link(prev_p);
            break;
        
        case GLUE_NODE:
        case KERN_NODE:
        case PENALTY_NODE:
            q = p;
            p = link(q);
            link(q) = null;
            link(prev_p) = p;
            flush_node_list(q);
            break;
        
        default:
            confusion("pruning");
        }
    }
    return link(TEMP_HEAD);
}
// ~~~ End section 968 ~~~

// ~~~ Section 970 ~~~
// finds optimum page break
pointer vert_break(pointer p, scaled h, scaled d) {
    pointer prev_p;            // if |p| is a glue node, |type(prev_p)| determines whether |p| is a legal breakpoint
    pointer q, r;              // glue specifications
    int pi = 0;                // penalty value
    int b;                     // badness at a trial breakpoint
    int least_cost;            // the smallest badness plus penalties found so far
    pointer best_place = null; // the most recent break that leads to |least_cost|
    scaled prev_dp;            // depth of previous box in the list
    small_number t;            // |type| of the node following a kern
    
    prev_p = p; // an initial glue node is not a legal breakpoint
    least_cost = AWFUL_BAD;
    do_all_six(set_height_zero);
    prev_dp = 0;
    while(true) {
        // ~~~ If node |p| is a legal breakpoint, check if this break is the best known, and |goto done| if |p| is null or if the page-so-far is already too full to accept more stuff, 972 ~~~
        if (p == null) {
            pi = EJECT_PENALTY;
        }
        else {
            // ~~~ Use node |p| to update the current height and depth measurements; if this node is not a legal breakpoint, |goto not_found| or |update_heights|, otherwise set |pi| to the associated penalty at the break, 973 ~~~
            switch (type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case RULE_NODE: 
                cur_height += prev_dp + height(p);
                prev_dp = depth(p);
                goto not_found;
            
            case WHATSIT_NODE:
                // ~~~ Process whatsit |p| in |vert_break| loop, |goto not_found|, 1365 ~~~
                goto not_found;
                // ~~~ End section 1365 ~~~
            
            case GLUE_NODE:
                if (precedes_break(prev_p)) {
                    pi = 0;
                }
                else {
                    goto update_heights;
                }
                break;
            
            case KERN_NODE:
                if (link(p) == null) {
                    t = PENALTY_NODE;
                }
                else {
                    t = type(link(p));
                }
                if (t == GLUE_NODE) {
                    pi = 0;
                }
                else {
                    goto update_heights;
                }
                break;
            
            case PENALTY_NODE:
                pi = penalty(p);
                break;
            
            case MARK_NODE:
            case INS_NODE:
                goto not_found;
            
            default:
                confusion("vertbreak");
            }
            // ~~~ End section 973 ~~~
        }
        // ~~~ Check if node |p| is a new champion breakpoint; then |goto done| if |p| is a forced break or if the page-so-far is already too full, 974 ~~~
        if (pi < INF_PENALTY) {
            // ~~~ Compute the badness, |b|, using |AWFUL_BAD| if the box is too full, 975 ~~~
            if (cur_height < h) {
                if (active_height[3] != 0
                  || active_height[4] != 0
                  || active_height[5] != 0)
                {
                  b = 0;
                }
                else {
                  b = badness(h - cur_height, active_height[2]);
                }
            }
            else if (cur_height - h > active_height[6]) {
                b = AWFUL_BAD;
            }
            else {
                b = badness(cur_height - h, active_height[6]);
            }
            // ~~~ End section 975 ~~~
            if (b < AWFUL_BAD) {
                if (pi <= EJECT_PENALTY) {
                    b = pi;
                }
                else if (b < INF_BAD) {
                    b += pi;
                }
                else {
                    b = DEPLORABLE;
                }
            }
            if (b <= least_cost) {
                best_place = p;
                least_cost = b;
                best_height_plus_depth = cur_height + prev_dp;
            }
            if (b == AWFUL_BAD || pi <= EJECT_PENALTY) {
                goto done;
            }
        }
        // ~~~ End section 974 ~~~
        if (type(p) < GLUE_NODE || type(p) > KERN_NODE) {
            goto not_found;
        }
        
update_heights:
        // ~~~ Update the current height and depth measurements with respect to a glue or kern node |p|, 976 ~~~
        if (type(p) == KERN_NODE) {
            q = p;
        }
        else {
            q = glue_ptr(p);
            active_height[2 + stretch_order(q)] += stretch(q);
            active_height[6] += shrink(q);
            if (shrink_order(q) != NORMAL && shrink(q) != 0) {
                print_err("Infinite glue shrinkage found in box being split");
                help4("The box you are \\vsplitting contains some infinitely")
                    ("shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.")
                    ("Such glue doesn't belong there; but you can safely proceed,")
                    ("since the offensive shrinkability has been made finite.");
                error();
                r = new_spec(q);
                shrink_order(r) = NORMAL;
                delete_glue_ref(q);
                glue_ptr(p) = r;
                q = r;
            }
        }
        cur_height += prev_dp + width(q);
        prev_dp = 0;
        // ~~~ End section 976 ~~~
        
not_found:
        if (prev_dp > d) {
            cur_height += prev_dp - d;
            prev_dp = d;
        }
        // ~~~ End section 972 ~~~
        prev_p = p;
        p = link(prev_p);
    }
done:
    return best_place;
}
// ~~~ End section 970 ~~~

// ~~~ Section 977 ~~~
// extracts a page of height |h| from box |n|
pointer vsplit(eight_bits n, scaled h) {
    pointer v; // the box to be split
    pointer p; // runs through the vlist
    pointer q; // points to where the break occurs
    v = box(n);
    if (split_first_mark != null) {
        delete_token_ref(split_first_mark);
        split_first_mark = null;
        delete_token_ref(split_bot_mark);
        split_bot_mark = null;
    }
    // ~~~ Dispense with trivial cases of void or bad boxes, 978 ~~~
    if (v == null) {
        return null;
    }
    if (type(v) != VLIST_NODE) {
        print_err("");
        print_esc("vsplit");
        print(" needs a ");
        print_esc("vbox");
        help2("The box you are trying to split is an \\hbox.")
            ("I can't split such a box, so I'll leave it alone.");
        error();
        return null;
    }
    // ~~~ End section 978 ~~~
    q = vert_break(list_ptr(v), h, split_max_depth);
    // ~~~ Look at all the marks in nodes before the break, and set the final link to |null| at the break, 979 ~~~
    p = list_ptr(v);
    if (p == q) {
        list_ptr(v) = null;
    }
    else {
        while(true) {
            if (type(p) == MARK_NODE) {
                if (split_first_mark == null) {
                    split_first_mark = mark_ptr(p);
                    split_bot_mark = split_first_mark;
                    token_ref_count(split_first_mark) += 2;
                }
                else {
                    delete_token_ref(split_bot_mark);
                    split_bot_mark = mark_ptr(p);
                    add_token_ref(split_bot_mark);
                }
            }
            if (link(p) == q) {
                link(p) = null;
                break; // goto done
            }
            p = link(p);
        }
    }
    // done:
    // ~~~ End section 979 ~~~
    q = prune_page_top(q);
    p = list_ptr(v);
    free_node(v, BOX_NODE_SIZE);
    if (q == null) {
        box(n) = null; // the |eq_level| of the box stays the same
    }
    else {
        box(n) = vpack(q, NATURAL);
    }
    return vpackage(p, h, EXACTLY, split_max_depth);
}
// ~~~ End section 977 ~~~
