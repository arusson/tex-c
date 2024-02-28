// ~~~ Section 649 ~~~
// ~~~ Start file |packaging.c|, 1382 ~~~
#include "builder.h"
#include "font_metric.h"
#include "arithmetic.h"
// ~~~ End section 1382 ~~~

pointer hpack(pointer p, scaled w, small_number m) {
    pointer r;              // the box node that will be returned
    pointer q;              // trails behind |p|
    scaled h, d, x;         // height, depth, and natural width
    scaled s;               // shift amount
    pointer g;              // points to a glue specification
    int o;                  // order of infinity
    internal_font_number f; // the font in a |CHAR_NODE|
    memory_word i;          // font information about a |CHAR_NODE|
    eight_bits hd;          // height and depth indices for a character
    
    last_badness = 0;
    r = get_node(BOX_NODE_SIZE);
    type(r) = HLIST_NODE;
    subtype(r) = MIN_QUARTERWORD;
    shift_amount(r) = 0;
    q = r + LIST_OFFSET;
    link(q) = p;
    h = 0;
    // ~~~ Clear dimensions to zero, 650 ~~~
    d = 0;
    x = 0;
    total_stretch[NORMAL] = 0;
    total_shrink[NORMAL] = 0;
    total_stretch[FIL] = 0;
    total_shrink[FIL] = 0;
    total_stretch[FILL] = 0;
    total_shrink[FILL] = 0;
    total_stretch[FILLL] = 0;
    total_shrink[FILLL] = 0;
    // ~~~ End section 650 ~~~
    while (p != null) {
        // ~~~ Examine node |p| in the hlist, taking account of its effect on the dimensions of the new box, or moving it to the adjustment list; then advance |p| to the next node, 651 ~~~
reswitch:
        while (is_char_node(p)) {
            // ~~~ Incorporate character dimensions into the dimensions of the hbox that will contain it, then move to the next node, 654 ~~~
            f = font(p);
            i = char_info(f, character(p));
            hd = height_depth(i);
            x += char_width(f, i);
            s = char_height(f, hd);
            if (s > h) {
                h = s;
            }
            s = char_depth(f, hd);
            if (s > d) {
                d = s;
            }
            p = link(p);
            // ~~~ End section 654 ~~~
        }
        if (p != null) {
            switch (type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case RULE_NODE:
            case UNSET_NODE:
                // ~~~ Incorporate box dimensions into the dimensions of the hbox that will contain it, 653 ~~~
                x += width(p);
                if (type(p) >= RULE_NODE) {
                    s = 0;
                }
                else {
                    s = shift_amount(p);
                }
                if (height(p) - s > h) {
                    h = height(p) - s;
                }
                if (depth(p) + s > d) {
                    d = depth(p) + s;
                }
                // ~~~ End section 653 ~~~
                break;
            
            case INS_NODE:
            case MARK_NODE:
            case ADJUST_NODE:
                if (adjust_tail != null) {
                    // ~~~ Transfer node |p| to the adjustment list, 655 ~~~
                    while (link(q) != p) {
                        q = link(q);
                    }
                    if (type(p) == ADJUST_NODE) {
                        link(adjust_tail) = adjust_ptr(p);
                        while (link(adjust_tail) != null) {
                            adjust_tail = link(adjust_tail);
                        }
                        p = link(p);
                        free_node(link(q), SMALL_NODE_SIZE);
                    }
                    else {
                        link(adjust_tail) = p;
                        adjust_tail = p;
                        p = link(p);
                    }
                    link(q) = p;
                    p = q;
                    // ~~~ End section 655 ~~~
                }
                break;
            
            case WHATSIT_NODE:
                // ~~~ Incorporate a whatsit node into an hbox, 1360 ~~~
                do_nothing;
                // ~~~ End section 1360 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ Incorporate glue into the horizontal totals, 656 ~~~
                g = glue_ptr(p);
                x += width(g);
                o = stretch_order(g);
                total_stretch[o] += stretch(g);
                o = shrink_order(g);
                total_shrink[o] += shrink(g);
                if (subtype(p) >= A_LEADERS) {
                    g = leader_ptr(p);
                    if (height(g) > h) {
                        h = height(g);
                    }
                    if (depth(g) > d) {
                        d = depth(g);
                    }
                }
                // ~~~ End section 656 ~~~
                break;
            
            case KERN_NODE:
            case MATH_NODE:
                x += width(p);
                break;
            
            case LIGATURE_NODE:
                // ~~~ Make node |p| look like a |CHAR_NODE| and |goto reswitch|, 652 ~~~
                mem[LIG_TRICK] = mem[lig_char(p)];
                link(LIG_TRICK) = link(p);
                p = LIG_TRICK;
                goto reswitch;
                // ~~~ End section 652 ~~~
            
            default:
                do_nothing;
            }
            p = link(p);
        }
        // ~~~ End section 651 ~~~
    }
    if (adjust_tail != null) {
        link(adjust_tail) = null;
    }
    height(r) = h;
    depth(r) = d;
    // ~~~ Determine the value of |width(r)| and the appropriate glue setting; then |return| or |goto common_ending|, 657 ~~~
    if (m == ADDITIONAL) {
        w = x + w;
    }
    width(r) = w;
    x = w - x; // now |x| is the excess to be made up
    if (x == 0) {
        glue_sign(r) = NORMAL;
        glue_order(r) = NORMAL;
        set_glue_ratio_zero(glue_set(r));
        return r;
    }
    else if (x > 0) {
        // ~~~ Determine horizontal glue stretch setting, then |return| or |goto common_ending|, 658 ~~~
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
        glue_order(r) = o;
        glue_sign(r) = STRETCHING;
        if (total_stretch[o] != 0) {
            glue_set(r) = (double)x / total_stretch[o];
        }
        else {
            glue_sign(r) = NORMAL;
            set_glue_ratio_zero(glue_set(r)); // there's nothing to stretch
        }
        if (o == NORMAL && list_ptr(r) != null) {
            // ~~~ Report an underfull hbox and |goto common_ending|, if this box is sufficiently bad, 660 ~~~
            last_badness = badness(x, total_stretch[NORMAL]);
            if (last_badness > hbadness) {
                print_ln();
                if (last_badness > 100) {
                    print_nl("Underfull");
                }
                else {
                    print_nl("Loose");
                }
                print(" \\hbox (badness ");
                print_int(last_badness);
                goto common_ending;
            }
            // ~~~ End section 660 ~~~
        }
        return r;
        // ~~~ End section 658 ~~~
    }
    else {
        // ~~~ Determine horizontal glue shrink setting, then |return| or |goto common_ending|, 664 ~~~
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
        glue_order(r) = o;
        glue_sign(r) = SHRINKING;
        if (total_shrink[o] != 0) {
            glue_set(r) = (double)(-x) / total_shrink[o];
        }
        else {
            glue_sign(r) = NORMAL;
            set_glue_ratio_zero(glue_set(r)); // there's nothing to shrink
        }
        if (total_shrink[o] < -x
            && o == NORMAL
            && list_ptr(r) != null)
        {
            last_badness = 1000000;
            set_glue_ratio_one(glue_set(r)); // use the maximum shrinkage
            // ~~~ Report an overfull hbox and |goto common_ending|, if this box is sufficiently bad, 666 ~~~
            if (-x - total_shrink[NORMAL] > hfuzz || hbadness < 100) {
                if (overfull_rule > 0 && -x - total_shrink[NORMAL] > hfuzz) {
                    while (link(q) != null) {
                        q = link(q);
                    }
                    link(q) = new_rule();
                    width(link(q)) = overfull_rule;
                }
                print_ln();
                print_nl("Overfull \\hbox (");
                print_scaled(-x - total_shrink[NORMAL]);
                print("pt too wide");
                goto common_ending;
            }
            // ~~~ End section 666 ~~~
        }
        else if (o == NORMAL && list_ptr(r) != null) {
            // ~~~ Report a tight hbox and |goto common_ending|, if this box is sufficiently bad, 667 ~~~
            last_badness = badness(-x, total_shrink[NORMAL]);
            if (last_badness > hbadness) {
                print_ln();
                print_nl("Tight \\hbox (badness ");
                print_int(last_badness);
                goto common_ending;
            }
            // ~~~ End section 667 ~~~
        }
        return r;
        // ~~~ End section 664 ~~~
    }
    // ~~~ End section 657 ~~~
common_ending:
    // ~~~ Finish issuing a diagnostic message for an overfull or underfull hbox, 663 ~~~
    if (output_active) {
        print(") has occurred while \\output is active");
    }
    else {
        if (pack_begin_line != 0) {
            if (pack_begin_line > 0) {
                print(") in paragraph at lines ");
            }
            else {
                print(") in alignment at lines ");
            }
            print_int(abs(pack_begin_line));
            print("--");
        }
        else {
            print(") detected at line ");
        }
        print_int(line);
    }
    print_ln();
    font_in_short_display = NULL_FONT;
    short_display(list_ptr(r));
    print_ln();
    begin_diagnostic();
    show_box(r);
    end_diagnostic(true);
    // ~~~ End section 663 ~~~
    return r;
}
// ~~~ End section 649 ~~~

// ~~~ Section 668 ~~~
pointer vpackage(pointer p, scaled h, small_number m, scaled l) {
    pointer r;      // the box node that will be returned
    scaled w, d, x; // width, depth, and natural height
    scaled s;       // shift amount
    pointer g;      // points to a glue specification
    int o;          // order of infinity
    
    last_badness = 0;
    r = get_node(BOX_NODE_SIZE);
    type(r) = VLIST_NODE;
    subtype(r) = MIN_QUARTERWORD;
    shift_amount(r) = 0;
    list_ptr(r) = p;
    w = 0;
    // ~~~ Clear dimensions to zero, 650 ~~~
    d = 0;
    x = 0;
    total_stretch[NORMAL] = 0;
    total_shrink[NORMAL] = 0;
    total_stretch[FIL] = 0;
    total_shrink[FIL] = 0;
    total_stretch[FILL] = 0;
    total_shrink[FILL] = 0;
    total_stretch[FILLL] = 0;
    total_shrink[FILLL] = 0;
    // ~~~ End section 650 ~~~
    while (p != null) {
        // ~~~ Examine node |p| in the vlist, taking account of its effect on the dimensions of the new box; then advance |p| to the next node, 669 ~~~
        if (is_char_node(p)) {
            confusion("vpack");
        }
        else {
            switch (type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case RULE_NODE:
            case UNSET_NODE:
                // ~~~ Incorporate box dimensions into the dimensions of the vbox that will contain it, 670 ~~~
                x += d + height(p);
                d = depth(p);
                if (type(p) >= RULE_NODE) {
                    s = 0;
                }
                else {
                    s = shift_amount(p);
                }
                if (width(p) + s > w) {
                    w = width(p) + s;
                }
                // ~~~ End section 670 ~~~
                break;
            
            case WHATSIT_NODE:
                // ~~~ Incorporate a whatsit node into a vbox, 1359 ~~~
                do_nothing;
                // ~~~ End section 1359 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ Incorporate glue into the vertical totals, 671 ~~~
                x += d;
                d = 0;
                g = glue_ptr(p);
                x += width(g);
                o = stretch_order(g);
                total_stretch[o] += stretch(g);
                o = shrink_order(g);
                total_shrink[o] += shrink(g);
                if (subtype(p) >= A_LEADERS) {
                    g = leader_ptr(p);
                    if (width(g) > w) {
                        w = width(g);
                    }
                }
                // ~~~ End section 671 ~~~
                break;
            
            case KERN_NODE:
                x += d + width(p);
                d = 0;
                break;
            
            default:
                do_nothing;
            }
        }
        p = link(p);
        // ~~~ End section 669 ~~~
    }
    width(r) = w;
    if (d > l) {
        x = x + d - l;
        depth(r) = l;
    }
    else {
        depth(r) = d;
    }
    // ~~~ Determine the value of |height(r)| and the appropriate glue setting; then |return| or |goto common_ending|, 672 ~~~
    if (m == ADDITIONAL) {
        h += x;
    }
    height(r) = h;
    x = h - x; // now |x| is the excess to be made up
    if (x == 0) {
        glue_sign(r) = NORMAL;
        glue_order(r) = NORMAL;
        set_glue_ratio_zero(glue_set(r));
        return r;
    }
    else if (x > 0) {
        // ~~~ Determine vertical glue stretch setting, then |return| or |goto common_ending|, 673 ~~~
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
        glue_order(r) = o;
        glue_sign(r) = STRETCHING;
        if (total_stretch[o] != 0) {
            glue_set(r) = (double)x / total_stretch[o];
        }
        else {
            glue_sign(r) = NORMAL;
            set_glue_ratio_zero(glue_set(r)); // there's nothing to stretch
        }
        if (o == NORMAL && list_ptr(r) != null) {
            // ~~~ Report an underfull vbox and |goto common_ending|, if this box is sufficiently bad, 674 ~~~
            last_badness = badness(x, total_stretch[NORMAL]);
            if (last_badness > vbadness) {
                print_ln();
                if (last_badness > 100) {
                    print_nl("Underfull");
                }
                else {
                    print_nl("Loose");
                }
                print(" \\vbox (badness ");
                print_int(last_badness);
                goto common_ending;
            }
            // ~~~ End section 674 ~~~
        }
        return r;
        // ~~~ End section 673 ~~~
    }
    else {
        // ~~~ Determine vertical glue shrink setting, then |return| or |goto common_ending|, 676 ~~~
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
        glue_order(r) = o;
        glue_sign(r) = SHRINKING;
        if (total_shrink[o] != 0) {
            glue_set(r) = (double)(-x) / total_shrink[o];
        }
        else {
            glue_sign(r) = NORMAL;
            set_glue_ratio_zero(glue_set(r)); // there's nothing to shrink
        }
        if (total_shrink[o] < -x
            && o == NORMAL
            && list_ptr(r) != null)
        {
            last_badness = 1000000;
            set_glue_ratio_one(glue_set(r)); // use the maximum shrinkage
            // ~~~ Report an overfull vbox and |goto common_ending|, if this box is sufficiently bad, 677 ~~~
            if (-x - total_shrink[NORMAL] > vfuzz || vbadness < 100) {
                print_ln();
                print_nl("Overfull \\vbox (");
                print_scaled(-x - total_shrink[NORMAL]);
                print("pt too high");
                goto common_ending;
            }
            // ~~~ End section 677 ~~~
        }
        else if (o == NORMAL && list_ptr(r) != null) {
            // ~~~ Report a tight vbox and |goto common_ending|, if this box is sufficiently bad, 678 ~~~
            last_badness = badness(-x, total_shrink[NORMAL]);
            if (last_badness > vbadness) {
                print_ln();
                print_nl("Tight \\vbox (badness ");
                print_int(last_badness);
                goto common_ending;
            }
            // ~~~ End section 678 ~~~
        }
        return r;
        // ~~~ End section 676 ~~~
    }
    // ~~~ End section 672 ~~~

common_ending:
    // ~~~ Finish issuing a diagnostic message for an overfull or underfull vbox, 675 ~~~
    if (output_active) {
        print(") has occurred while \\output is active");
    }
    else {
        if (pack_begin_line != 0) {
            // it's actually negative
            print(") in alignment at lines ");
            print_int(abs(pack_begin_line));
            print("--");
        }
        else {
            print(") detected at line ");
        }
        print_int(line);
        print_ln();
    }
    begin_diagnostic();
    show_box(r);
    end_diagnostic(true);
    // ~~~ End section 675 ~~~
    return r;
}
// ~~~ End section 668 ~~~

// ~~~ Section 679 ~~~
void append_to_vlist(pointer b) {
    scaled d; // deficiency of space between baselines
    pointer p; // a new glue node
    if (prev_depth > IGNORE_DEPTH) {
        d = width(baseline_skip) - prev_depth - height(b);
        if (d < line_skip_limit) {
            p = new_param_glue(LINE_SKIP_CODE);
        }
        else {
            p = new_skip_param(BASELINE_SKIP_CODE);
            width(temp_ptr) = d; // |temp_ptr = glue_ptr(p)|
        }
        link(tail) = p;
        tail = p;
    }
    link(tail) = b;
    tail = b;
    prev_depth = depth(b);
}
// ~~~ End section 679 ~~~
