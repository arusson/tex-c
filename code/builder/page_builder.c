// ~~~ Section 987 ~~~
// ~~~ Start file |page_builder.c|, 1382 ~~~
#include "builder.h"
#include "breaker.h"
#include "texerror.h"
#include "parser.h"
#include "dvi.h"
#include "arithmetic.h"
// ~~~ End section 1382 ~~~

void freeze_page_specs(small_number s) {
    page_contents = s;
    page_goal = vsize;
    page_max_depth = max_depth;
    page_depth = 0;
    do_all_six(set_page_so_far_zero);
    least_page_cost = AWFUL_BAD;
#ifdef STAT
    if (tracing_pages > 0) {
        begin_diagnostic();
        print_nl("\%\% goal height=");
        print_scaled(page_goal);
        print(", max depth=");
        print_scaled(page_max_depth);
        end_diagnostic(false);
    }
#endif
}
// ~~~ End section 987 ~~~

// ~~~ Section 992 ~~~
void box_error(eight_bits n) {
    error();
    begin_diagnostic();
    print_nl("The following box has been deleted:");
    show_box(box(n));
    end_diagnostic(true);
    flush_node_list(box(n));
    box(n) = null;
}
// ~~~ End section 992 ~~~

// ~~~ Section 993 ~~~
void ensure_vbox(eight_bits n) {
    pointer p; // the box register contents
    p = box(n);
    if (p != null && type(p) == HLIST_NODE) {
        print_err("Insertions can only be added to a vbox");
        help3("Tut tut: You're trying to \\insert into a")
            ("\\box register that now contains an \\hbox.")
            ("Proceed, and I'll discard its present contents.");
        box_error(n);
    }
}
// ~~~ End section 993 ~~~

// ~~~ Section 994 ~~~
// ~~~ Declare the procedure called |fire_up|, 1012 ~~~
void fire_up(pointer c) {
    pointer p, q, r, s;          // nodes being examined and/or changed
    pointer prev_p;              // predecessor of |p|
    int n;                       // insertion box number
    bool wait;                   // should the present insertion be held over?
    int save_vbadness;           // saved value of |vbadness|
    scaled save_vfuzz;           // saved value of |vfuzz|
    pointer save_split_top_skip; // saved value of |split_top_skip|
    
    // ~~~ Set the value of |output_penalty|, 1013 ~~~
    if (type(best_page_break) == PENALTY_NODE) {
        geq_word_define(INT_BASE + OUTPUT_PENALTY_CODE, penalty(best_page_break));
        penalty(best_page_break) = INF_PENALTY;
    }
    else {
        geq_word_define(INT_BASE + OUTPUT_PENALTY_CODE, INF_PENALTY);
    }
    // ~~~ End section 1013 ~~~
    if (bot_mark != null) {
        if (top_mark != null) {
            delete_token_ref(top_mark);
        }
        top_mark = bot_mark;
        add_token_ref(top_mark);
        delete_token_ref(first_mark);
        first_mark = null;
    }

    // ~~~ Put the optimal current page into box 255, update |first_mark| and |bot_mark|, append insertions to their boxes, and put the remaining nodes back on the contribution list, 1014 ~~~
    if (c == best_page_break) {
        best_page_break = null; // |c| not yet linked in
    }
    
    // ~~~ Ensure that box 255 is empty before output, 1015 ~~~
    if (box(255) != null) {
        print_err("");
        print_esc("box");
        print("255 is not void");
        help2("You shouldn't use \\box255 except in \\output routines.")
            ("Proceed, and I'll discard its present contents.");
        box_error(255);
    }
    // ~~~ End section 1015 ~~~
    
    insert_penalties = 0; // this will count the number of insertions held over
    save_split_top_skip = split_top_skip;
    if (holding_inserts <= 0) {
        // ~~~ Prepare all the boxes involved in insertions to act as queues, 1018 ~~~
        r = link(PAGE_INS_HEAD);
        while (r != PAGE_INS_HEAD) {
            if (best_ins_ptr(r) != null) {
                n = subtype(r);
                ensure_vbox(n);
                if (box(n) == null) {
                    box(n) = new_null_box();
                }
                p = box(n) + LIST_OFFSET;
                while (link(p) != null) {
                    p = link(p);
                }
                last_ins_ptr(r) = p;
            }
            r = link(r);
        }
        // ~~~ End section 1018 ~~~
    }
    q = HOLD_HEAD;
    link(q) = null;
    prev_p = PAGE_HEAD;
    p = link(prev_p);
    while (p != best_page_break) {
        if (type(p) == INS_NODE) {
            if (holding_inserts <= 0) {
                // ~~~ Either insert the material specified by node |p| into the appropriate box, or hold it for the next page; also delete node |p| from the current page, 1020 ~~~
                r = link(PAGE_INS_HEAD);
                while (subtype(r) != subtype(p)) {
                    r = link(r);
                }
                if (best_ins_ptr(r) == null) {
                    wait = true;
                }
                else {
                    wait = false;
                    s = last_ins_ptr(r);
                    link(s) = ins_ptr(p);
                    if (best_ins_ptr(r) == p) {
                        // ~~~ Wrap up the box specified by node |r|, splitting node |p| if called for; set |wait = true| if node |p| holds a remainder after splitting, 1021 ~~~
                        if (type(r) == SPLIT_UP
                            && broken_ins(r) == p
                            && broken_ptr(r) != null)
                        {
                            while (link(s) != broken_ptr(r)) {
                                s = link(s);
                            }
                            link(s) = null;
                            split_top_skip = split_top_ptr(p);
                            ins_ptr(p) = prune_page_top(broken_ptr(r));
                            if (ins_ptr(p) != null) {
                                temp_ptr = vpack(ins_ptr(p), NATURAL);
                                height(p) = height(temp_ptr) + depth(temp_ptr);
                                free_node(temp_ptr, BOX_NODE_SIZE);
                                wait = true;
                            }
                        }
                        best_ins_ptr(r) = null;
                        n = subtype(r);
                        temp_ptr = list_ptr(box(n));
                        free_node(box(n), BOX_NODE_SIZE);
                        box(n) = vpack(temp_ptr, NATURAL);
                        // ~~~ End section 1021 ~~~
                    }
                    else {
                        while (link(s) != null) {
                            s = link(s);
                        }
                        last_ins_ptr(r) = s;
                    }
                }
                // ~~~ Either append the insertion node |p| after node |q|, and remove it from the current page, or delete |node(p)|, 1022 ~~~
                link(prev_p) = link(p);
                link(p) = null;
                if (wait) {
                    link(q) = p;
                    q = p;
                    incr(insert_penalties);
                }
                else {
                    delete_glue_ref(split_top_ptr(p));
                    free_node(p, INS_NODE_SIZE);
                }
                p = prev_p;
                // ~~~ End section 1022 ~~~
                // ~~~ End section 1020 ~~~
            }
        }
        else if (type(p) == MARK_NODE) {
            // ~~~ Update the values of |first_mark| and |bot_mark|, 1016 ~~~
            if (first_mark == null) {
                first_mark = mark_ptr(p);
                add_token_ref(first_mark);
            }
            if (bot_mark != null) {
                delete_token_ref(bot_mark);
            }
            bot_mark = mark_ptr(p);
            add_token_ref(bot_mark);
            // ~~~ End section 1016 ~~~
        }
        prev_p = p;
        p = link(prev_p);
    }
    split_top_skip = save_split_top_skip;
    
    // ~~~ Break the current page at node |p|, put it in box 255, and put the remaining nodes on the contribution list, 1017 ~~~
    if (p != null) {
        if (link(CONTRIB_HEAD) == null) {
            if (nest_ptr == 0) {
                tail = page_tail;
            }
            else {
                contrib_tail = page_tail;
            }
        }
        link(page_tail) = link(CONTRIB_HEAD);
        link(CONTRIB_HEAD) = p;
        link(prev_p) = null;
    }
    save_vbadness = vbadness;
    vbadness = INF_BAD;
    save_vfuzz = vfuzz;
    vfuzz = MAX_DIMEN; // inhibit error messages
    box(255) = vpackage(link(PAGE_HEAD), best_size, EXACTLY, page_max_depth);
    vbadness = save_vbadness;
    vfuzz = save_vfuzz;
    if (last_glue != MAX_HALFWORD) {
        delete_glue_ref(last_glue);
    }
    // this sets |last_glue = MAX_HALFWORD|:
    // ~~~ Start a new current page, 991 ~~~
    page_contents = EMPTY;
    page_tail = PAGE_HEAD;
    link(PAGE_HEAD) = null;
    last_glue = MAX_HALFWORD;
    last_penalty = 0;
    last_kern = 0;
    page_depth = 0;
    page_max_depth = 0;
    // ~~~ End section 991 ~~~
    if (q != HOLD_HEAD) {
        link(PAGE_HEAD) = link(HOLD_HEAD);
        page_tail = q;
    }
    // ~~~ End section 1017 ~~~
    
    // ~~~ Delete the page-insertion nodes, 1019 ~~~
    r = link(PAGE_INS_HEAD);
    while (r != PAGE_INS_HEAD) {
        q = link(r);
        free_node(r, PAGE_INS_NODE_SIZE);
        r = q;
    }
    link(PAGE_INS_HEAD) = PAGE_INS_HEAD;
    // ~~~ End section 1019 ~~~
    // ~~~ End section 1014 ~~~
    
    if (top_mark != null && first_mark == null) {
        first_mark = top_mark;
        add_token_ref(top_mark);
    }
    if (output_routine != null) {
        if (dead_cycles >= max_dead_cycles) {
            // ~~~ Explain that too many dead cycles have occurred in a row, 1024 ~~~
            print_err("Output loop---");
            print_int(dead_cycles);
            print(" consecutive dead cycles");
            help3("I've concluded that your \\output is awry; it never does a")
                ("\\shipout, so I'm shipping \\box255 out myself. Next time")
                ("increase \\maxdeadcycles if you want me to be more patient!");
            error();
            // ~~~ End section 1024 ~~~
        }
        else {
            // ~~~ Fire up the user's output routine and |return|, 1025 ~~~
            output_active = true;
            incr(dead_cycles);
            push_nest();
            mode = -VMODE;
            prev_depth = IGNORE_DEPTH;
            mode_line = -line;
            begin_token_list(output_routine, OUTPUT_TEXT);
            new_save_level(OUTPUT_GROUP);
            normal_paragraph();
            scan_left_brace();
            return;
            // ~~~ End section 1025 ~~~
        }
    }
    // ~~~ Perform the default output routine, 1023 ~~~
    if (link(PAGE_HEAD) != null) {
        if (link(CONTRIB_HEAD) == null) {
            if (nest_ptr == 0) {
                tail = page_tail;
            }
            else {
                contrib_tail = page_tail;
            }
        }
        else {
            link(page_tail) = link(CONTRIB_HEAD);
        }
        link(CONTRIB_HEAD) = link(PAGE_HEAD);
        link(PAGE_HEAD) = null;
        page_tail = PAGE_HEAD;
    }
    ship_out(box(255));
    box(255) = null;
    // ~~~ End section 1023 ~~~
}
// ~~~ End section 1012 ~~~

// append contributions to the current page
void build_page() {
    pointer p;          // the node being appended
    pointer q, r;       // nodes being examined
    int b, c;           // badness and cost of current page
    int pi = 0;         // penalty to be added to the badness
    int n;              // insertion box number
    scaled delta, h, w; // sizes used for insertion calculations
    
    if (link(CONTRIB_HEAD) == null || output_active) {
        return;
    }
    do {
continue_lbl:
        p = link(CONTRIB_HEAD);
        
        // ~~~ Update the values of |last_glue|, |last_penalty|, and |last_kern|, 996 ~~~
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
        // ~~~ End section 996 ~~~
        
        // ~~~ Move node |p| to the current page; if it is time for a page break, put the nodes following the break back onto the contribution list, and |return| to the user's output routine if there is one, 997 ~~~
        // ~~~ If the current page is empty and node |p| is to be deleted, |goto done1|; otherwise use node |p| to update the state of the current page; if this node is an insertion, |goto contribute|; otherwise if this node is not a legal breakpoint, |goto contribute| or |update_heights|; otherwise set |pi| to the penalty associated with this breakpoint, 1000 ~~~
        switch (type(p)) {
        case HLIST_NODE:
        case VLIST_NODE:
        case RULE_NODE:
            if (page_contents < BOX_THERE) {
                // ~~~ Initialize the current page, insert the \topskip glue ahead of |p|, and |goto continue|, 1001 ~~~
                if (page_contents == EMPTY) {
                    freeze_page_specs(BOX_THERE);
                }
                else {
                    page_contents = BOX_THERE;
                }
                q = new_skip_param(TOP_SKIP_CODE); // now |temp_ptr = glue_ptr(q)|
                if (width(temp_ptr) > height(p)) {
                    width(temp_ptr) -= height(p);
                }
                else {
                    width(temp_ptr) = 0;
                }
                link(q) = p;
                link(CONTRIB_HEAD) = q;
                goto continue_lbl;
                // ~~~ End section 1001 ~~~
            }
            else {
                // ~~~ Prepare to move a box or rule node to the current page, then |goto contribute|, 1002 ~~~
                page_total += page_depth + height(p);
                page_depth = depth(p);
                goto contribute;
                // ~~~ End section 1002 ~~~
            }
            break;
        
        case WHATSIT_NODE:
            // ~~~ Prepare to move whatsit |p| to the current page, then |goto contribute|, 1364 ~~~
            goto contribute;
            // ~~~ End section 1364 ~~~
        
        case GLUE_NODE:
            if (page_contents < BOX_THERE) {
                goto done1;
            }
            else if (precedes_break(page_tail)) {
                pi = 0;
            }
            else {
                goto update_heights;
            }
            break;
        
        case KERN_NODE:
            if (page_contents < BOX_THERE) {
                goto done1;
            }
            else if (link(p) == null) {
                return;
            }
            else if (type(link(p)) == GLUE_NODE) {
                pi = 0;
            }
            else {
                goto update_heights;
            }
            break;
        
        case PENALTY_NODE:
            if (page_contents < BOX_THERE) {
                goto done1;
            }
            else {
                pi = penalty(p);
            }
            break;
        
        case MARK_NODE:
            goto contribute;
        
        case INS_NODE:
            // ~~~ Append an insertion to the current page and |goto contribute|, 1008 ~~~
            if (page_contents == EMPTY) {
                freeze_page_specs(INSERTS_ONLY);
            }
            n = subtype(p);
            r = PAGE_INS_HEAD;
            while (n >= subtype(link(r))) {
                r = link(r);
            }
            if (subtype(r) != n) {
                // ~~~ Create a page insertion node with |subtype(r) = n|, and include the glue correction for box |n| in the current page state, 1009 ~~~
                q = get_node(PAGE_INS_NODE_SIZE);
                link(q) = link(r);
                link(r) = q;
                r = q;
                subtype(r) = n;
                type(r) = INSERTING;
                ensure_vbox(n);
                if (box(n) == null) {
                    height(r) = 0;
                }
                else {
                    height(r) = height(box(n)) + depth(box(n));
                }
                best_ins_ptr(r) = null;
                q = skip(n);
                if (count(n) == 1000) {
                    h = height(r);
                }
                else {
                    h = x_over_n(height(r), 1000)*count(n);
                }
                page_goal -= h + width(q);
                page_so_far[2 + stretch_order(q)] += stretch(q);
                page_shrink += shrink(q);
                if (shrink_order(q) != NORMAL && shrink(q) != 0) {
                    print_err("Infinite glue shrinkage inserted from ");
                    print_esc("skip");
                    print_int(n);
                    help3("The correction glue for page breaking with insertions")
                        ("must have finite shrinkability. But you may proceed,")
                        ("since the offensive shrinkability has been made finite.");
                    error();
                }
                // ~~~ End section 1009 ~~~
            }
            if (type(r) == SPLIT_UP) {
                insert_penalties += float_cost(p);
            }
            else {
                last_ins_ptr(r) = p;
                delta = page_goal - page_total - page_depth + page_shrink;
                // this much room is left if we shrink the maximum
                if (count(n) == 1000) {
                    h = height(p);
                }
                else {
                    h = x_over_n(height(p), 1000)*count(n); // this much room is needed
                }
                if ((h <= 0 || h <= delta)
                    && height(p) + height(r) <= dimen(n))
                {
                    page_goal -= h;
                    height(r) += height(p);
                }
                else {
                    // ~~~ Find the best way to split the insertion, and change |type(r)| to |SPLIT_UP|, 1010 ~~~
                    if (count(n) <= 0) {
                        w = MAX_DIMEN;
                    }
                    else {
                        w = page_goal - page_total - page_depth;
                        if (count(n) != 1000) {
                            w = x_over_n(w, count(n))*1000;
                        }
                    }
                    if (w > dimen(n) - height(r)) {
                        w = dimen(n) - height(r);
                    }
                    q = vert_break(ins_ptr(p), w, depth(p));
                    height(r) += best_height_plus_depth;
                    
#ifdef STAT
                    if (tracing_pages > 0) {
                        // ~~~ Display the insertion split cost, 1011 ~~~
                        begin_diagnostic();
                        print_nl("\% split");
                        print_int(n);
                        print(" to ");
                        print_scaled(w);
                        print_char(',');
                        print_scaled(best_height_plus_depth);
                        print(" p=");
                        if (q == null) {
                            print_int(EJECT_PENALTY);
                        }
                        else if (type(q) == PENALTY_NODE) {
                            print_int(penalty(q));
                        }
                        else {
                            print_char('0');
                        }
                        end_diagnostic(false);
                        // ~~~ End section 1011 ~~~
                    }
#endif
                    
                    if (count(n) != 1000) {
                      best_height_plus_depth = x_over_n(best_height_plus_depth, 1000)*count(n);
                    }
                    page_goal -= best_height_plus_depth;
                    type(r) = SPLIT_UP;
                    broken_ptr(r) = q;
                    broken_ins(r) = p;
                    if (q == null) {
                        insert_penalties += EJECT_PENALTY;
                    }
                    else if (type(q) == PENALTY_NODE) {
                        insert_penalties += penalty(q);
                    }
                    // ~~~ End section 1010 ~~~
                }
            }
            goto contribute;
            // ~~~ End section 1008 ~~~
        
        default:
            confusion("page");
        }
        // ~~~ End section 1000 ~~~
        
        // ~~~ Check if node |p| is a new champion breakpoint; then if it is time for a page break, prepare for output, and either fire up the user's output routine and |return| or ship out the page and |goto done|, 1005 ~~~
        if (pi < INF_PENALTY) {
            // ~~~ Compute the badness, |b|, of the current page, using |AWFUL_BAD| if the box is too full, 1007 ~~~
            if (page_total < page_goal) {
                if (page_so_far[3] != 0
                    || page_so_far[4] != 0
                    || page_so_far[5] != 0)
                {
                    b = 0;
                }
                else {
                    b = badness(page_goal - page_total, page_so_far[2]);
                }
            }
            else if (page_total - page_goal > page_shrink) {
                b = AWFUL_BAD;
            }
            else {
                b = badness(page_total - page_goal, page_shrink);
            }
            // ~~~ End section 1007 ~~~
            if (b < AWFUL_BAD) {
                if (pi <= EJECT_PENALTY) {
                    c = pi;
                }
                else if (b < INF_BAD) {
                    c = b + pi + insert_penalties;
                }
                else {
                    c = DEPLORABLE;
                }
            }
            else {
                c = b;
            }
            if (insert_penalties >= 10000) {
                c = AWFUL_BAD;
            }
        
#ifdef STAT
            if (tracing_pages > 0) {
                // ~~~ Display the page break cost, 1006 ~~~
                begin_diagnostic();
                print_nl("\%");
                print(" t=");
                print_totals();
                print(" g=");
                print_scaled(page_goal);
                print(" b=");
                if (b == AWFUL_BAD) {
                    print_char('*');
                }
                else {
                    print_int(b);
                }
                print(" p=");
                print_int(pi);
                print(" c=");
                if (c == AWFUL_BAD) {
                    print_char('*');
                }
                else {
                    print_int(c);
                }
                if (c <= least_page_cost) {
                    print_char('#');
                }
                end_diagnostic(false);
                // ~~~ End section 1006 ~~~
            }
#endif
        
            if (c <= least_page_cost) {
                best_page_break = p;
                best_size = page_goal;
                least_page_cost = c;
                r = link(PAGE_INS_HEAD);
                while (r != PAGE_INS_HEAD) {
                    best_ins_ptr(r) = last_ins_ptr(r);
                    r = link(r);
                }
            }
            if (c == AWFUL_BAD || pi <= EJECT_PENALTY) {
                fire_up(p); // output the current page at the best place
                if (output_active) {
                    return; // user's output routine will act
                }
                goto done; // the page has been shipped out by default output routine
            }
        }
        // ~~~ End section 1005 ~~~
        
        if (type(p) < GLUE_NODE || type(p) > KERN_NODE) {
            goto contribute;
        }
update_heights:
        // ~~~ Update the current page measurements with respect to the glue or kern specified by node |p|, 1004 ~~~
        if (type(p) == KERN_NODE) {
            q = p;
        }
        else {
            q = glue_ptr(p);
            page_so_far[2 + stretch_order(q)] += stretch(q);
            page_shrink += shrink(q);
            if (shrink_order(q) != NORMAL && shrink(q) != 0) {
                print_err("Infinite glue shrinkage found on current page");
                help4("The page about to be output contains some infinitely")
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
        page_total += page_depth + width(q);
        page_depth = 0;
        // ~~~ End section 1004 ~~~
contribute:
        // ~~~ Make sure that |page_max_depth| is not exceeded, 1003 ~~~
        if (page_depth > page_max_depth) {
            page_total += page_depth - page_max_depth;
            page_depth = page_max_depth;
        }
        // ~~~ End section 1003 ~~~
        // ~~~ Link node |p| into the current page and |goto done|, 998 ~~~
        link(page_tail) = p;
        page_tail = p;
        link(CONTRIB_HEAD) = link(p);
        link(p) = null;
        goto done;
        // ~~~ End section 998 ~~~
done1:
        // ~~~ Recycle node |p|, 999 ~~~
        link(CONTRIB_HEAD) = link(p);
        link(p) = null;
        flush_node_list(p);
        // ~~~ End section 999 ~~~
done:
        // ~~~ End section 997 ~~~
    } while (link(CONTRIB_HEAD) != null);
    
    // ~~~ Make the contribution list empty by setting its tail to |CONTRIB_HEAD|, 995 ~~~
    if (nest_ptr == 0) {
        tail = CONTRIB_HEAD; // vertical mode
    }
    else {
        contrib_tail = CONTRIB_HEAD; // other modes
    }
    // ~~~ End section 995 ~~~
}
// ~~~ End section 994 ~~~
