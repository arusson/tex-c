// ~~~ Section 815 ~~~
// ~~~ Start file |line_break.c|, 1382 ~~~
#include "breaker.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "arithmetic.h"
#include "extensions.h"
// ~~~ End section 1382 ~~~

// ~~~ Declare subprocedures for |line_break|, 826 ~~~
// recovers from infinite shrinkage
pointer finite_shrink(pointer p) {
    pointer q; // new glue specification
    if (no_shrink_error_yet) {
        no_shrink_error_yet = false;
#ifdef STAT
        if (tracing_paragraphs > 0) {
            end_diagnostic(true);
        }
#endif
        print_err("Infinite glue shrinkage found in a paragraph");
        help5("The paragraph just ended includes some glue that has")
            ("infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.")
            ("Such glue doesn't belong there---it allows a paragraph")
            ("of any length to fit on one line. But it's safe to proceed,")
            ("since the offensive shrinkability has been made finite.");
        error();
#ifdef STAT
        if (tracing_paragraphs > 0) {
            begin_diagnostic();
        }
#endif
    }
    q = new_spec(p);
    shrink_order(q) = NORMAL;
    delete_glue_ref(p);
    return q;
}

// ~~~ Section 829 ~~~
void try_break(int pi, small_number break_type) {
    pointer r;      // runs through the active list
    pointer prev_r; // stays a step behind |r|
    halfword old_l; // maximum line number in current equivalence class of lines
    bool no_break_yet; // have we found a feasible break at |cur_p|?
    // ~~~ Other local variables for |try_break|, 830 ~~~
    pointer prev_prev_r = null; // a step behind |prev_r|, if |type(prev_r) = DELTA_NODE|
    pointer s;                  // runs through nodes ahead of |cur_p|
    pointer q;                  // points to a new node being created
    pointer v;                  // points to a glue specification or a node ahead of |cur_p|
    int t;                      // node count, if |cur_p| is a discretionary node
    internal_font_number f;     // used in character width calculation
    halfword l;                 // line number of current active node
    bool node_r_stays_active;   // should node |r| remain in the active list?
    scaled line_width = 0;      // the current line will be justified to this width
    int fit_class;              // possible fitness class of test line
    halfword b;                 // badness of test line
    int d;                      // demerits of test line
    bool artificial_demerits;   // has |d| been forced to zero?
#ifdef STAT
    pointer save_link;          // temporarily holds value of |link(cur_p)|
#endif
    scaled shortfall;           // used in badness calculations
    // ~~~ End section 830 ~~~
    
    // ~~~ Make sure that |pi| is in the proper range, 831 ~~~
    if (abs(pi) >= INF_PENALTY) {
        if (pi > 0) {
            goto end; // this breakpoint is inhibited by infinite penalty
        }
        else {
            pi = EJECT_PENALTY; // this breakpoint will be forced
        }
    }
    // ~~~ End section 831 ~~~
    no_break_yet = true;
    prev_r = ACTIVE;
    old_l = 0;
    do_all_six(copy_to_cur_active);
    while(true) {
continue_lbl:
        r = link(prev_r);
        
        // ~~~ If node |r| is of type |DELTA_NODE|, update |cur_active_width|, set |prev_r| and |prev_prev_r|, then |goto continue|, 832 ~~~
        if (type(r) == DELTA_NODE) {
            do_all_six(update_width);
            prev_prev_r = prev_r;
            prev_r = r;
            goto continue_lbl;
        }
        // ~~~ End section 832 ~~~

        // ~~~ If a line number class has ended, create new active nodes for the best feasible breaks in that class; then |return| if |r = LAST_ACTIVE|, otherwise compute the new |line_width|, 835 ~~~
        l = line_number(r);
        if (l > old_l) {
            // now we are no longer in the inner loop
            if (minimum_demerits < AWFUL_BAD
                && (old_l != easy_line || r == LAST_ACTIVE))
            {
                // ~~~ Create new active nodes for the best feasible breaks just found, 836 ~~~
                if (no_break_yet) {
                    // ~~~ Compute the values of |break_width|, 837 ~~~
                    no_break_yet = false;
                    do_all_six(set_break_width_to_background);
                    s = cur_p;
                    if (break_type > UNHYPHENATED && cur_p != null) {
                        // ~~~ Compute the discretionary |break_width| values, 840 ~~~
                        t = replace_count(cur_p);
                        v = cur_p;
                        s = post_break(cur_p);
                        while (t > 0) {
                            decr(t);
                            v = link(v);
                            // ~~~ Subtract the width of node |v| from |break_width|, 841 ~~~
                            if (is_char_node(v)) {
                                f = font(v);
                                break_width[1] -= char_width(f, char_info(f, character(v)));
                            }
                            else {
                                switch (type(v)) {
                                case LIGATURE_NODE:
                                    f = font(lig_char(v));
                                    break_width[1] -= char_width(f, char_info(f, character(lig_char(v))));
                                    break;
                                
                                case HLIST_NODE:
                                case VLIST_NODE:
                                case RULE_NODE:
                                case KERN_NODE:
                                    break_width[1] -= width(v);
                                    break;
                                
                                default:
                                    confusion("disc1");
                                }
                            }
                            // ~~~ End section 841 ~~~
                        }
                        while (s != null) {
                            // ~~~ Add the width of node |s| to |break_width|, 842 ~~~
                            if (is_char_node(s)) {
                                f = font(s);
                                break_width[1] += char_width(f, char_info(f, character(s)));
                            }
                            else {
                                switch (type(s)) {
                                case LIGATURE_NODE:
                                    f = font(lig_char(s));
                                    break_width[1] += char_width(f, char_info(f, character(lig_char(s))));
                                    break;
                            
                                case HLIST_NODE:
                                case VLIST_NODE:
                                case RULE_NODE:
                                case KERN_NODE:
                                    break_width[1] += width(s);
                                    break;
                                
                                default:
                                    confusion("disc2");
                                }
                            }
                            // ~~~ End section 842 ~~~
                            s = link(s);
                        }
                        break_width[1] += disc_width;
                        if (post_break(cur_p) == null) {
                            s = link(v); // nodes may be discardable after the break
                        }
                        // ~~~ End section 840 ~~~
                    }
                    while (s != null) {
                        if (is_char_node(s)) {
                            goto done;
                        }
                        switch (type(s)) {
                        case GLUE_NODE:
                            // ~~~ Subtract glue from |break_width|, 838 ~~~
                            v = glue_ptr(s);
                            break_width[1] -= width(v);
                            break_width[2 + stretch_order(v)] -= stretch(v);
                            break_width[6] -= shrink(v);
                            // ~~~ End section 838 ~~~
                            break;
                        
                        case PENALTY_NODE:
                            do_nothing;
                            break;
                        
                        case MATH_NODE:
                            break_width[1] -= width(s);
                            break;
                        
                        case KERN_NODE:
                            if (subtype(s) != EXPLICIT) {
                                goto done;
                            }
                            else {
                                break_width[1] -= width(s);
                            }
                            break;
                        
                        default:
                            goto done;
                        }
                        s = link(s);
                    }
done:
                    // ~~~ End section 837 ~~~
                }
                // ~~~ Insert a delta node to prepare for breaks at |cur_p|, 843 ~~~
                if (type(prev_r) == DELTA_NODE) {
                    // modify an existing delta node
                    do_all_six(convert_to_break_width);
                }
                else if (prev_r == ACTIVE) {
                    // no delta node needed at the beginning
                    do_all_six(store_break_width);
                }
                else {
                    q = get_node(DELTA_NODE_SIZE);
                    link(q) = r;
                    type(q) = DELTA_NODE;
                    subtype(q) = 0; // the |subtype| is not used
                    do_all_six(new_delta_to_break_width);
                    link(prev_r) = q;
                    prev_prev_r = prev_r;
                    prev_r = q;
                }
                // ~~~ End section 843 ~~~
                if (abs(adj_demerits) >= AWFUL_BAD - minimum_demerits) {
                    minimum_demerits = AWFUL_BAD - 1;
                }
                else {
                    minimum_demerits += abs(adj_demerits);
                }
                for(fit_class = VERY_LOOSE_FIT; fit_class <= TIGHT_FIT; fit_class++) {
                    if (minimal_demerits[fit_class] <= minimum_demerits) {
                        // ~~~ Insert a new active node from |best_place[fit_class]| to |cur_p|, 845 ~~~
                        q = get_node(PASSIVE_NODE_SIZE);
                        link(q) = passive;
                        passive = q;
                        cur_break(q) = cur_p;
#ifdef STAT
                        incr(pass_number);
                        serial(q) = pass_number;
#endif
                        prev_break(q) = best_place[fit_class];
                        q = get_node(ACTIVE_NODE_SIZE);
                        break_node(q) = passive;
                        line_number(q) = best_pl_line[fit_class] + 1;
                        fitness(q) = fit_class;
                        type(q) = break_type;
                        total_demerits(q) = minimal_demerits[fit_class];
                        link(q) = r;
                        link(prev_r) = q;
                        prev_r = q;
#ifdef STAT
                        if (tracing_paragraphs > 0) {
                            // ~~~ Print a symbolic description of the new break node, 846 ~~~
                            print_nl("@@");
                            print_int(serial(passive));
                            print(": line ");
                            print_int(line_number(q) - 1);
                            print_char('.');
                            print_int(fit_class);
                            if (break_type == HYPHENATED) {
                                print_char('-');
                            }
                            print(" t=");
                            print_int(total_demerits(q));
                            print(" -> @@");
                            if (prev_break(passive) == null) {
                                print_char('0');
                            }
                            else {
                                print_int(serial(prev_break(passive)));
                            }
                            // ~~~ End section 846 ~~~
                        }
#endif
                        // ~~~ End section 845 ~~~
                    }
                    minimal_demerits[fit_class] = AWFUL_BAD;
                }
                minimum_demerits = AWFUL_BAD;
                // ~~~ Insert a delta node to prepare for the next active node, 844 ~~~
                if (r != LAST_ACTIVE) {
                    q = get_node(DELTA_NODE_SIZE);
                    link(q) = r;
                    type(q) = DELTA_NODE;
                    subtype(q) = 0; // the |subtype| is not used
                    do_all_six(new_delta_from_break_width);
                    link(prev_r) = q;
                    prev_prev_r = prev_r;
                    prev_r = q;
                }
                // ~~~ End section 844 ~~~
                // ~~~ End section 836 ~~~
            }
            if (r == LAST_ACTIVE) {
                goto end;
            }
            // ~~~ Compute the new line width, 850 ~~~
            if (l > easy_line) {
                line_width = second_width;
                old_l = MAX_HALFWORD - 1;
            }
            else {
                old_l = l;
                if (l > last_special_line) {
                    line_width = second_width;
                }
                else if (par_shape_ptr == null) {
                    line_width = first_width;
                }
                else {
                    line_width = mem[par_shape_ptr + 2*l].sc;
                }
            }
            // ~~~ End section 850 ~~~
        }
        // ~~~ End section 835 ~~~
        
        // ~~~ Consider the demerits for a line from |r| to |cur_p|; deactivate node |r| if it should no longer be active; then |goto continue| if a line from |r| to |cur_p| is infeasible, otherwise record a new feasible break, 851 ~~~
        artificial_demerits = false;
        shortfall = line_width - cur_active_width[1]; // we're this much too short
        if (shortfall > 0) {
            // ~~~ Set the value of |b| to the badness for stretching the line, and compute the corresponding |fit_class|, 852 ~~~
            if (cur_active_width[3] != 0
                || cur_active_width[4] != 0
                || cur_active_width[5] != 0)
            {
                b = 0;
                fit_class = DECENT_FIT; // infinite stretch
            }
            else if (shortfall > 7230584 && cur_active_width[2] < 1663497) {
                b = INF_BAD;
                fit_class = VERY_LOOSE_FIT;
            }
            else {
                b = badness(shortfall, cur_active_width[2]);
                if (b > 12) {
                    if (b > 99) {
                        fit_class = VERY_LOOSE_FIT;
                    }
                    else {
                        fit_class = LOOSE_FIT;
                    }
                }
                else {
                    fit_class = DECENT_FIT;
                }
            }
            // ~~~ End section 852 ~~~
        }
        else{
            // ~~~ Set the value of |b| to the badness for shrinking the line, and compute the corresponding |fit_class|, 853 ~~~
            if (-shortfall > cur_active_width[6]) {
                b = INF_BAD + 1;
            }
            else {
                b = badness(-shortfall, cur_active_width[6]);
            }
            if (b > 12) {
                fit_class = TIGHT_FIT;
            }
            else {
                fit_class = DECENT_FIT;
            }
            // ~~~ End section 853 ~~~
        }
        if (b > INF_BAD || pi == EJECT_PENALTY) {
            // ~~~ Prepare to deactivate node |r|, and |goto deactivate| unless there is a reason to consider lines of text from |r| to |cur_p|, 854 ~~~
            if (final_pass
                && minimum_demerits == AWFUL_BAD
                && link(r) == LAST_ACTIVE
                && prev_r == ACTIVE)
            {
                artificial_demerits = true; // set demerits zero, this break is forced
            }
            else if (b > threshold) {
                goto deactivate;
            }
            node_r_stays_active = false;
            // ~~~ End section 854 ~~~
        }
        else {
            prev_r = r;
            if (b > threshold) {
                goto continue_lbl;
            }
            node_r_stays_active = true;
        }
        // ~~~ Record a new feasible break, 855 ~~~
        if (artificial_demerits) {
            d = 0;
        }
        else {
            // ~~~ Compute the demerits, |d|, from |r| to |cur_p|, 859 ~~~
            d = line_penalty + b;
            if (abs(d) >= 10000) {
                d = 100000000;
            }
            else {
                d *= d;
            }
            if (pi != 0) {
                if (pi > 0) {
                    d += pi*pi;
                }
                else if (pi > EJECT_PENALTY) {
                    d -= pi*pi;
                }
            }
            if (break_type == HYPHENATED && type(r) == HYPHENATED) {
                if (cur_p != null) {
                    d += double_hyphen_demerits;
                }
                else {
                    d += final_hyphen_demerits;
                }
            }
            if (abs(fit_class - fitness(r)) > 1) {
                d += adj_demerits;
            }
            // ~~~ End section 859 ~~~
        }
#ifdef STAT
        if (tracing_paragraphs > 0) {
            // ~~~ Print a symbolic description of this feasible break, 856 ~~~
            if (printed_node != cur_p) {
                // ~~~ Print the list between |printed_node| and |cur_p|, then set |printed_node = cur_p|, 857 ~~~
                print_nl("");
                if (cur_p == null) {
                    short_display(link(printed_node));
                }
                else {
                    save_link = link(cur_p);
                    link(cur_p) = null;
                    print_nl("");
                    short_display(link(printed_node));
                    link(cur_p) = save_link;
                }
                printed_node = cur_p;
                // ~~~ End section 857 ~~~
            }
            print_nl("@");
            if (cur_p == null) {
                print_esc("par");
            }
            else if (type(cur_p) != GLUE_NODE) {
                if (type(cur_p) == PENALTY_NODE) {
                    print_esc("penalty");
                }
                else if (type(cur_p) == DISC_NODE) {
                    print_esc("discretionary");
                }
                else if (type(cur_p) == KERN_NODE) {
                    print_esc("kern");
                }
                else {
                    print_esc("math");
                }
            }
            print(" via @@");
            if (break_node(r) == null) {
                print_char('0');
            }
            else {
                print_int(serial(break_node(r)));
            }
            print(" b=");
            if (b > INF_BAD) {
                print_char('*');
            }
            else {
                print_int(b);
            }
            print(" p=");
            print_int(pi);
            print(" d=");
            if (artificial_demerits) {
                print_char('*');
            }
            else {
                print_int(d);
            }
            // ~~~ End section 856 ~~~
        }
#endif
        d += total_demerits(r); // this is the minimum total demerits from the beginning to |cur_p| via |r|
        if (d <= minimal_demerits[fit_class]) {
            minimal_demerits[fit_class] = d;
            best_place[fit_class] = break_node(r);
            best_pl_line[fit_class] = l;
            if (d < minimum_demerits) {
                minimum_demerits = d;
            }
        }
        // ~~~ End section 855 ~~~
        if (node_r_stays_active) {
            goto continue_lbl; // |prev_r| has been set to |r|
        }
deactivate:
        // ~~~ Deactivate node |r|, 860 ~~~
        link(prev_r) = link(r);
        free_node(r, ACTIVE_NODE_SIZE);
        if (prev_r == ACTIVE) {
            // ~~~ Update the active widths, since the first active node has been deleted, 861 ~~~
            r = link(ACTIVE);
            if (type(r) == DELTA_NODE) {
                do_all_six(update_active);
                do_all_six(copy_to_cur_active);
                link(ACTIVE) = link(r);
                free_node(r, DELTA_NODE_SIZE);
            }
            // ~~~ End section 861 ~~~
        }
        else if (type(prev_r) == DELTA_NODE) {
            r = link(prev_r);
            if (r == LAST_ACTIVE) {
                do_all_six(downdate_width);
                link(prev_prev_r) = LAST_ACTIVE;
                free_node(prev_r, DELTA_NODE_SIZE);
                prev_r = prev_prev_r;
            }
            else if (type(r) == DELTA_NODE) {
                do_all_six(update_width);
                do_all_six(combine_two_deltas);
                link(prev_r) = link(r);
                free_node(r, DELTA_NODE_SIZE);
            }
        }
        // ~~~ End section 860 ~~~
        // ~~~ End section 851 ~~~
    }
end:
#ifdef STAT
    // ~~~ Update the value of |printed_node| for symbolic displays, 858 ~~~
    if (cur_p == printed_node
        && cur_p != null
        && type(cur_p) == DISC_NODE)
    {
        t = replace_count(cur_p);
        while (t > 0) {
            decr(t);
            printed_node = link(printed_node);
        }
    }
    // ~~~ End section 858 ~~~
#endif
}
// ~~~ End section 829 ~~~

// ~~~ Section 877 ~~~
void post_line_break(int final_widow_penalty) {
    pointer q, r, s;      // temporary registers for list manipulation
    bool disc_break;      // was the current break at a discretionary node?
    bool post_disc_break; // and did it have a nonempty post-break part?
    scaled cur_width;     // width of line number |cur_line|
    scaled cur_indent;    // left margin of line number |cur_line|
    quarterword t;        // used for replacement counts in discretionary nodes
    int pen;              // use when calculating penalties between lines
    halfword cur_line;    // the current line number being justified
    
    // ~~~ Reverse the links of the relevant passive nodes, setting |cur_p| to the first breakpoint, 878 ~~~
    q = break_node(best_bet);
    cur_p = null;
    do {
        r = q;
        q = prev_break(q);
        next_break(r) = cur_p;
        cur_p = r;
    } while (q != null);
    // ~~~ End section 878 ~~~
    cur_line = prev_graf + 1;
    do {
        // ~~~ Justify the line ending at breakpoint |cur_p|, and append it to the current vertical list, together with associated penalties and other insertions, 880 ~~~
        // ~~~ Modify the end of the line to reflect the nature of the break and to include \rightskip; also set the proper value of |disc_break|, 881 ~~~
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
                    // ~~~ Change discretionary to compulsory and set |disc_break = true|, 882 ~~~
                    t = replace_count(q);
                    // ~~~ Destroy the |t| nodes following |q|, and make |r| point to the following node, 883 ~~~
                    if (t == 0) {
                        r = link(q);
                    }
                    else {
                        r = q;
                        while (t > 1) {
                            r = link(r);
                            decr(t);
                        }
                        s = link(r);
                        r = link(s);
                        link(s) = null;
                        flush_node_list(link(q));
                        replace_count(q) = 0;
                    }
                    // ~~~ End section 883 ~~~
                    if (post_break(q) != null) {
                        // ~~~ Transplant the post-break list, 884 ~~~
                        s = post_break(q);
                        while (link(s) != null) {
                            s = link(s);
                        }
                        link(s) = r;
                        r = post_break(q);
                        post_break(q) = null;
                        post_disc_break = true;
                        // ~~~ End section 884 ~~~
                    }
                    if (pre_break(q) != null) {
                        // ~~~ Transplant the pre-break list, 885 ~~~
                        s = pre_break(q);
                        link(q) = s;
                        while (link(s) != null) {
                            s = link(s);
                        }
                        pre_break(q) = null;
                        q = s;
                        // ~~~ End section 885 ~~~
                    }
                    link(q) = r;
                    disc_break = true;
                    // ~~~ End section 882 ~~~
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
        // ~~~ Put the \rightskip glue after node |q|, 886 ~~~
        r = new_param_glue(RIGHT_SKIP_CODE);
        link(r) = link(q);
        link(q) = r;
        q = r;
        // ~~~ End section 886 ~~~
done:
        // ~~~ End section 881 ~~~
        
        // ~~~ Put the \leftskip glue at the left and detach this line, 887 ~~~
        r = link(q);
        link(q) = null;
        q = link(TEMP_HEAD);
        link(TEMP_HEAD) = r;
        if (left_skip != ZERO_GLUE) {
            r = new_param_glue(LEFT_SKIP_CODE);
            link(r) = q;
            q = r;
        }
        // ~~~ End section 887 ~~~
        
        // ~~~ Call the packaging subroutine, setting |just_box| to the justified box, 889 ~~~
        if (cur_line > last_special_line) {
            cur_width = second_width;
            cur_indent = second_indent;
        }
        else if (par_shape_ptr == null) {
            cur_width = first_width;
            cur_indent = first_indent;
        }
        else {
            cur_width = mem[par_shape_ptr + 2*cur_line].sc;
            cur_indent = mem[par_shape_ptr + 2*cur_line - 1].sc;
        }
        adjust_tail = ADJUST_HEAD;
        just_box = hpack(q, cur_width, EXACTLY);
        shift_amount(just_box) = cur_indent;
        // ~~~ End section 889 ~~~
        
        // ~~~ Append the new box to the current vertical list, followed by the list of special nodes taken out of the box by the packager, 888 ~~~
        append_to_vlist(just_box);
        if (ADJUST_HEAD != adjust_tail) {
            link(tail) = link(ADJUST_HEAD);
            tail = adjust_tail;
        }
        adjust_tail = null;
        // ~~~ End section 888 ~~~
        
        // ~~~ Append a penalty node, if a nonzero penalty is appropriate, 890 ~~~
        if (cur_line + 1 != best_line) {
            pen = inter_line_penalty;
            if (cur_line == prev_graf + 1) {
                pen += club_penalty;
            }
            if (cur_line + 2 == best_line) {
                pen += final_widow_penalty;
            }
            if (disc_break) {
                pen += broken_penalty;
            }
            if (pen != 0) {
                r = new_penalty(pen);
                link(tail) = r;
                tail = r;
            }
        }
        // ~~~ End section 890 ~~~
        // ~~~ End section 880 ~~~
        incr(cur_line);
        cur_p = next_break(cur_p);
        if (cur_p != null && !post_disc_break) {
            // ~~~ Prune unwanted nodes at the beginning of the next line, 879 ~~~
            r = TEMP_HEAD;
            while(true) {
                q = link(r);
                if (q == cur_break(cur_p) // |cur_break(cur_p)| is the next breakpoint
                    // now |q| cannot be |null|   
                    || is_char_node(q)
                    || non_discardable(q)
                    || (type(q) == KERN_NODE && subtype(q) != EXPLICIT))
                {
                    break; // goto done1
                }    
                r = q; // now |type(q) = GLUE_NODE|, |KERN_NODE|, |MATH_NODE|, or |PENALTY_NODE|
            }
            //done1:
            if (r != TEMP_HEAD) {
                link(r) = null;
                flush_node_list(link(TEMP_HEAD));
                link(TEMP_HEAD) = q;
            }
            // ~~~ End section 879 ~~~
        }
    } while (cur_p != null);
    if (cur_line != best_line || link(TEMP_HEAD) != null) {
        confusion("line breaking");
    }
    prev_graf = best_line - 1;
}
// ~~~ End section 877 ~~~
// ~~~ End section 826 ~~~

void line_break(int final_widow_penalty) {
    // ~~~ Local variables for line breaking, 862 ~~~
    bool auto_breaking;      // is node |cur_p| outside a formula?
    pointer prev_p;          // helps to determine when glue nodes are breakpoints
    pointer q, r, s, prev_s; // miscellaneous nodes of temporary interest
    internal_font_number f;  // used when calculating character widths
    
    // ~~~ Section 893 ~~~
    small_number j; // an index into |hc| or |hu|
    unsigned char c; // character being considered for hyphenation
    // ~~~ End section 893 ~~~
    // ~~~ End section 862 ~~~
    pack_begin_line = mode_line; // this is for over/underfull box messages

    // ~~~ Get ready to start line breaking, 816 ~~~
    link(TEMP_HEAD) = link(head);
    if (is_char_node(tail)) {
        tail_append(new_penalty(INF_PENALTY));
    }
    else if (type(tail) != GLUE_NODE) {
        tail_append(new_penalty(INF_PENALTY));
    }
    else {
        type(tail) = PENALTY_NODE;
        delete_glue_ref(glue_ptr(tail));
        flush_node_list(leader_ptr(tail));
        penalty(tail) = INF_PENALTY;
    }
    link(tail) = new_param_glue(PAR_FILL_SKIP_CODE);
    init_cur_lang = prev_graf % 0x10000;
    init_l_hyf = prev_graf / 0x400000;
    init_r_hyf = (prev_graf / 0x10000) % 64;
    pop_nest();
    
    // ~~~ Section 827 ~~~
    no_shrink_error_yet = true;
    check_shrinkage(left_skip);
    check_shrinkage(right_skip);
    q = left_skip;
    r = right_skip;
    background[1] = width(q) + width(r);
    background[2] = 0;
    background[3] = 0;
    background[4] = 0;
    background[5] = 0;
    background[2 + stretch_order(q)] = stretch(q);
    background[2 + stretch_order(r)] += stretch(r);
    background[6] = shrink(q) + shrink(r);
    // ~~~ End section 827 ~~~
    
    // ~~~ Section 834 ~~~
    minimum_demerits = AWFUL_BAD;
    minimal_demerits[TIGHT_FIT] = AWFUL_BAD;
    minimal_demerits[DECENT_FIT] = AWFUL_BAD;
    minimal_demerits[LOOSE_FIT] = AWFUL_BAD;
    minimal_demerits[VERY_LOOSE_FIT] = AWFUL_BAD;
    // ~~~ End section 834 ~~~
    
    // ~~~ Section 848 ~~~
    if (par_shape_ptr == null) {
        if (hang_indent == 0) {
            last_special_line = 0;
            second_width = hsize;
            second_indent = 0;
        }
        else {
            // ~~~ Set line length parameters in preparation for hanging indentation, 849 ~~~
            last_special_line = abs(hang_after);
            if (hang_after < 0) {
                first_width = hsize - abs(hang_indent);
                if (hang_indent >= 0) {
                    first_indent = hang_indent;
                }
                else {
                    first_indent = 0;
                }
                second_width = hsize;
                second_indent = 0;
            }
            else {
                first_width = hsize;
                first_indent = 0;
                second_width = hsize - abs(hang_indent);
                if (hang_indent >= 0) {
                    second_indent = hang_indent;
                }
                else {
                    second_indent = 0;
                }
            }
            // ~~~ End section 849 ~~~
        }
    }
    else {
        last_special_line = info(par_shape_ptr) - 1;
        second_width = mem[par_shape_ptr + 2*(last_special_line + 1)].sc;
        second_indent = mem[par_shape_ptr + 2*last_special_line + 1].sc;
    }
    if (looseness == 0) {
        easy_line = last_special_line;
    }
    else {
        easy_line = MAX_HALFWORD;
    }
    // ~~~ End section 848 ~~~
    // ~~~ End section 816 ~~~

    // ~~~ Find optimal breakpoints, 863 ~~~
    threshold = pretolerance;
    if (threshold >= 0) {
#ifdef STAT
        if (tracing_paragraphs > 0) {
            begin_diagnostic();
            print_nl("@firstpass");
        } 
#endif
        second_pass = false;
        final_pass = false;
    }
    else {
        threshold = tolerance;
        second_pass = true;
        final_pass = (emergency_stretch <= 0);
     
#ifdef STAT
        if (tracing_paragraphs > 0) {
            begin_diagnostic();
        }
#endif
    }
    while(true) {
        if (threshold > INF_BAD) {
            threshold = INF_BAD;
        }
        if (second_pass) {
            // ~~~ Initialize for hyphenating a paragraph, 891 ~~~
#ifdef INIT
            if (trie_not_ready) {
                init_trie();
            }
#endif
            cur_lang = init_cur_lang;
            l_hyf = init_l_hyf;
            r_hyf = init_r_hyf;
            // ~~~ End section 891 ~~~
        }
        // ~~~ Create an active breakpoint representing the beginning of the paragraph, 864 ~~~
        q = get_node(ACTIVE_NODE_SIZE);
        type(q) = UNHYPHENATED;
        fitness(q) = DECENT_FIT;
        link(q) = LAST_ACTIVE;
        break_node(q) = null;
        line_number(q) = prev_graf + 1;
        total_demerits(q) = 0;
        link(ACTIVE) = q;
        do_all_six(store_background);
        passive = null;
        printed_node = TEMP_HEAD;
        pass_number = 0;
        font_in_short_display = NULL_FONT;
        // ~~~ End section 864 ~~~
        cur_p = link(TEMP_HEAD);
        auto_breaking = true;
        prev_p = cur_p; // glue at beginning is not a legal breakpoint
        while (cur_p != null && link(ACTIVE) != LAST_ACTIVE) {
            // ~~~ Call |try_break| if |cur_p| is a legal breakpoint; on the second pass, also try to hyphenate the next word, if |cur_p| is a glue node; then advance |cur_p| to the next node of the paragraph that could possibly be a legal breakpoint, 866 ~~~
            if (is_char_node(cur_p)) {
                // ~~~ Advance |cur_p| to the node following the present string of characters, 867 ~~~
                prev_p = cur_p;
                do {
                    f = font(cur_p);
                    act_width += char_width(f, char_info(f, character(cur_p)));
                    cur_p = link(cur_p);
                } while (is_char_node(cur_p));
                // ~~~ End section 867 ~~~
            }
            switch (type(cur_p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case RULE_NODE:
                act_width += width(cur_p);
                break;
            
            case WHATSIT_NODE:
                // ~~~ Advance past a whatsit node in the |line_break| loop, 1362 ~~~
                adv_past(cur_p);
                // ~~~ End section 1362 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ If node |cur_p| is a legal breakpoint, call |try_break|; then update the active widths by including the glue in |glue_ptr(cur_p)|, 868 ~~~
                if (auto_breaking) {
                    if (is_char_node(prev_p)
                        || precedes_break(prev_p)
                        || (type(prev_p) == KERN_NODE && subtype(prev_p) != EXPLICIT))
                    {
                        try_break(0, UNHYPHENATED);
                    }
                }
                check_shrinkage(glue_ptr(cur_p));
                q = glue_ptr(cur_p);
                act_width += width(q);
                active_width[2 + stretch_order(q)] += stretch(q);
                active_width[6] += shrink(q);
                // ~~~ End section 868 ~~~
                if (second_pass && auto_breaking) {
                    // ~~~ Try to hyphenate the following word, 894 ~~~
                    prev_s = cur_p;
                    s = link(prev_s);
                    if (s != null) {
                        // ~~~ Skip to node |ha|, or |goto done1| if no hyphenation should be attempted, 896 ~~~
                        while(true) {
                            if (is_char_node(s)) {
                                c = character(s);
                                hf = font(s);
                            }
                            else if (type(s) == LIGATURE_NODE) {
                                if (lig_ptr(s) == null) {
                                    goto continue_lbl;
                                }
                                else {
                                    q = lig_ptr(s);
                                    c = character(q);
                                    hf = font(q);
                                }
                            }
                            else if (type(s) == KERN_NODE && subtype(s) == NORMAL) {
                                goto continue_lbl;
                            }
                            else if (type(s) == WHATSIT_NODE) {
                                // ~~~ Advance past a whatsit node in the pre-hyphenation loop, 1363 ~~~
                                adv_past(s);
                                // ~~~ End section 1363 ~~~
                                goto continue_lbl;
                            }
                            else {
                                goto done1;
                            }
                            if (lc_code(c) != 0) {
                                if (lc_code(c) == c || uc_hyph > 0) {
                                    goto done2;
                                }
                                else {
                                    goto done1;
                                }
                            }
continue_lbl:
                            prev_s = s;
                            s = link(prev_s);
                        }
done2:
                        hyf_char = hyphen_char[hf];
                        if (hyf_char < 0 || hyf_char > 255) {
                            goto done1;
                        }
                        ha = prev_s;
                        // ~~~ End section 896 ~~~
                        if (l_hyf + r_hyf > 63) {
                            goto done1;
                        }
                        // ~~~ Skip to node |hb|, putting letters into |hu| and |hc|, 897 ~~~
                        hn = 0;
                        while(true) {
                            if (is_char_node(s)) {
                                if (font(s) != hf) {
                                    goto done3;
                                }
                                hyf_bchar = character(s);
                                c = hyf_bchar;
                                if (lc_code(c) == 0 || hn == 63) {
                                    goto done3;
                                }
                                hb = s;
                                incr(hn);
                                hu[hn] = c;
                                hc[hn] = lc_code(c);
                                hyf_bchar = NON_CHAR;
                            }
                            else if (type(s) == LIGATURE_NODE) {
                                // ~~~ Move the characters of a ligature node to |hu| and |hc|; but |goto done3| if they are not all letters, 898 ~~~
                                if (font(lig_char(s)) != hf) {
                                    goto done3;
                                }
                                j = hn;
                                q = lig_ptr(s);
                                if (q > null) {
                                    hyf_bchar = character(q);
                                }
                                while (q > null) {
                                    c = character(q);
                                    if (lc_code(c) == 0 || j == 63) {
                                        goto done3;
                                    }
                                    incr(j);
                                    hu[j] = c;
                                    hc[j] = lc_code(c);
                                    q = link(q);
                                }
                                hb = s;
                                hn = j;
                                if (odd(subtype(s))) {
                                    hyf_bchar = font_bchar[hf];
                                }
                                else {
                                    hyf_bchar = NON_CHAR;
                                }
                                // ~~~ End section 898 ~~~
                            }
                            else if (type(s) == KERN_NODE && subtype(s) == NORMAL) {
                                hb = s;
                                hyf_bchar = font_bchar[hf];
                            }
                            else {
                                goto done3;
                            }
                            s = link(s);
                        }
done3:
                        // ~~~ End section 897 ~~~
                        // ~~~ Check that the nodes following |hb| permit hyphenation and that at least |l_hyf + r_hyf| letters have been found, otherwise |goto done1|, 899 ~~~
                        if (hn < l_hyf + r_hyf) {
                            goto done1; // |l_hyf| and |r_hyf| are >= 1
                        }
                        while(true) {
                            if (!(is_char_node(s))) {
                                switch (type(s)) {
                                case LIGATURE_NODE:
                                    do_nothing;
                                    break;
                                
                                case KERN_NODE:
                                    if (subtype(s) != NORMAL) {
                                        goto done4;
                                    }
                                    break;
                        
                                case WHATSIT_NODE:
                                case GLUE_NODE:
                                case PENALTY_NODE:
                                case INS_NODE:
                                case ADJUST_NODE:
                                case MARK_NODE:
                                    goto done4;
                                
                                default:
                                    goto done1;
                                }
                            }
                            s = link(s);
                        }
done4:
                        // ~~~ End section 899 ~~~
                        hyphenate();
                    }
done1:
                    // ~~~ End section 894 ~~~
                }
                break;
            
            case KERN_NODE:
                if (subtype(cur_p) == EXPLICIT) {
                    kern_break;
                }
                else {
                    act_width += width(cur_p);
                }
                break;
            
            case LIGATURE_NODE:
                f = font(lig_char(cur_p));
                act_width += char_width(f, char_info(f, character(lig_char(cur_p))));
                break;
            
            case DISC_NODE:
                // ~~~ Try to break after a discretionary fragment, then |goto done5|, 869 ~~~
                s = pre_break(cur_p);
                disc_width = 0;
                if (s == null) {
                    try_break(ex_hyphen_penalty, HYPHENATED);
                }
                else {
                    do {
                        // ~~~ Add the width of node |s| to |disc_width|, 870 ~~~
                        if (is_char_node(s)) {
                            f = font(s);
                            disc_width += char_width(f, char_info(f, character(s)));
                        }
                        else {
                            switch (type(s)) {
                            case LIGATURE_NODE:
                                f = font(lig_char(s));
                                disc_width += char_width(f, char_info(f, character(lig_char(s)))); 
                                break;
                            
                            case HLIST_NODE:
                            case VLIST_NODE:
                            case RULE_NODE:
                            case KERN_NODE:
                                disc_width += width(s);
                                break;
                            
                            default:
                                confusion("disc3");
                            }
                        }
                        // ~~~ End section 870 ~~~
                        s = link(s);
                    } while (s != null);
                    act_width += disc_width;
                    try_break(hyphen_penalty, HYPHENATED);
                    act_width -= disc_width;
                }
                r = replace_count(cur_p);
                s = link(cur_p);
                while (r > 0) {
                    // ~~~ Add the width of node |s| to |act_width|, 871 ~~~
                    if (is_char_node(s)) {
                        f = font(s);
                        act_width += char_width(f, char_info(f, character(s)));
                    }
                    else {
                        switch (type(s)) {
                        case LIGATURE_NODE:
                            f = font(lig_char(s));
                            act_width += char_width(f, char_info(f, character(lig_char(s))));
                            break;
                        
                        case HLIST_NODE:
                        case VLIST_NODE:
                        case RULE_NODE:
                        case KERN_NODE:
                            act_width += width(s);
                            break;
                        
                        default:
                            confusion("disc4");
                        }
                    }
                    // ~~~ End section 871 ~~~
                    decr(r);
                    s = link(s);
                }
                prev_p = cur_p;
                cur_p = s;
                goto done5;
                // ~~~ End section 869 ~~~
            
            case MATH_NODE:
                auto_breaking = (subtype(cur_p) == AFTER);
                kern_break;
                break;
            
            case PENALTY_NODE:
                try_break(penalty(cur_p), UNHYPHENATED);
                break;
            
            case MARK_NODE:
            case INS_NODE:
            case ADJUST_NODE:
                do_nothing;
                break;
            
            default:
                confusion("paragraph");
            }
            prev_p = cur_p;
            cur_p = link(cur_p);
done5:
            // ~~~ End section 866 ~~~
        }
        if (cur_p == null) {
            // ~~~ Try the final line break at the end of the paragraph, and |goto done| if the desired breakpoints have been found, 873 ~~~
            try_break(EJECT_PENALTY, HYPHENATED);
            if (link(ACTIVE) != LAST_ACTIVE) {
                // ~~~ Find an active node with fewest demerits, 874 ~~~
                r = link(ACTIVE);
                fewest_demerits = AWFUL_BAD;
                do {
                    if (type(r) != DELTA_NODE && total_demerits(r) < fewest_demerits) {
                        fewest_demerits = total_demerits(r);
                        best_bet = r;
                    }
                    r = link(r);
                } while (r != LAST_ACTIVE);
                best_line = line_number(best_bet);
                // ~~~ End section 874 ~~~
                if (looseness == 0) {
                    goto done;
                }
                // ~~~ Find the best active node for the desired looseness, 875 ~~~
                r = link(ACTIVE);
                actual_looseness = 0;
                do {
                    if (type(r) != DELTA_NODE) {
                        line_diff = line_number(r) - best_line;
                        if ((line_diff < actual_looseness && looseness <= line_diff)
                            || (line_diff > actual_looseness && looseness >= line_diff))
                        {
                            best_bet = r;
                            actual_looseness = line_diff;
                            fewest_demerits = total_demerits(r);
                        }
                        else if (line_diff == actual_looseness && total_demerits(r) < fewest_demerits) {
                            best_bet = r;
                            fewest_demerits = total_demerits(r);
                        }
                    }
                    r = link(r);
                } while (r != LAST_ACTIVE);
                best_line = line_number(best_bet);
                // ~~~ End section 875 ~~~
                if (actual_looseness == looseness || final_pass) {
                    goto done;
                }
            }
            // ~~~ End section 873 ~~~
        }
        // ~~~ Clean up the memory by removing the break nodes, 865 ~~~
        q = link(ACTIVE);
        while (q != LAST_ACTIVE) {
            cur_p = link(q);
            if (type(q) == DELTA_NODE) {
                free_node(q, DELTA_NODE_SIZE);
            }
            else {
                free_node(q, ACTIVE_NODE_SIZE);
            }
            q = cur_p;
        }
        q = passive;
        while (q != null) {
            cur_p = link(q);
            free_node(q, PASSIVE_NODE_SIZE);
            q = cur_p;
        }
        // ~~~ End section 865 ~~~
        if (!second_pass) {
#ifdef STAT
            if (tracing_paragraphs > 0) {
                print_nl("@secondpass");
            }
#endif
            threshold = tolerance;
            second_pass = true;
            final_pass = (emergency_stretch <= 0);
        } // if at first you don't succeed, \dots
        else {
#ifdef STAT
            if (tracing_paragraphs > 0) {
                print_nl("@emergencypass");
            }
#endif
            background[2] += emergency_stretch;
            final_pass = true;
        }
    }
done:
#ifdef STAT
    if (tracing_paragraphs > 0) {
        end_diagnostic(true);
        normalize_selector();
    }
#endif
    // ~~~ End section 863 ~~~
    
    // ~~~ Break the paragraph at the chosen breakpoints, justify the resulting lines to the correct widths, and append them to the current vertical list, 876 ~~~
    post_line_break(final_widow_penalty);
    // ~~~ End section 876 ~~~
    
    // ~~~ Clean up the memory by removing the break nodes, 865 ~~~
    q = link(ACTIVE);
    while (q != LAST_ACTIVE) {
        cur_p = link(q);
        if (type(q) == DELTA_NODE) {
            free_node(q, DELTA_NODE_SIZE);
        }
        else {
            free_node(q, ACTIVE_NODE_SIZE);
        }
        q = cur_p;
    }
    q = passive;
    while (q != null) {
        cur_p = link(q);
        free_node(q, PASSIVE_NODE_SIZE);
        q = cur_p;
    }
    // ~~~ End section 865 ~~~
    pack_begin_line = 0;
}
// ~~~ End section 815 ~~~
