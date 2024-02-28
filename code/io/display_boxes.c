// ~~~ Section 174 ~~~
// ~~~ Start file |display_boxes.c|, 1382 ~~~
#include <math.h>
#include <string.h>
#include "datastructures.h"
#include "io.h"
#include "extensions.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

// prints highlights of list |p|
void short_display(int p) {
    int n; // for replacement counts
    while (p > MEM_MIN) {
        if (is_char_node(p)) {
            if (p <= mem_end) {
                if (font(p) != font_in_short_display) {
                    if (/* font(p) < FONT_BASE || */ font(p) > FONT_MAX) {
                        // Comparison with |FONT_BASE| is useless
                        // since |FONT_BASE = 0| and |font(p)| is in [0 .. 65535]
                        print_char('*');
                    }
                    else {
                        // ~~~ Print the font identifier for |font(p)|, 267 ~~~
                        print_esc_strnumber(font_id_text(font(p)));
                        // ~~~ End section 267 ~~~
                    }
                    print_char(' ');
                    font_in_short_display = font(p);
                }
                print_strnumber(character(p));
            }
        }
        else {
            // ~~~ Print a short indication of the contents of node |p|, 175 ~~~
            switch(type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case INS_NODE:
            case WHATSIT_NODE:
            case MARK_NODE:
            case ADJUST_NODE:
            case UNSET_NODE:
                print("[]");
                break;
            
            case RULE_NODE:
                print_char('|');
                break;
            
            case GLUE_NODE:
                if (glue_ptr(p) != ZERO_GLUE) {
                    print_char(' ');
                }
                break;
            
            case MATH_NODE:
                print_char('$');
                break;
            
            case LIGATURE_NODE:
                short_display(lig_ptr(p));
                break;
            
            case DISC_NODE:
                short_display(pre_break(p));
                short_display(post_break(p));
                n = replace_count(p);
                while (n > 0) {
                    if (link(p) != null) {
                        p = link(p);
                    }
                    decr(n);
                }
                break;
            
            default:
                do_nothing;
            }
            // ~~~ End section 175 ~~~
        }
        p = link(p);
    }
}
// ~~~ End section 174 ~~~

// ~~~ Section 176 ~~~
// prints |CHAR_NODE| data
void print_font_and_char(int p) {
    if (p > mem_end) {
        print_esc("CLOBBERED.");
    }
    else {
        if (/* font(p) < FONT_BASE || */ font(p) > FONT_MAX) {
            // |FONT_BASE = 0| and |font(p)| is in [0 .. 65535]
            print_char('*');
        }
        else {
            // ~~~ Print the font identifier for |font(p)|, 267 ~~~
            print_esc_strnumber(font_id_text(font(p)));
            // ~~~ End section 267 ~~~
        }
        print_char(' ');
        print_strnumber(character(p));
    }
}

// prints token list data in braces
void print_mark(int p) {
    print_char('{');
    if (p < hi_mem_min || p > mem_end) {
        print_esc("CLOBBERED.");
    }
    else {
        show_token_list(link(p), null, MAX_PRINT_LINE - 10);
    }
    print_char('}');
}

// prints dimension in rule node
void print_rule_dimen(scaled d) {
    if (is_running(d)) {
        print_char('*');
    }
    else {
        print_scaled(d);
    }
}
// ~~~ End section 176 ~~~

// ~~~ Section 177 ~~~
// prints a glue component
void print_glue(scaled d, int order, char *s) {
    print_scaled(d);
    if (order < NORMAL || order > FILLL) {
        print("foul");
    }
    else if (order > NORMAL) {
        print("fil");
        while (order > FIL) {
            print_char('l');
            decr(order);
        }
    }
    else if (strlen(s) != 0) {
        print(s);
    }
}
// ~~~ End section 177 ~~~

// ~~~ Section 178 ~~~
// prints a glue specification
void print_spec(int p, char *s) {
    if (p < MEM_MIN || p >= lo_mem_max) {
        print_char('*');
    }
    else {
        print_scaled(width(p));
        if (strlen(s) != 0) {
            print(s);
        }
        if (stretch(p) != 0) {
            print(" plus ");
            print_glue(stretch(p), stretch_order(p), s);
        }
        if (shrink(p) != 0) {
            print(" minus ");
            print_glue(shrink(p), shrink_order(p), s);
        }
    }
}
// ~~~ End section 178 ~~~

// ~~~ Section 182 ~~~
// prints a node list symbolically
void show_node_list(int p) {
    int n;    // the number of items already printed at this level
    double g; // a glue ratio, as a floating point number
    if (cur_length > depth_threshold) {
        if (p > null) {
            // indicate that there's been some truncation
            print(" []");
        }
        return;
    }
    n = 0;
    while (p > MEM_MIN) {
        // display the nesting history
        print_ln();
        print_current_string();
        if (p > mem_end) {
            // pointer out of range
            print("Bad link, display aborted.");
            return;
        }
        incr(n);
        if (n > breadth_max) {
            // time to stop
            print("etc.");
            return;
        }
        // ~~~ Display node |p|, 183 ~~~
        if (is_char_node(p)) {
            print_font_and_char(p);
        }
        else {
            switch(type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case UNSET_NODE:
                // ~~~ Display box |p|, 184 ~~~
                if (type(p) == HLIST_NODE) {
                    print_esc("h");
                }
                else if (type(p) == VLIST_NODE) {
                    print_esc("v");
                }
                else {
                    print_esc("unset");
                }
                print("box(");
                print_scaled(height(p));
                print_char('+');
                print_scaled(depth(p));
                print(")x");
                print_scaled(width(p));
                if (type(p) == UNSET_NODE) {
                    // ~~~ Display special fields of the unset node |p|, 185 ~~~
                    if (span_count(p) != MIN_QUARTERWORD) {
                        print(" (");
                        print_int(span_count(p) + 1);
                        print(" columns)");
                    }
                    if (glue_stretch(p) != 0) {
                        print(", stretch ");
                        print_glue(glue_stretch(p), glue_order(p), "");
                    }
                    if (glue_shrink(p) != 0) {
                        print(", shrink ");
                        print_glue(glue_shrink(p), glue_sign(p), "");
                    }
                    // ~~~ End section 185 ~~~
                }
                else {
                    // ~~~ Display the value of |glue_set(p)|, 186 ~~~
                    g = glue_set(p);
                    if (g != 0.0 && glue_sign(p) != NORMAL) {
                        print(", glue set ");
                        if (glue_sign(p) == SHRINKING) {
                            print("- ");
                        }
                        /* if (abs(mem[p + GLUE_OFFSET].integer) < 0x100000) {
                            print("?.?");
                        } */
                        if (abs(g) > 20000.0) {
                            if (g > 0.0) {
                                print_char('>');
                            }
                            else {
                                print("< -");
                            }
                            print_glue(20000*UNITY, glue_order(p), "");
                        }
                        else {
                            print_glue((scaled)round(UNITY*g), glue_order(p), "");
                        }
                    }
                    // ~~~ End section 186 ~~~
                    if (shift_amount(p) != 0) {
                        print(", shifted ");
                        print_scaled(shift_amount(p));
                    }
                }
                node_list_display(list_ptr(p)); // recursive call
                // ~~~ End section 184 ~~~
                break;
            
            case RULE_NODE:
                // ~~~ Display rule |p|, 187 ~~~
                print_esc("rule(");
                print_rule_dimen(height(p));
                print_char('+');
                print_rule_dimen(depth(p));
                print(")x");
                print_rule_dimen(width(p));
                // ~~~ End section 187 ~~~
                break;
            
            case INS_NODE:
                // ~~~ Display insertion |p|, 188 ~~~
                print_esc("insert");
                print_int(subtype(p));
                print(", natural size ");
                print_scaled(height(p));
                print("; split(");
                print_spec(split_top_ptr(p), "");
                print_char(',');
                print_scaled(depth(p));
                print("); float cost ");
                print_int(float_cost(p));
                node_list_display(ins_ptr(p)); // recursive call
                // ~~~ End section 188 ~~~
                break;
            
            case WHATSIT_NODE:
                // ~~~ Display the whatsit node |p|, 1356 ~~~
                switch (subtype(p)) {
                case OPEN_NODE:
                    print_write_whatsit("openout", p);
                    print_char('=');
                    print_file_name(open_name(p), open_area(p), open_ext(p));
                    break;
                
                case WRITE_NODE:
                    print_write_whatsit("write", p);
                    print_mark(write_tokens(p));
                    break;
                
                case CLOSE_NODE:
                    print_write_whatsit("closeout", p);
                    break;
                
                case SPECIAL_NODE:
                    print_esc("special");
                    print_mark(write_tokens(p));
                    break;
                
                case LANGUAGE_NODE:
                    print_esc("setlanguage");
                    print_int(what_lang(p));
                    print(" (hyphenmin ");
                    print_int(what_lhm(p));
                    print_char(',');
                    print_int(what_rhm(p));
                    print_char(')');
                    break;
                
                default:
                    print("whatsit?");
                }
                // ~~~ End section 1356 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ Display glue |p|, 189 ~~~
                if (subtype(p) >= A_LEADERS) {
                    // ~~~ Display leaders |p|, 190 ~~~
                    if (subtype(p) == C_LEADERS) {
                        print_esc("cleaders ");
                    }
                    else if (subtype(p) == X_LEADERS) {
                        print_esc("xleaders ");
                    }
                    else {
                        print_esc("leaders ");
                    }
                    print_spec(glue_ptr(p), "");
                    node_list_display(leader_ptr(p)); // recursive call
                    // ~~~ End section 190 ~~~
                }
                else {
                    print_esc("glue");
                    if (subtype(p) != NORMAL) {
                        print_char('(');
                        if (subtype(p) < COND_MATH_GLUE) {
                            print_skip_param(subtype(p) - 1);
                        }
                        else if (subtype(p) == COND_MATH_GLUE) {
                            print_esc("nonscript");
                        }
                        else {
                            print_esc("mskip");
                        }
                        print_char(')');
                    }
                
                    if (subtype(p) != COND_MATH_GLUE) {
                        print_char(' ');
                        if (subtype(p) < COND_MATH_GLUE) {
                            print_spec(glue_ptr(p), "");
                        }
                        else {
                            print_spec(glue_ptr(p), "mu");
                        }
                    }
                }
                // ~~~ End section 189 ~~~
                break;
            
            case KERN_NODE:
                // ~~~ Display kern |p|, 191 ~~~
                if (subtype(p) != MU_GLUE) {
                    print_esc("kern");
                    if (subtype(p) != NORMAL) {
                        print_char(' ');
                    }
                    print_scaled(width(p));
                    if (subtype(p) == ACC_KERN) {
                        print(" (for accent)");
                    }
                }
                else {
                    print_esc("mkern");
                    print_scaled(width(p));
                    print("mu");
                }
                // ~~~ End section 191 ~~~
                break;
            
            case MATH_NODE:
                // ~~~ Display math node |p|, 192 ~~~
                print_esc("math");
                if (subtype(p) == BEFORE) {
                    print("on");
                }
                else {
                    print("off");
                }
                if (width(p) != 0) {
                    print(", surrounded ");
                    print_scaled(width(p));
                }
                // ~~~ End section 192 ~~~
                break;
            
            case LIGATURE_NODE:
                // ~~~ Display ligature |p|, 193 ~~~
                print_font_and_char(lig_char(p));
                print(" (ligature ");
                if (subtype(p) > 1) {
                    print_char('|');
                }
                font_in_short_display = font(lig_char(p));
                short_display(lig_ptr(p));
                if (odd(subtype(p))) {
                    print_char('|');
                }
                print_char(')');
                // ~~~ End section 193 ~~~
                break;
            
            case PENALTY_NODE:
                // ~~~ Display penalty |p|, 194 ~~~
                print_esc("penalty ");
                print_int(penalty(p));
                // ~~~ End section 194 ~~~
                break;
            
            case DISC_NODE:
                // ~~~ Display discretionary |p|, 195 ~~~
                print_esc("discretionary");
                if (replace_count(p) > 0) {
                    print(" replacing ");
                    print_int(replace_count(p));
                }
                node_list_display(pre_break(p)); // recursive call
                append_char('|');
                show_node_list(post_break(p)); // recursive call
                flush_char;
                // ~~~ End section 195 ~~~
                break;
            
            case MARK_NODE:
                // ~~~ Display mark |p|, 196 ~~~
                print_esc("mark");
                print_mark(mark_ptr(p));
                // ~~~ End section 196 ~~~
                break;
            
            case ADJUST_NODE:
                // ~~~ Display adjustment |p|, 197 ~~~
                print_esc("vadjust");
                node_list_display(adjust_ptr(p)); // recursive call
                // ~~~ End section 197 ~~~
                break;
            
            // ~~~ Cases of |show_node_list| that arise in mlists only, 690 ~~~
            case STYLE_NODE:
                print_style(subtype(p));
                break;
            
            case CHOICE_NODE:
                // ~~~ Display choice node |p|, 695 ~~~
                print_esc("mathchoice");
                append_char('D');
                show_node_list(display_mlist(p));
                flush_char;
                append_char('T');
                show_node_list(text_mlist(p));
                flush_char;
                append_char('S');
                show_node_list(script_mlist(p));
                flush_char;
                append_char('s');
                show_node_list(script_script_mlist(p));
                flush_char;
                // ~~~ End section 695 ~~~
                break;
            
            case ORD_NOAD:
            case OP_NOAD:
            case BIN_NOAD:
            case REL_NOAD:
            case OPEN_NOAD:
            case CLOSE_NOAD:
            case PUNCT_NOAD:
            case INNER_NOAD:
            case RADICAL_NOAD:
            case OVER_NOAD:
            case UNDER_NOAD:
            case VCENTER_NOAD:
            case ACCENT_NOAD:
            case LEFT_NOAD:
            case RIGHT_NOAD:
                // ~~~ Display normal noad |p|, 696 ~~~
                switch (type(p)) {
                case ORD_NOAD:
                    print_esc("mathord");
                    break;
                
                case OP_NOAD:
                    print_esc("mathop");
                    break;
                
                case BIN_NOAD:
                    print_esc("mathbin");
                    break;
                
                case REL_NOAD:
                    print_esc("mathrel");
                    break;
                
                case OPEN_NOAD:
                    print_esc("mathopen");
                    break;
                
                case CLOSE_NOAD:
                    print_esc("mathclose");
                    break;
                
                case PUNCT_NOAD:
                    print_esc("mathpunct");
                    break;
                
                case INNER_NOAD:
                    print_esc("mathinner");
                    break;
                
                case OVER_NOAD:
                    print_esc("overline");
                    break;
                
                case UNDER_NOAD:
                    print_esc("underline");
                    break;
                
                case VCENTER_NOAD:
                    print_esc("vcenter");
                    break;
                
                case RADICAL_NOAD:
                    print_esc("radical");
                    print_delimiter(left_delimiter(p));
                    break;
                
                case ACCENT_NOAD:
                    print_esc("accent");
                    print_fam_and_char(accent_chr(p));
                    break;
                
                case LEFT_NOAD:
                    print_esc("left");
                    print_delimiter(delimiter(p));
                    break;
                
                case RIGHT_NOAD:
                    print_esc("right");
                    print_delimiter(delimiter(p));
                }
                if (subtype(p) != NORMAL) {
                    if (subtype(p) == LIMITS) {
                        print_esc("limits");
                    }
                    else {
                        print_esc("nolimits");
                    }
                }
                if (type(p) < LEFT_NOAD) {
                    print_subsidiary_data(nucleus(p), '.');
                }
                print_subsidiary_data(supscr(p), '^');
                print_subsidiary_data(subscr(p), '_');
                // ~~~ End section 696 ~~~
                break;
            
            case FRACTION_NOAD:
                // ~~~ Display fraction noad |p|, 697 ~~~
                print_esc("fraction, thickness ");
                if (thickness(p) == DEFAULT_CODE) {
                    print("= default");
                }
                else {
                    print_scaled(thickness(p));
                }
                if (small_fam(left_delimiter(p)) != 0
                    || small_char(left_delimiter(p)) != MIN_QUARTERWORD
                    || large_fam(left_delimiter(p)) != 0
                    || large_char(left_delimiter(p)) != MIN_QUARTERWORD)
                {
                    print(", left-delimiter ");
                    print_delimiter(left_delimiter(p));
                }
                if (small_fam(right_delimiter(p)) != 0
                    || small_char(right_delimiter(p)) != MIN_QUARTERWORD
                    || large_fam(right_delimiter(p)) != 0
                    || large_char(right_delimiter(p)) != MIN_QUARTERWORD)
                {
                    print(", right-delimiter ");
                    print_delimiter(right_delimiter(p));
                }
                print_subsidiary_data(numerator(p), '\\');
                print_subsidiary_data(denominator(p), '/');
                // ~~~ End section 697 ~~~
                break;
            // ~~~ End section 690 ~~~
        
            default:
                print("Unknown node type!");
            }
        }
        // ~~~ End section 183 ~~~
        p = link(p);
    }
}
// ~~~ End section 182 ~~~

// ~~~ Section 198 ~~~
void show_box(pointer p) {
    // ~~~ Assign the values |depth_threshold = show_box_depth| and |breadth_max = show_box_breadth|, 236 ~~~
    depth_threshold = show_box_depth;
    breadth_max = show_box_breadth;
    // ~~~ End section 236 ~~~
    if (breadth_max <= 0) {
        breadth_max = 5;
    }
    if (pool_ptr + depth_threshold >= POOL_SIZE) {
        depth_threshold = POOL_SIZE - pool_ptr - 1;
    } // now there's enough room for prefix string
    show_node_list(p); // the show starts at |p|
    print_ln();
}
// ~~~ End section 198 ~~~
