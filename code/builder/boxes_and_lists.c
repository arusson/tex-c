// ~~~ Section 1060 ~~~
// ~~~ Start file |boxes_and_lists.c|, 1382 ~~~
#include <math.h>
#include "texerror.h"
#include "builder.h"
#include "parser.h"
#include "texmath.h"
#include "font_metric.h"
#include "alignment.h"
#include "dvi.h"
#include "breaker.h"
// ~~~ End section 1382 ~~~

void append_glue() {
    small_number s; // modifier of skip command
    s = cur_chr;
    switch (s) {
    case FIL_CODE:
        cur_val = FIL_GLUE;
        break;
    
    case FILL_CODE:
        cur_val = FILL_GLUE;
        break;
    
    case SS_CODE:
        cur_val = SS_GLUE;
        break;
    
    case FIL_NEG_CODE:
        cur_val = FIL_NEG_GLUE;
        break;
    
    case SKIP_CODE:
        scan_glue(GLUE_VAL);
        break;
    
    case MSKIP_CODE:
        scan_glue(MU_VAL);
    } // now |cur_val| points to the glue specification
    tail_append(new_glue(cur_val));
    if (s >= SKIP_CODE) {
        decr(glue_ref_count(cur_val));
        if (s > SKIP_CODE) {
            subtype(tail) = MU_GLUE;
        }
    }
}
// ~~~ End section 1060 ~~~

// ~~~ Section 1061 ~~~
void append_kern() {
    quarterword s; // |subtype| of the kern node
    s = cur_chr;
    scan_dimen(s == MU_GLUE, false, false);
    tail_append(new_kern(cur_val));
    subtype(tail) = s;
}
// ~~~ End section 1061 ~~~

// ~~~ Section 1064 ~~~
void off_save() {
    pointer p; // inserted token
    if (cur_group == BOTTOM_LEVEL) {
        // ~~~ Drop current token and complain that it was unmatched, 1066 ~~~
        print_err("Extra ");
        print_cmd_chr(cur_cmd, cur_chr);
        help1("Things are pretty mixed up, but I think the worst is over.");
        error();
        // ~~~ End section 1066 ~~~
    }
    else {
        back_input();
        p = get_avail();
        link(TEMP_HEAD) = p;
        print_err("Missing ");
        // ~~~ Prepare to insert a token that matches |cur_group|, and print what it is, 1065 ~~~
        switch (cur_group) {
        case SEMI_SIMPLE_GROUP:
            info(p) = CS_TOKEN_FLAG + FROZEN_END_GROUP;
            print_esc("endgroup"); 
            break;
        
        case MATH_SHIFT_GROUP:
            info(p) = MATH_SHIFT_TOKEN + '$';
            print_char('$');
            break;
        
        case MATH_LEFT_GROUP:
            info(p) = CS_TOKEN_FLAG + FROZEN_RIGHT;
            link(p) = get_avail();
            p = link(p);
            info(p) = OTHER_TOKEN + '.';
            print_esc("right.");
            break;
        
        default:
            info(p) = RIGHT_BRACE_TOKEN + '}';
            print_char('}');
        }
        // ~~~ End section 1065 ~~~
        print(" inserted");
        ins_list(link(TEMP_HEAD));
        help5("I've inserted something that you may have forgotten.")
            ("(See the <inserted text> above.)")
            ("With luck, this will get me unwedged. But if you")
            ("really didn't forget anything, try typing `2' now; then")
            ("my insertion and my current dilemma will both disappear.");
        error();
    }
}
// ~~~ End section 1064 ~~~

// ~~~ Section 1068 ~~~
void handle_right_brace() {
    pointer p, q; // for short - term use
    scaled d;     // holds |split_max_depth| in |insert_group|
    int f;        // holds |floating_penalty| in |insert_group|
    switch (cur_group) {
    case SIMPLE_GROUP:
        unsave();
        break;
    
    case BOTTOM_LEVEL:
        print_err("Too many }'s");
        help2("You've closed more groups than you opened.")
            ("Such booboos are generally harmless, so keep going.");
        error();
        break;
    
    case SEMI_SIMPLE_GROUP:
    case MATH_SHIFT_GROUP:
    case MATH_LEFT_GROUP:
        extra_right_brace();
        break;
    
    // ~~~ Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action, 1085 ~~~
    case HBOX_GROUP:
        package(0);
        break;
    
    case ADJUSTED_HBOX_GROUP:
        adjust_tail = ADJUST_HEAD;
        package(0);
        break;
    
    case VBOX_GROUP:
        end_graf();
        package(0);
        break;
    
    case VTOP_GROUP:
        end_graf();
        package(VTOP_CODE);
        break;
    
    // ~~~ Section 1100 ~~~
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
        // ~~~ Resume the page builder after an output routine has come to an end, 1026 ~~~
        if (loc != null
            || (token_type != OUTPUT_TEXT && token_type != BACKED_UP))
        {
            // ~~~ Recover from an unbalanced output routine, 1027 ~~~
            print_err("Unbalanced output routine");
            help2("Your sneaky output routine has problematic {'s and/or }'s.")
                ("I can't handle that very well; good luck.");
            error();
            do {
                get_token();
            } while (loc != null);
            // loops forever if reading from a file, since |null = MIN_HALFWORD <= 0|
            // ~~~ End section 1027 ~~~
        }
        end_token_list(); // conserve stack space in case more outputs are triggered
        end_graf();
        unsave();
        output_active = false;
        insert_penalties = 0;
        // ~~~ Ensure that box 255 is empty after output, 1028 ~~~
        if (box(255) != null) {
            print_err("Output routine didn't use all of ");
            print_esc("box");
            print_int(255);
            help3("Your \\output commands should empty \\box255,")
                ("e.g., by saying `\\shipout\\box255'.")
                ("Proceed; I'll discard its present contents.");
            box_error(255);
        }
        // ~~~ End section 1028 ~~~
        if (tail != head) {
            // current list goes after heldover insertions
            link(page_tail) = link(head);
            page_tail = tail;
        }
        if (link(PAGE_HEAD) != null) {
            // and both go before heldover contributions
            if (link(CONTRIB_HEAD) == null) {
                contrib_tail = page_tail;
            }
            link(page_tail) = link(CONTRIB_HEAD);
            link(CONTRIB_HEAD) = link(PAGE_HEAD);
            link(PAGE_HEAD) = null;
            page_tail = PAGE_HEAD;
        }
        pop_nest();
        build_page();
        // ~~~ End section 1026 ~~~
        break;
    // ~~~ End section 1100 ~~~
    
    // ~~~ Section 1118 ~~~
    case DISC_GROUP:
        build_discretionary();
        break;
    // ~~~ End section 1118 ~~~
    
    // ~~~ Section 1132 ~~~
    case ALIGN_GROUP:
        back_input();
        cur_tok = CS_TOKEN_FLAG + FROZEN_CR;
        print_err("Missing ");
        print_esc("cr");
        print(" inserted");
        help1("I'm guessing that you meant to end an alignment here.");
        ins_error();
        break;
    // ~~~ End section 1132 ~~~
    
    // ~~~ Section 1133 ~~~
    case NO_ALIGN_GROUP:
        end_graf();
        unsave();
        align_peek();
        break;
    // ~~~ End section 1133 ~~~
    
    // ~~~ Section 1168 ~~~
    case VCENTER_GROUP:
        end_graf();
        unsave();
        save_ptr -= 2;
        p = vpack(link(head), saved(1), saved(0));
        pop_nest();
        tail_append(new_noad());
        type(tail) = VCENTER_NOAD;
        math_type(nucleus(tail)) = SUB_BOX;
        info(nucleus(tail)) = p;
        break;
    // ~~~ End section 1168 ~~~
    
    // ~~~ Section 1173 ~~~
    case MATH_CHOICE_GROUP:
        build_choices();
        break;
    // ~~~ End section 1173 ~~~
    
    // ~~~ Section 1186 ~~~
    case MATH_GROUP:
        unsave();
        decr(save_ptr);
        math_type(saved(0)) = SUB_MLIST;
        p = fin_mlist(null);
        info(saved(0)) = p;
        if (p != null && link(p) == null) {
            if (type(p) == ORD_NOAD) {
                if (math_type(subscr(p)) == EMPTY && math_type(supscr(p)) == EMPTY) {
                    mem[saved(0)] = mem[nucleus(p)];
                    free_node(p, NOAD_SIZE);
                }
            }
            else if (type(p) == ACCENT_NOAD
                && saved(0) == nucleus(tail)
                && type(tail) == ORD_NOAD)
            {
                // ~~~ Replace the tail of the list by |p|, 1187 ~~~
                q = head;
                while (link(q) != tail) {
                    q = link(q);
                }
                link(q) = p;
                free_node(tail, NOAD_SIZE);
                tail = p;
                // ~~~ End section 1187 ~~~
            }
        }
        break;
    // ~~~ End section 1186 ~~~
    // ~~~ End section 1085 ~~~

    default:
        confusion("rightbrace");
    }
}
// ~~~ End section 1068 ~~~

// ~~~ Section 1070 ~~~
void normal_paragraph() {
    if (looseness != 0) {
        eq_word_define(INT_BASE + LOOSENESS_CODE, 0);
    }
    if (hang_indent != 0) {
        eq_word_define(DIMEN_BASE + HANG_INDENT_CODE, 0);
    }
    if (hang_after != 1) {
        eq_word_define(INT_BASE + HANG_AFTER_CODE, 1);
    }
    if (par_shape_ptr != null) {
        eq_define(PAR_SHAPE_LOC, SHAPE_REF, null);
    }
}
// ~~~ End section 1070 ~~~

// ~~~ Section 1075 ~~~
void box_end(int box_context) {
    pointer p; // |ORD_NOAD| for new box in math mode
    if (box_context < BOX_FLAG) {
        // ~~~ Append box |cur_box| to the current list, shifted by |box_context|, 1076 ~~~
        if (cur_box != null) {
            shift_amount(cur_box) = box_context;
            if (abs(mode) == VMODE) {
                append_to_vlist(cur_box);
                if (adjust_tail != null) {
                    if (ADJUST_HEAD != adjust_tail) {
                        link(tail) = link(ADJUST_HEAD);
                        tail = adjust_tail;
                    }
                    adjust_tail = null;
                }
                if (mode > 0) {
                    build_page();
                }
            }
            else {
                if (abs(mode) == HMODE) {
                    space_factor = 1000;
                }
                else {
                    p = new_noad();
                    math_type(nucleus(p)) = SUB_BOX;
                    info(nucleus(p)) = cur_box;
                    cur_box = p;
                }
                link(tail) = cur_box;
                tail = cur_box;
            }
        }
        // ~~~ End section 1076 ~~~
    }
    else if (box_context < SHIP_OUT_FLAG) {
        // ~~~ Store |cur_box| in a box register, 1077 ~~~
        if (box_context < BOX_FLAG + 256) {
            eq_define(BOX_BASE - BOX_FLAG + box_context, BOX_REF, cur_box);
        }
        else {
            geq_define(BOX_BASE - BOX_FLAG - 256 + box_context, BOX_REF, cur_box);
        }
        // ~~~ End section 1077 ~~~
    }
    else if (cur_box != null) {
        if (box_context > SHIP_OUT_FLAG) {
            // ~~~ Append a new leader node that uses |cur_box|, 1078 ~~~
            // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
            do {
                get_x_token();
            } while (cur_cmd == SPACER || cur_cmd == RELAX);
            // ~~~ End section 404 ~~~
            if ((cur_cmd == HSKIP && abs(mode) != VMODE)
                || (cur_cmd == VSKIP && abs(mode) == VMODE))
            {
                append_glue();
                subtype(tail) = box_context - (LEADER_FLAG - A_LEADERS);
                leader_ptr(tail) = cur_box;
            }
            else {
                print_err("Leaders not followed by proper glue");
                help3("You should say `\\leaders <box or rule><hskip or vskip>'.")
                    ("I found the <box or rule>, but there's no suitable")
                    ("<hskip or vskip>, so I'm ignoring these leaders.");
                back_error();
                flush_node_list(cur_box);
            }
            // ~~~ End section 1078 ~~~
        }
        else {
            ship_out(cur_box);
        }
    }
}
// ~~~ End section 1075 ~~~

// ~~~ Section 1079 ~~~
void begin_box(int box_context) {
    pointer p, q; // run through the current list
    int m;        // the length of a replacement list
    halfword k;   // 0 or |VMODE| or |HMODE|
    eight_bits n; // a box number
    
    switch (cur_chr) {
    case BOX_CODE:
        scan_eight_bit_int();
        cur_box = box(cur_val);
        box(cur_val) = null; // the box becomes void, at the same level
        break;
    
    case COPY_CODE:
        scan_eight_bit_int();
        cur_box = copy_node_list(box(cur_val));
        break;
    
    case LAST_BOX_CODE:
        // ~~~ If the current list ends with a box node, delete it from the list and make |cur_box| point to it; otherwise set |cur_box = null|, 1080 ~~~
        cur_box = null;
        if (abs(mode) == MMODE) {
            you_cant();
            help1("Sorry; this \\lastbox will be void.");
            error();
        }
        else if (mode == VMODE && head == tail) {
            you_cant();
            help2("Sorry...I usually can't take things from the current page.")
                ("This \\lastbox will therefore be void.");
            error();
        }
        else if (!is_char_node(tail)
            && (type(tail) == HLIST_NODE || type(tail) == VLIST_NODE))
        {
            // ~~~ Remove the last box, unless it's part of a discretionary, 1081 ~~~
            q = head;
            do {
                p = q;
                if (!is_char_node(q) && type(q) == DISC_NODE) {
                    for(m = 1; m <= replace_count(q); m++) {
                        p = link(p);
                    }
                    if (p == tail) {
                        goto done;
                    }
                }
                q = link(p);
            } while (q != tail);
            cur_box = tail;
            shift_amount(cur_box) = 0;
            tail = p;
            link(p) = null;
done:
            // ~~~ End section 1081 ~~~
        }
        // ~~~ End section 1080 ~~~
        break;
    
    case VSPLIT_CODE:
        // ~~~ Split off part of a vertical box, make |cur_box| point to it, 1082 ~~~
        scan_eight_bit_int();
        n = cur_val;
        if (!scan_keyword("to")) {
            print_err("Missing `to' inserted");
            help2("I'm working on `\\vsplit<box number> to <dimen>';")
                ("will look for the <dimen> next.");
            error();
        }
        scan_normal_dimen;
        cur_box = vsplit(n, cur_val);
        // ~~~ End section 1082 ~~~
        break;
    
    default:
        // ~~~ Initiate the construction of an hbox or vbox, then |return|, 1083 ~~~
        k = cur_chr - VTOP_CODE;
        saved(0) = box_context;
        if (k == HMODE) {
            if (box_context < BOX_FLAG && abs(mode) == VMODE) {
                scan_spec(ADJUSTED_HBOX_GROUP, true);
            }
            else {
                scan_spec(HBOX_GROUP, true);
            }
        }
        else {
            if (k == VMODE) {
                scan_spec(VBOX_GROUP, true);
            }
            else {
                scan_spec(VTOP_GROUP, true);
                k = VMODE;
            }
            normal_paragraph();
        }
        push_nest();
        mode = -k;
        if (k == VMODE) {
            prev_depth = IGNORE_DEPTH;
            if (every_vbox != null) {
                begin_token_list(every_vbox, EVERY_VBOX_TEXT);
            }
        }
        else {
            space_factor = 1000;
            if (every_hbox != null) {
                begin_token_list(every_hbox, EVERY_HBOX_TEXT);
            }
        }
        return;
        // ~~~ End section 1083 ~~~
    }
    box_end(box_context); // in simple cases, we use the box immediately
}
// ~~~ End section 1079 ~~~

// ~~~ Section 1084 ~~~
// the next input should specify a box or perhaps a rule
void scan_box(int box_context) {
    // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER || cur_cmd == RELAX);
    // ~~~ End section 404 ~~~
    if (cur_cmd == MAKE_BOX) {
        begin_box(box_context);
    }
    else if (box_context >= LEADER_FLAG
        && (cur_cmd == HRULE || cur_cmd == VRULE))
    {
        cur_box = scan_rule_spec();
        box_end(box_context);
    }
    else {
        print_err("A <box> was supposed to be here");
        help3("I was expecting to see \\hbox or \\vbox or \\copy or \\box or")
            ("something like that. So you might find something missing in")
            ("your output. But keep trying; you can fix this later.");
        back_error();
    }
}
// ~~~ End section 1084 ~~~

// ~~~ Section 1086 ~~~
void package(small_number c) {
    scaled h;  // height of box
    pointer p; // first node in a box
    scaled d;  // max depth
    d = box_max_depth;
    unsave();
    save_ptr -= 3;
    if (mode == -HMODE) {
        cur_box = hpack(link(head), saved(2), saved(1));
    }
    else {
        cur_box = vpackage(link(head), saved(2), saved(1), d);
        if (c == VTOP_CODE) {
            // ~~~ Readjust the height and depth of |cur_box|, for \vtop, 1087 ~~~
            h = 0;
            p = list_ptr(cur_box);
            if (p != null && type(p) <= RULE_NODE) {
                h = height(p);
            }
            depth(cur_box) += (-h + height(cur_box));
            height(cur_box) = h;
            // ~~~ End section 1087 ~~~
        }
    }
    pop_nest();
    box_end(saved(0));
}
// ~~~ End section 1086 ~~~

// ~~~ Section 1091 ~~~
small_number norm_min(int h) {
    if (h <= 0) {
        return 1;
    }
    if (h >= 63) {
        return 63;
    }
    return h;
}

void new_graf(bool indented) {
    prev_graf = 0;
    if (mode == VMODE || head != tail) {
        tail_append(new_param_glue(PAR_SKIP_CODE));
    }
    push_nest();
    mode = HMODE;
    space_factor = 1000;
    set_cur_lang;
    clang = cur_lang;
    prev_graf = (norm_min(left_hyphen_min)*64 + norm_min(right_hyphen_min))*0x10000 + cur_lang;
    if (indented) {
        tail = new_null_box();
        link(head) = tail;
        width(tail) = par_indent;    
    }
    if (every_par != null) {
        begin_token_list(every_par, EVERY_PAR_TEXT);
    }
    if (nest_ptr == 1) {
        build_page(); // put |par_skip| glue on current page
    }
}
// ~~~ End section 1091 ~~~

// ~~~ Section 1093 ~~~
void indent_in_hmode() {
    pointer p, q;
    if (cur_chr > 0) {
        // \indent
        p = new_null_box();
        width(p) = par_indent;
        if (abs(mode) == HMODE) {
            space_factor = 1000;
        }
        else {
            q = new_noad();
            math_type(nucleus(q)) = SUB_BOX;
            info(nucleus(q)) = p;
            p = q;
        }
        tail_append(p);
    }
}
// ~~~ End section 1093 ~~~

// ~~~ Section 1095 ~~~
void head_for_vmode() {
    if (mode < 0) {
        if (cur_cmd != HRULE) {
            off_save();
        }
        else {
            print_err("You can't use `");
            print_esc("hrule");
            print("' here except with leaders");
            help2("To put a horizontal rule in an hbox or an alignment,")
                ("you should use \\leaders or \\hrulefill (see The TeXbook).");
            error();
        }
    }
    else {
        back_input();
        cur_tok = par_token;
        back_input();
        token_type = INSERTED;
    }
}
// ~~~ End section 1095 ~~~

// ~~~ Section 1096 ~~~
void end_graf() {
    if (mode == HMODE) {
        if (head == tail) {
            pop_nest(); // null paragraphs are ignored
        }
        else {
            line_break(widow_penalty);
        }
        normal_paragraph();
        error_count = 0;
    }
}
// ~~~ End section 1096 ~~~

// ~~~ Section 1099 ~~~
void begin_insert_or_adjust() {
    if (cur_cmd == VADJUST) {
        cur_val = 255;
    }
    else {
        scan_eight_bit_int();
        if (cur_val == 255) {
            print_err("You can't ");
            print_esc("insert");
            print_int(255);
            help1("I'm changing to \\insert0; box 255 is special.");
            error();
            cur_val = 0;
        }
    }
    saved(0) = cur_val;
    incr(save_ptr);
    new_save_level(INSERT_GROUP);
    scan_left_brace();
    normal_paragraph();
    push_nest();
    mode = -VMODE;
    prev_depth = IGNORE_DEPTH;
}
// ~~~ End section 1099 ~~~

// ~~~ Section 1101 ~~~
void make_mark() {
    pointer p; // new node
    p = scan_toks(false, true);
    p = get_node(SMALL_NODE_SIZE);
    type(p) = MARK_NODE;
    subtype(p) = 0; // the |subtype| is not used
    mark_ptr(p) = def_ref;
    link(tail) = p;
    tail = p;
}
// ~~~ End section 1101 ~~~

// ~~~ Section 1103 ~~~
void append_penalty() {
    scan_int();
    tail_append(new_penalty(cur_val));
    if (mode == VMODE) {
        build_page();
    }
}
// ~~~ End section 1103 ~~~

// ~~~ Section 1105 ~~~
void delete_last() {
    pointer p, q; // run through the current list
    int m;        // the length of a replacement list
    if (mode == VMODE && tail == head) {
        // ~~~ Apologize for inability to do the operation now, unless \unskip follows non-glue, 1106 ~~~
        if (cur_chr != GLUE_NODE || last_glue != MAX_HALFWORD) {
            you_cant();
            help2("Sorry...I usually can't take things from the current page.")
                ("Try `I\\vskip-\\lastskip' instead.");
            if (cur_chr == KERN_NODE) {
                help_line[0] = "Try `I\\kern-\\lastkern' instead.";
            }
            else if (cur_chr != GLUE_NODE) {
                help_line[0] = "Perhaps you can make the output routine do it.";
            }
            error();
        }
        // ~~~ End section 1106 ~~~
    }
    else if (!is_char_node(tail) && type(tail) == cur_chr) {
        q = head;
        do {
            p = q;
            if (!is_char_node(q) && type(q) == DISC_NODE) {
                for(m = 1; m <= replace_count(q); m++) {
                    p = link(p);
                }
                if (p == tail) {
                    return;
                }
            }
            q = link(p);
        } while (q != tail);
        link(p) = null;
        flush_node_list(tail);
        tail = p;
    }
}
// ~~~ End section 1105 ~~~

// ~~~ Section 1110 ~~~
void unpackage() {
    pointer p; // the box
    int c;     // should we copy?
    c = cur_chr;
    scan_eight_bit_int();
    p = box(cur_val);
    if (p == null) {
        return;
    }
    if (abs(mode) == MMODE
        || (abs(mode) == VMODE && type(p) != VLIST_NODE)
        || (abs(mode) == HMODE && type(p) != HLIST_NODE))
    {
        print_err("Incompatible list can't be unboxed");
        help3("Sorry, Pandora. (You sneaky devil.)")
            ("I refuse to unbox an \\hbox in vertical mode or vice versa.")
            ("And I can't open any boxes in math mode.");
        error();
        return;
    }
    if (c == COPY_CODE) {
        link(tail) = copy_node_list(list_ptr(p));
    }
    else {
        link(tail) = list_ptr(p);
        box(cur_val) = null;
        free_node(p, BOX_NODE_SIZE);
    }
    while (link(tail) != null) {
        tail = link(tail);
    }
}
// ~~~ End section 1110 ~~~

// ~~~ Section 1113 ~~~
void append_italic_correction() {
    pointer p;              // |CHAR_NODE| at the tail of the current list
    internal_font_number f; // the font in the |CHAR_NODE|
    if (tail != head) {
        if (is_char_node(tail)) {
            p = tail;
        }
        else if (type(tail) == LIGATURE_NODE) {
            p = lig_char(tail);
        }
        else {
            return;
        }
        f = font(p);
        tail_append(new_kern(char_italic(f, char_info(f, character(p)))));
        subtype(tail) = EXPLICIT;
    }
}
// ~~~ End section 1113 ~~~

// ~~~ Section 1117 ~~~
void append_discretionary() {
    int c; // hyphen character
    tail_append(new_disc());
    if (cur_chr == 1) {
        c = hyphen_char[cur_font];
        if (c >= 0 && c < 256) {
            pre_break(tail) = new_character(cur_font, c);
        }
    }
    else {
        incr(save_ptr);
        saved(-1) = 0;
        new_save_level(DISC_GROUP);
        scan_left_brace();
        push_nest();
        mode = -HMODE;
        space_factor = 1000;
    }
}
// ~~~ End section 1117 ~~~

// ~~~ Section 1119 ~~~
void build_discretionary() {
    pointer p, q; // for link manipulation
    int n;        // length of discretionary list
    unsave();
    // ~~~ Prune the current list, if necessary, until it contains only |CHAR_NODE|, |KERN_NODE|, |HLIST_NODE|, |VLIST_NODE|, |RULE_NODE|, and |LIGATURE_NODE| items; set |n| to the length of the list, and set |q| to the list's tail, 1121 ~~~
    q = head;
    p = link(q);
    n = 0;
    while (p != null) {
        if (!is_char_node(p)
            && type(p) > RULE_NODE
            && type(p) != KERN_NODE
            && type(p) != LIGATURE_NODE)
        {
            print_err("Improper discretionary list");
            help1("Discretionary lists must contain only boxes and kerns.");
            error();
            begin_diagnostic();
            print_nl("The following discretionary sublist has been deleted:");
            show_box(p);
            end_diagnostic(true);
            flush_node_list(p);
            link(q) = null;
            break; // goto done
        }
        q = p;
        p = link(q);
        incr(n);
    }
    // done:
    // ~~~ End section 1121 ~~~
    p = link(head);
    pop_nest();
    switch (saved(-1)) {
    case 0:
        pre_break(tail) = p;
        break;
    
    case 1:
        post_break(tail) = p;
        break;
    
    case 2:
        // ~~~ Attach list |p| to the current list, and record its length; then finish up and |return|, 1120 ~~~
        if (n > 0 && abs(mode) == MMODE) {
            print_err("Illegal math ");
            print_esc("discretionary");
            help2("Sorry: The third part of a discretionary break must be")
                ("empty, in math formulas. I had to delete your third part.");
            flush_node_list(p);
            n = 0;
            error();
        }
        else {
            link(tail) = p;
        }
        if (n <= MAX_QUARTERWORD) {
            replace_count(tail) = n;
        }
        else {
            print_err("Discretionary list is too long");
            help2("Wow---I never thought anybody would tweak me here.")
                ("You can't seriously need such a huge discretionary list?");
            error();
        }
        if (n > 0) {
            tail = q;
        }
        decr(save_ptr);
        return;
        // ~~~ End section 1120 ~~~
    } // there are no other cases
    incr(saved(-1));
    new_save_level(DISC_GROUP);
    scan_left_brace();
    push_nest();
    mode = -HMODE;
    space_factor = 1000;
}
// ~~~ End section 1119 ~~~

// ~~~ Section 1123 ~~~
void make_accent() {
    double s, t;              // amount of slant
    pointer p, q, r;          // character, box, and kern nodes
    internal_font_number f;   // relevant font
    scaled a, h, x, w, delta; // heights and widths, as explained above
    memory_word i;            // character information
    
    scan_char_num();
    f = cur_font;
    p = new_character(f, cur_val);
    if (p != null) {
        x = x_height(f);
        s = slant(f) / 65536.0;
        a = char_width(f, char_info(f, character(p)));
        do_assignments();
        // ~~~ Create a character node |q| for the next character, but set |q = null| if problems arise, 1124 ~~~
        q = null;
        f = cur_font;
        if (cur_cmd == LETTER
            || cur_cmd == OTHER_CHAR
            || cur_cmd == CHAR_GIVEN)
        {
            q = new_character(f, cur_chr);
        }
        else if (cur_cmd == CHAR_NUM) {
            scan_char_num();
            q = new_character(f, cur_val);
        }
        else {
            back_input();
        }
        // ~~~ End section 1124 ~~~
        if (q != null) {
            // ~~~ Append the accent with appropriate kerns, then set |p = q|, 1125 ~~~
            t = slant(f) / 65536.0;
            i = char_info(f, character(q));
            w = char_width(f, i);
            h = char_height(f, height_depth(i));
            if (h != x) {
                // the accent must be shifted up or down
                p = hpack(p, NATURAL);
                shift_amount(p) = x - h;
            }
            delta = (scaled)round((w - a)/2.0 + h*t - x*s);
            r = new_kern(delta);
            subtype(r) = ACC_KERN;
            link(tail) = r;
            link(r) = p;
            tail = new_kern(-a - delta);
            subtype(tail) = ACC_KERN;
            link(p) = tail;
            p = q;
            // ~~~ End section 1125 ~~~
        }
        link(tail) = p;
        tail = p;
        space_factor = 1000;
    }
}
// ~~~ End section 1123 ~~~

// ~~~ Section 1131 ~~~
void do_endv() {
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input;
    while (input_stack[base_ptr].index_field != V_TEMPLATE
        && input_stack[base_ptr].loc_field == null
        && input_stack[base_ptr].state_field == TOKEN_LIST)
    {
        decr(base_ptr);
    }
    if (input_stack[base_ptr].index_field != V_TEMPLATE
        || input_stack[base_ptr].loc_field != null
        || input_stack[base_ptr].state_field != TOKEN_LIST)
    {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    if (cur_group == ALIGN_GROUP) {
        end_graf();
        if (fin_col()) {
            fin_row();
        }
    }
    else {
        off_save();
    }
}
// ~~~ End section 1131 ~~~
