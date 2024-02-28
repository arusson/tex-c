// ~~~ Section 772 ~~~
// ~~~ Start file |alignment.c|, 1382 ~~~
#include <math.h>
#include "alignment.h"
#include "texerror.h"
#include "builder.h"
#include "texmath.h"
#include "parser.h"
#include "arithmetic.h"
// ~~~ End section 1382 ~~~

void push_alignment() {
    pointer p; // the new alignment stack node
    p = get_node(ALIGN_STACK_NODE_SIZE);
    link(p) = align_ptr;
    info(p) = cur_align;
    llink(p) = preamble;
    rlink(p) = cur_span;
    mem[p + 2].integer = cur_loop;
    mem[p + 3].integer = align_state;
    info(p + 4) = cur_head;
    link(p + 4) = cur_tail;
    align_ptr = p;
    cur_head = get_avail();
}

void pop_alignment() {
    pointer p; // the top alignment stack node
    free_avail(cur_head);
    p = align_ptr;
    cur_tail = link(p + 4);
    cur_head = info(p + 4);
    align_state = mem[p + 3].integer;
    cur_loop = mem[p + 2].integer;
    cur_span = rlink(p);
    preamble = llink(p);
    cur_align = info(p);
    align_ptr = link(p);
    free_node(p, ALIGN_STACK_NODE_SIZE);
}
// ~~~ End section 772 ~~~

// ~~~ Section 774 ~~~
// ~~~ Declare the procedure called |get_preamble_token|, 782 ~~~
void get_preamble_token() {
restart:
    get_token();
    while (cur_chr == SPAN_CODE && cur_cmd == TAB_MARK) {
        get_token(); // this token will be expanded once
        if (cur_cmd > MAX_COMMAND) {
            expand();
            get_token();
        }
    }
    if (cur_cmd == ENDV) {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    if (cur_cmd == ASSIGN_GLUE
        && cur_chr == GLUE_BASE + TAB_SKIP_CODE)
    {
        scan_optional_equals();
        scan_glue(GLUE_VAL);
        if (global_defs > 0) {
            geq_define(GLUE_BASE + TAB_SKIP_CODE, GLUE_REF, cur_val);
        }
        else {
            eq_define(GLUE_BASE + TAB_SKIP_CODE, GLUE_REF, cur_val);
        }
        goto restart;
    }
}
// ~~~ End section 782 ~~~

void init_align() {
    pointer save_cs_ptr; // |warning_index| value for error messages
    pointer p;           // for short-term temporary use

    save_cs_ptr = cur_cs; // \halign or \valign, usually
    push_alignment();
    align_state = -1000000; // enter a new alignment level

    // ~~~ Check for improper alignment in displayed math, 776 ~~~
    if (mode == MMODE
        && (tail != head || incompleat_noad != null))
    {
        print_err("Improper ");
        print_esc("halign");
        print(" inside $$'s");
        help3("Displays can use special alignments (like \\eqalignno)")
            ("only if nothing but the alignment itself is between $$'s.")
            ("So I've deleted the formulas that preceded this alignment.");
        error();
        flush_math();
    }
    // ~~~ End section 776 ~~~
    
    push_nest(); // enter a new semantic level
    
    // ~~~ Change current mode to |-VMODE| for \halign, |-HMODE| for \valign, 775 ~~~
    if (mode == MMODE) {
        mode = -VMODE;
        prev_depth = nest[nest_ptr - 2].aux_field.sc;
    }
    else if (mode > 0) {
        negate(mode);
    }
    // ~~~ End section 775 ~~~
    
    scan_spec(ALIGN_GROUP, false);
    
    // ~~~ Scan the preamble and record it in the |preamble| list, 777 ~~~
    preamble = null;
    cur_align = ALIGN_HEAD;
    cur_loop = null;
    scanner_status = ALIGNING;
    warning_index = save_cs_ptr;
    align_state = -1000000; // at this point, |cur_cmd = LEFT_BRACE|
    while(true) {
        // ~~~ Append the current tabskip glue to the preamble list, 778 ~~~
        link(cur_align) = new_param_glue(TAB_SKIP_CODE);
        cur_align = link(cur_align);
        // ~~~ End section 778 ~~~
        if (cur_cmd == CAR_RET) {
            break; // goto done, \cr ends the preamble
        }
        // ~~~ Scan preamble text until |cur_cmd| is |TAB_MARK| or |CAR_RET|, looking for changes in the tabskip glue; append an alignrecord to the preamble list, 779 ~~~
        // ~~~ Scan the template <u_j>, putting the resulting token list in |HOLD_HEAD|, 783 ~~~
        p = HOLD_HEAD;
        link(p) = null;
        while(true) {
            get_preamble_token();
            if (cur_cmd == MAC_PARAM) {
                break; // goto done1
            }
            if (cur_cmd <= CAR_RET
                && cur_cmd >= TAB_MARK
                && align_state == -1000000)
            {
                if (p == HOLD_HEAD
                    && cur_loop == null
                    && cur_cmd == TAB_MARK)
                {
                    cur_loop = cur_align;
                }
                else {
                    print_err("Missing # inserted in alignment preamble");
                    help3("There should be exactly one # between &'s, when an")
                        ("\\halign or \\valign is being set up. In this case you had")
                        ("none, so I've put one in; maybe that will work.");
                    back_error();
                    break; // goto done1
                }
            }
            else if (cur_cmd != SPACER || p != HOLD_HEAD) {
                link(p) = get_avail();
                p = link(p);
                info(p) = cur_tok;
            }
        }
        // done1:
        // ~~~ End section 783 ~~~
        link(cur_align) = new_null_box();
        cur_align = link(cur_align); // a new alignrecord
        info(cur_align) = END_SPAN;
        width(cur_align) = NULL_FLAG;
        u_part(cur_align) = link(HOLD_HEAD);
        // ~~~ Scan the template <v_j>, putting the resulting token list in |HOLD_HEAD|, 784 ~~~
        p = HOLD_HEAD;
        link(p) = null;
        while(true) {
            get_preamble_token();
            if (cur_cmd <= CAR_RET
                && cur_cmd >= TAB_MARK
                && align_state == -1000000)
            {
                break; // goto done2
            }
            if (cur_cmd == MAC_PARAM) {
                print_err("Only one # is allowed per tab");
                help3("There should be exactly one # between &'s, when an")
                    ("\\halign or \\valign is being set up. In this case you had")
                    ("more than one, so I'm ignoring all but the first.");
                error();
                continue;
            }
            link(p) = get_avail();
            p = link(p);
            info(p) = cur_tok;
        }
        // done2:
        link(p) = get_avail();
        p = link(p);
        info(p) = END_TEMPLATE_TOKEN; // put \endtemplate at the end
        // ~~~ End section 784 ~~~
        v_part(cur_align) = link(HOLD_HEAD);
        // ~~~ End section 779 ~~~
    }
    // done:
    scanner_status = NORMAL;
    // ~~~ End section 777 ~~~
    
    new_save_level(ALIGN_GROUP);
    if (every_cr != null) {
        begin_token_list(every_cr, EVERY_CR_TEXT);
    }
    align_peek(); // look for \noalign or \omit
}
// ~~~ End section 774 ~~~

// ~~~ Section 785 ~~~
void align_peek() {
restart:
    align_state = 1000000;
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    if (cur_cmd == NO_ALIGN) {
        scan_left_brace();
        new_save_level(NO_ALIGN_GROUP);
        if (mode == -VMODE) {
            normal_paragraph();
        }
    }
    else if (cur_cmd == RIGHT_BRACE) {
        fin_align();
    }
    else if (cur_cmd == CAR_RET && cur_chr == CR_CR_CODE) {
        goto restart; // ignore \crcr
    }
    else {
        init_row(); // start a new row
        init_col(); // start a new column and replace what we peeked at
    }
}
// ~~~ End section 785 ~~~

// ~~~ Section 786 ~~~
void init_row() {
    push_nest();
    mode = (-HMODE - VMODE) - mode;
    if (mode == -HMODE) {
        space_factor = 0;
    } 
    else {
        prev_depth = 0;
    }
    tail_append(new_glue(glue_ptr(preamble)));
    subtype(tail) = TAB_SKIP_CODE + 1;
    cur_align = link(preamble);
    cur_tail = cur_head;
    init_span(cur_align);
}
// ~~~ End section 786 ~~~

// ~~~ Section 787 ~~~
void init_span(pointer p) {
    push_nest();
    if (mode == -HMODE) {
        space_factor = 1000;
    }
    else {
        prev_depth = IGNORE_DEPTH;
        normal_paragraph();
    }
    cur_span = p;
}
// ~~~ End section 787 ~~~

// ~~~ Section 788 ~~~
void init_col() {
    extra_info(cur_align) = cur_cmd;
    if (cur_cmd == OMIT) {
        align_state = 0;
    }
    else {
        back_input();
        begin_token_list(u_part(cur_align), U_TEMPLATE);
    } // now |align_state = 1000000|
}
// ~~~ End section 788 ~~~

// ~~~ Section 791 ~~~
bool fin_col() {
    pointer p;    // the alignrecord after the current one
    pointer q, r; // temporary pointers for list manipulation
    pointer s;    // a new span node
    pointer u;    // a new unset box
    scaled w;     // natural width
    int o;        // order of infinity
    halfword n;   // span counter
    
    if (cur_align == null) {
        confusion("endv");
    }
    q = link(cur_align);
    if (q == null) {
        confusion("endv");
    }
    
    if (align_state < 500000) {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    p = link(q);
    // ~~~ If the preamble list has been traversed, check that the row has ended, 792 ~~~
    if (p == null && extra_info(cur_align) < CR_CODE) {
        if (cur_loop != null) {
            // ~~~ Lengthen the preamble periodically, 793 ~~~
            link(q) = new_null_box();
            p = link(q); // a new alignrecord
            info(p) = END_SPAN;
            width(p) = NULL_FLAG;
            cur_loop = link(cur_loop);
            // ~~~ Copy the templates from node |cur_loop| into node |p|, 794 ~~~
            q = HOLD_HEAD;
            r = u_part(cur_loop);
            while (r != null) {
                link(q) = get_avail();
                q = link(q);
                info(q) = info(r);
                r = link(r);
            }
            link(q) = null;
            u_part(p) = link(HOLD_HEAD);
            q = HOLD_HEAD;
            r = v_part(cur_loop);
            while (r != null) {
                link(q) = get_avail();
                q = link(q);
                info(q) = info(r);
                r = link(r);
            }
            link(q) = null;
            v_part(p) = link(HOLD_HEAD);
            // ~~~ End section 794 ~~~
            cur_loop = link(cur_loop);
            link(p) = new_glue(glue_ptr(cur_loop));
            subtype(link(p)) = TAB_SKIP_CODE + 1;
            // ~~~ End section 793 ~~~
        }
        else {
            print_err("Extra alignment tab has been changed to ");
            print_esc("cr");
            help3("You have given more \\span or & marks than there were")
                ("in the preamble to the \\halign or \\valign now in progress.")
                ("So I'll assume that you meant to type \\cr instead.");
            extra_info(cur_align) = CR_CODE;
            error();
        }
    }
    // ~~~ End section 792 ~~~
    if (extra_info(cur_align) != SPAN_CODE) {
        unsave();
        new_save_level(ALIGN_GROUP);
        // ~~~ Package an unset box for the current column and record its width, 796 ~~~
        if (mode == -HMODE) {
            adjust_tail = cur_tail;
            u = hpack(link(head), NATURAL);
            w = width(u);
            cur_tail = adjust_tail;
            adjust_tail = null;
        }
        else {
            u = vpackage(link(head), NATURAL, 0);
            w = height(u);
        }
        n = MIN_QUARTERWORD; // this represents a span count of 1
        if (cur_span != cur_align) {
            // ~~~ Update width entry for spanned columns, 798 ~~~
            q = cur_span;
            do {
                incr(n);
                q = link(link(q));
            } while (q != cur_align);
            if (n > MAX_QUARTERWORD) {
                confusion("256 spans"); // this can happen, but won't
            }
            q = cur_span;
            while (link(info(q)) < n) {
                q = info(q);
            }
            if (link(info(q)) > n) {
                s = get_node(SPAN_NODE_SIZE);
                info(s) = info(q);
                link(s) = n;
                info(q) = s;
                width(s) = w;
            }
            else if (width(info(q)) < w) {
                width(info(q)) = w;
            }
            // ~~~ End section 798 ~~~
        }
        else if (w > width(cur_align)) {
            width(cur_align) = w;
        }
        type(u) = UNSET_NODE;
        span_count(u) = n;
        // ~~~ Determine the stretch order, 659 ~~~
        if (total_stretch[FILLL] != 0) {
            o = FILLL;
        }
        else if (total_stretch[FILL] != 0) {
            o = FILL;
        }
        else if (total_stretch[FIL] != 0) {
            o = FIL;
        }
        else {
            o = NORMAL;
        }
        // ~~~ End section 659 ~~~
        glue_order(u) = o;
        glue_stretch(u) = total_stretch[o];
        // ~~~ Determine the shrink order, 665 ~~~
        if (total_shrink[FILLL] != 0) {
            o = FILLL;
        }
        else if (total_shrink[FILL] != 0) {
            o = FILL;
        }
        else if (total_shrink[FIL] != 0) {
            o = FIL;
        }
        else {
            o = NORMAL;
        }
        // ~~~ End section 665 ~~~
        glue_sign(u) = o;
        glue_shrink(u) = total_shrink[o];
        pop_nest();
        link(tail) = u;
        tail = u;
        // ~~~ End section 796 ~~~
        // ~~~ Copy the tabskip glue between columns, 795 ~~~
        tail_append(new_glue(glue_ptr(link(cur_align))));
        subtype(tail) = TAB_SKIP_CODE + 1;
        // ~~~ End section 795 ~~~
        if (extra_info(cur_align) >= CR_CODE) {
            return true;
        }
        init_span(p);
    }
    align_state = 1000000;
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    cur_align = p;
    init_col();
    return false;
}
// ~~~ End section 791 ~~~

// ~~~ Section 799 ~~~
void fin_row() {
    pointer p; // the new unset box
    if (mode == -HMODE) {
        p = hpack(link(head), NATURAL);
        pop_nest();
        append_to_vlist(p);
        if (cur_head != cur_tail) {
            link(tail) = link(cur_head);
            tail = cur_tail;
        }
    }
    else {
        p = vpack(link(head), NATURAL);
        pop_nest();
        link(tail) = p;
        tail = p;
        space_factor = 1000;
    }
    type(p) = UNSET_NODE;
    glue_stretch(p) = 0;
    if (every_cr != null) {
        begin_token_list(every_cr, EVERY_CR_TEXT);
    }
    align_peek();
} // note that |glue_shrink(p) = 0| since |glue_shrink = shift_amount|
// ~~~ End section 799 ~~~

// ~~~ Section 800 ~~~
void fin_align() {
    pointer p, q, r, s, u, v; // registers for the list operations
    scaled t, w;              // width of column
    scaled o;                 // shift offset for unset boxes
    halfword n;               // matching span amount
    scaled rule_save;         // temporary storage for |overfull_rule|
    memory_word aux_save;     // temporary storage for |aux|
    
    if (cur_group != ALIGN_GROUP) {
        confusion("align1");
    }
    unsave(); // that |ALIGN_GROUP| was for individual entries
    if (cur_group != ALIGN_GROUP) {
        confusion("align0");
    }
    unsave(); // that |ALIGN_GROUP| was for the whole alignment
    if (nest[nest_ptr - 1].mode_field == MMODE) {
        o = display_indent;
    }
    else {
        o = 0;
    }

    // ~~~ Go through the preamble list, determining the column widths and changing the alignrecords to dummy unset boxes, 801 ~~~
    q = link(preamble);
    do {
        flush_list(u_part(q));
        flush_list(v_part(q));
        p = link(link(q));
        if (width(q) == NULL_FLAG) {
            // ~~~ Nullify |width(q)| and the tabskip glue following this column, 802 ~~~
            width(q) = 0;
            r = link(q);
            s = glue_ptr(r);
            if (s != ZERO_GLUE) {
                add_glue_ref(ZERO_GLUE);
                delete_glue_ref(s);
                glue_ptr(r) = ZERO_GLUE;
            }
            // ~~~ End section 802 ~~~
        }
        if (info(q) != END_SPAN) {
            // ~~~ Merge the widths in the span nodes of |q| with those of |p|, destroying the span nodes of |q|, 803 ~~~
            t = width(q) + width(glue_ptr(link(q)));
            r = info(q);
            s = END_SPAN;
            info(s) = p;
            n = MIN_QUARTERWORD + 1;
            do {
                width(r) -= t;
                u = info(r);
                while (link(r) > n) {
                    s = info(s);
                    n = link(info(s)) + 1;
                }
                if (link(r) < n) {
                    info(r) = info(s);
                    info(s) = r;
                    decr(link(r));
                    s = r;
                }
                else {
                    if (width(r) > width(info(s))) {
                        width(info(s)) = width(r);
                    }
                    free_node(r, SPAN_NODE_SIZE);
                }
                r = u;
            } while (r != END_SPAN);
            // ~~~ End section 803 ~~~
        }
        type(q) = UNSET_NODE;
        span_count(q) = MIN_QUARTERWORD;
        height(q) = 0;
        depth(q) = 0;
        glue_order(q) = NORMAL;
        glue_sign(q) = NORMAL;
        glue_stretch(q) = 0;
        glue_shrink(q) = 0;
        q = p;
    } while (q != null);
    // ~~~ End section 801 ~~~

    // ~~~ Package the preamble list, to determine the actual tabskip glue amounts, and let |p| point to this prototype box, 804 ~~~
    save_ptr -= 2;
    pack_begin_line = -mode_line;
    if (mode == -VMODE) {
        rule_save = overfull_rule;
        overfull_rule = 0; // prevent rule from being packaged
        p = hpack(preamble, saved(1), saved(0));
        overfull_rule = rule_save;
    }
    else {
        q = link(preamble);
        do {
            height(q) = width(q);
            width(q) = 0;
            q = link(link(q));
        } while (q != null);
        p = vpack(preamble, saved(1), saved(0));
        q = link(preamble);
        do {
            width(q) = height(q);
            height(q) = 0;
            q = link(link(q));
        } while (q != null);
    }
    pack_begin_line = 0;
    // ~~~ End section 804 ~~~

    // ~~~ Set the glue in all the unset boxes of the current list, 805 ~~~
    q = link(head);
    s = head;
    while (q != null) {
        if (!is_char_node(q)) {
            if (type(q) == UNSET_NODE) {
                // ~~~ Set the unset box |q| and the unset boxes in it, 807 ~~~
                if (mode == -VMODE) {
                    type(q) = HLIST_NODE;
                    width(q) = width(p);
                }
                else {
                    type(q) = VLIST_NODE;
                    height(q) = height(p);
                }
                glue_order(q) = glue_order(p);
                glue_sign(q) = glue_sign(p);
                glue_set(q) = glue_set(p);
                shift_amount(q) = o;
                r = link(list_ptr(q));
                s = link(list_ptr(p));
                do {
                    // ~~~ Set the glue in node |r| and change it from an unset node, 808 ~~~
                    n = span_count(r);
                    t = width(s);
                    w = t;
                    u = HOLD_HEAD;
                    while (n > MIN_QUARTERWORD) {
                        decr(n);
                        // ~~~ Append tabskip glue and an empty box to list |u|, and update |s| and |t| as the prototype nodes are passed, 809 ~~~
                        s = link(s);
                        v = glue_ptr(s);
                        link(u) = new_glue(v);
                        u = link(u);
                        subtype(u) = TAB_SKIP_CODE + 1;
                        t += width(v);
                        if (glue_sign(p) == STRETCHING) {
                            if (stretch_order(v) == glue_order(p)) {
                                t += (scaled)round(glue_set(p)*stretch(v));
                            }
                        }
                        else if (glue_sign(p) == SHRINKING) {
                            if (shrink_order(v) == glue_order(p)) {
                                t -= (scaled)round(glue_set(p)*shrink(v));
                            }
                        }
                        s = link(s);
                        link(u) = new_null_box();
                        u = link(u);
                        t += width(s);
                        if (mode == -VMODE) {
                            width(u) = width(s);
                        }
                        else {
                            type(u) = VLIST_NODE;
                            height(u) = width(s);
                        }
                        // ~~~ End section 809 ~~~
                    }
                    if (mode == -VMODE) {
                        // ~~~ Make the unset node |r| into an |HLIST_NODE| of width |w|, setting the glue as if the width were |t|, 810 ~~~
                        height(r) = height(q);
                        depth(r) = depth(q);
                        if (t == width(r)) {
                            glue_sign(r) = NORMAL;
                            glue_order(r) = NORMAL;
                            set_glue_ratio_zero(glue_set(r));
                        }
                        else if (t > width(r)) {
                            glue_sign(r) = STRETCHING;
                            if (glue_stretch(r) == 0) {
                                set_glue_ratio_zero(glue_set(r));
                            }
                            else {
                                glue_set(r) = (double)(t - width(r)) / glue_stretch(r);
                            }
                        }
                        else {
                            glue_order(r) = glue_sign(r);
                            glue_sign(r) = SHRINKING;
                            if (glue_shrink(r) == 0) {
                                set_glue_ratio_zero(glue_set(r));
                            }
                            else if (glue_order(r) == NORMAL && width(r) - t > glue_shrink(r)) {
                                set_glue_ratio_one(glue_set(r));
                            }
                            else {
                                glue_set(r) = (double)(width(r) - t) / glue_shrink(r);
                            }    
                        }
                        width(r) = w;
                        type(r) = HLIST_NODE;
                        // ~~~ End section 810 ~~~
                    }
                    else {
                        // ~~~ Make the unset node |r| into a |VLIST_NODE| of height |w|, setting the glue as if the height were |t|, 811 ~~~
                        width(r) = width(q);
                        if (t == height(r)) {
                            glue_sign(r) = NORMAL;
                            glue_order(r) = NORMAL;
                            set_glue_ratio_zero(glue_set(r));
                        }
                        else if (t > height(r)) {
                            glue_sign(r) = STRETCHING;
                            if (glue_stretch(r) == 0) {
                                set_glue_ratio_zero(glue_set(r));
                            }
                            else {
                                glue_set(r) = (double)(t - height(r)) / glue_stretch(r);
                            }
                        }
                        else {
                            glue_order(r) = glue_sign(r);
                            glue_sign(r) = SHRINKING;
                            if (glue_shrink(r) == 0) {
                                set_glue_ratio_zero(glue_set(r));
                            }
                            else if (glue_order(r) == NORMAL && height(r) - t > glue_shrink(r)) {
                                set_glue_ratio_one(glue_set(r));
                            }
                            else {
                                glue_set(r) = (double)(height(r) - t) / glue_shrink(r);
                            }
                        }
                        height(r) = w;
                        type(r) = VLIST_NODE;
                        // ~~~ End section 811 ~~~
                    }
                    shift_amount(r) = 0;
                    if (u != HOLD_HEAD) {
                        // append blank boxes to account for spanned nodes
                        link(u) = link(r);
                        link(r) = link(HOLD_HEAD);
                        r = u;
                    }
                    // ~~~ End section 808 ~~~
                    r = link(link(r));
                    s = link(link(s));
                } while (r != null);
                // ~~~ End section 807 ~~~
            }
            else if (type(q) == RULE_NODE) {
                // ~~~ Make the running dimensions in rule |q| extend to the boundaries of the alignment, 806 ~~~
                if (is_running(width(q))) {
                    width(q) = width(p);
                }
                if (is_running(height(q))) {
                    height(q) = height(p);
                }
                if (is_running(depth(q))) {
                    depth(q) = depth(p);
                }
                if (o != 0) {
                    r = link(q);
                    link(q) = null;
                    q = hpack(q, NATURAL);
                    shift_amount(q) = o;
                    link(q) = r;
                    link(s) = q;
                }
                // ~~~ End section 806 ~~~
            }
        }
        s = q;
        q = link(q);
    }
    // ~~~ End section 805 ~~~
    
    flush_node_list(p);
    pop_alignment();
    // ~~~ Insert the current list into its environment, 812 ~~~
    aux_save = aux;
    p = link(head);
    q = tail;
    pop_nest();
    if (mode == MMODE) {
        // ~~~ Finish an alignment in a display, 1206 ~~~
        do_assignments();
        if (cur_cmd != MATH_SHIFT) {
            // ~~~ Pontificate about improper alignment in display, 1207 ~~~
            print_err("Missing $$ inserted");
            help2("Displays can use special alignments (like \\eqalignno)")
                ("only if nothing but the alignment itself is between $$'s.");
            back_error();
            // ~~~ End section 1207 ~~~
        }
        else {
            // ~~~ Check that another $ follows, 1197 ~~~
            get_x_token();
            if (cur_cmd != MATH_SHIFT) {
                print_err("Display math should end with $$");
                help2("The `$' that I just saw supposedly matches a previous `$$'.")
                    ("So I shall assume that you typed `$$' both times.");
                back_error();
            }
            // ~~~ End section 1197 ~~~
        }
        pop_nest();
        tail_append(new_penalty(pre_display_penalty));
        tail_append(new_param_glue(ABOVE_DISPLAY_SKIP_CODE));
        link(tail) = p;
        if (p != null) {
            tail = q;
        }
        tail_append(new_penalty(post_display_penalty));
        tail_append(new_param_glue(BELOW_DISPLAY_SKIP_CODE));
        prev_depth = aux_save.sc;
        resume_after_display();
        // ~~~ End section 1206 ~~~
    }
    else {
        aux = aux_save;
        link(tail) = p;
        if (p != null) {
            tail = q;
        }
        if (mode == VMODE) {
            build_page();
        }
    }
    // ~~~ End section 812 ~~~
}
// ~~~ End section 800 ~~~
