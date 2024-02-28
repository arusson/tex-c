// ~~~ Section 704 ~~~
// ~~~ Start file |math_subroutines.c|, 1382 ~~~
#include "arithmetic.h"
#include "builder.h"
#include "font_metric.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

// construct the bar for a fraction
pointer fraction_rule(scaled t) {
    pointer p; // the new node
    p = new_rule();
    height(p) = t;
    depth(p) = 0;
    return p;
}
// ~~~ End section 704 ~~~

// ~~~ Section 705 ~~~
pointer overbar(pointer b, scaled k, scaled t) {
    pointer p, q; // nodes being constructed
    p = new_kern(k);
    link(p) = b;
    q = fraction_rule(t);
    link(q) = p;
    p = new_kern(t);
    link(p) = q;
    return vpack(p, NATURAL);
}
// ~~~ End section 705 ~~~

// ~~~ Section 706 ~~~
// ~~~ Declare subprocedures for |var_delimiter|, 709 ~~~
pointer char_box(internal_font_number f, quarterword c) {
    memory_word q;
    eight_bits hd; // |height_depth| byte
    pointer b, p;  // the new box and its character node
    q = char_info(f, c);
    hd = height_depth(q);
    b = new_null_box();
    width(b) = char_width(f, q) + char_italic(f, q);
    height(b) = char_height(f, hd);
    depth(b) = char_depth(f, hd);
    p = get_avail();
    character(p) = c;
    font(p) = f;
    list_ptr(b) = p;
    return b;
}

// ~~~ Section 711 ~~~
void stack_into_box(pointer b, internal_font_number f, quarterword c) {
    pointer p; // new node placed into |b|
    p = char_box(f, c);
    link(p) = list_ptr(b);
    list_ptr(b) = p;
    height(b) = height(p);
}
// ~~~ End section 711 ~~~

// ~~~ Section 712 ~~~
scaled height_plus_depth(internal_font_number f, quarterword c) {
    memory_word q;
    eight_bits hd; // |height_depth| byte
    q = char_info(f, c);
    hd = height_depth(q);
    return char_height(f, hd) + char_depth(f, hd);
}
// ~~~ End section 712 ~~~
// ~~~ End section 709 ~~~

pointer var_delimiter(pointer d, small_number s, scaled v) {
    pointer b;                 // the box that will be constructed
    internal_font_number f, g; // best-so-far and tentative font codes
    quarterword c, x, y;       // best-so-far and tentative character codes
    int m, n;                  // the number of extensible pieces
    scaled u;                  // height-plus-depth of a tentative character
    scaled w;                  // largest height-plus-depth so far
    memory_word q;             // character info
    eight_bits hd;             // height-depth byte
    memory_word r;             // extensible pieces
    small_number z;            // runs through font family members
    bool large_attempt;        // are we trying the "large" variant?
    
    c = 0;
    f = NULL_FONT;
    w = 0;
    large_attempt = false;
    z = small_fam(d);
    x = small_char(d);
    while(true) {
        // ~~~ Look at the variants of |(z, x)|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered, 707 ~~~
        if (z != 0 || x != MIN_QUARTERWORD) {
            z += s + 16;
            do {
                z -= 16;
                g = fam_fnt(z);
                if (g != NULL_FONT) {
                    // ~~~ Look at the list of characters starting with |x| in font |g|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered, 708 ~~~
                    y = x;
                    if (y >= font_bc[g] && y <= font_ec[g]) {
continue_lbl:
                        q = char_info(g, y);
                        if (char_exists(q)) {
                            if (char_tag(q) == EXT_TAG) {
                                f = g;
                                c = y;
                                goto found;
                            }
                            hd = height_depth(q);
                            u = char_height(g, hd) + char_depth(g, hd);
                            if (u > w) {
                                f = g;
                                c = y;
                                w = u;
                                if (u >= v) {
                                    goto found;
                                }
                            }
                            if (char_tag(q) == LIST_TAG) {
                                y = rem_byte(q);
                                goto continue_lbl;
                            }
                        }
                    }
                    // ~~~ End section 708 ~~~
                }
            } while (z >= 16);
        }
        // ~~~ End section 707 ~~~
        if (large_attempt) {
            goto found; // there were none large enough
        }
        large_attempt = true;
        z = large_fam(d);
        x = large_char(d);
    }
found:
    if (f != NULL_FONT) {
        // ~~~ Make variable |b| point to a box for |(f, c)|, 710 ~~~
        if (char_tag(q) == EXT_TAG) {
            // ~~~ Construct an extensible character in a new box |b|, using recipe |rem_byte(q)| and font |f|, 713 ~~~
            b = new_null_box();
            type(b) = VLIST_NODE;
            r = font_info[exten_base[f] + rem_byte(q)];
            // ~~~ Compute the minimum suitable height, |w|, and the corresponding number of extension steps, |n|; also set |width(b)|, 714 ~~~
            c = ext_rep(r);
            u = height_plus_depth(f, c);
            w = 0;
            q = char_info(f, c);
            width(b) = char_width(f, q) + char_italic(f, q);
            c = ext_bot(r);
            if (c != MIN_QUARTERWORD) {
                w += height_plus_depth(f, c);
            }
            c = ext_mid(r);
            if (c != MIN_QUARTERWORD) {
                w += height_plus_depth(f, c);
            }
            c = ext_top(r);
            if (c != MIN_QUARTERWORD) {
                w += height_plus_depth(f, c);
            }
            n = 0;
            if (u > 0) {
                while (w < v) {
                    w += u;
                    incr(n);
                    if (ext_mid(r) != MIN_QUARTERWORD) {
                        w += u;
                    }
                }
            }
            // ~~~ End section 714 ~~~
            c = ext_bot(r);
            if (c != MIN_QUARTERWORD) {
                stack_into_box(b, f, c);
            }
            c = ext_rep(r);
            for(m = 1; m <= n; m++) {
                stack_into_box(b, f, c);
            }
            c = ext_mid(r);
            if (c != MIN_QUARTERWORD) {
                stack_into_box(b, f, c);
                c = ext_rep(r);
                for(m = 1; m <= n; m++) {
                    stack_into_box(b, f, c);
                }
            }
            c = ext_top(r);
            if (c != MIN_QUARTERWORD) {
                stack_into_box(b, f, c);
            }
            depth(b) = w - height(b);
            // ~~~ End section 713 ~~~
        }
        else {
            b = char_box(f, c);
        }
        // ~~~ End section 710 ~~~
    }
    else {
        b = new_null_box();
        width(b) = null_delimiter_space; // use this width if no delimiter was found
    }
    shift_amount(b) = half(height(b) - depth(b)) - axis_height(s);
    return b;
}
// ~~~ End section 706 ~~~

// ~~~ Section 715 ~~~
pointer rebox(pointer b, scaled w) {
    pointer p;              // temporary register for list manipulation
    internal_font_number f; // font in a one-character box
    scaled v;               // width of a character without italic correction
    
    if (width(b) != w && list_ptr(b) != null) {
        if (type(b) == VLIST_NODE) {
            b = hpack(b, NATURAL);
        }
        p = list_ptr(b);
        if (is_char_node(p) && link(p) == null) {
            f = font(p);
            v = char_width(f, char_info(f, character(p)));
            if (v != width(b)) {
                link(p) = new_kern(width(b) - v);
            }
        }
        free_node(b, BOX_NODE_SIZE);
        b = new_glue(SS_GLUE);
        link(b) = p;
        while (link(p) != null) {
            p = link(p);
        }
        link(p) = new_glue(SS_GLUE);
        return hpack(b, w, EXACTLY);
    }
    else {
        width(b) = w;
        return b;
    }
}
// ~~~ End section 715 ~~~

// ~~~ Section 716 ~~~
pointer math_glue(pointer g, scaled m) {
    pointer p; // the new glue specification
    int n;     // integer part of |m|
    scaled f;  // fraction part of |m|
    n = x_over_n(m, 0x10000);
    f = remainder_;
    if (f < 0) {
        decr(n);
        f = f + 0x10000;
    }
    p = get_node(GLUE_SPEC_SIZE);
    width(p) = mu_mult(width(g)); // convert mu to pt
    stretch_order(p) = stretch_order(g);
    if (stretch_order(p) == NORMAL) {
        stretch(p) = mu_mult(stretch(g));
    }
    else {
        stretch(p) = stretch(g);
    }
    shrink_order(p) = shrink_order(g);
    if (shrink_order(p) == NORMAL) {
        shrink(p) = mu_mult(shrink(g));
    }
    else {
        shrink(p) = shrink(g);
    }
    return p;
}
// ~~~ End section 716 ~~~

// ~~~ Section 717 ~~~
void math_kern(pointer p, scaled m) {
    int n;    // integer part of |m|
    scaled f; // fraction part of |m|
    if (subtype(p) == MU_GLUE) {
        n = x_over_n(m, 0x10000);
        f = remainder_;
        if (f < 0) {
            decr(n);
            f += 0x10000;
        }
        width(p) = mu_mult(width(p));
        subtype(p) = EXPLICIT;
    }
}
// ~~~ End section 717 ~~~

// ~~~ Section 718 ~~~
void flush_math() {
    flush_node_list(link(head));
    flush_node_list(incompleat_noad);
    link(head) = null;
    tail = head;
    incompleat_noad = null;
}
// ~~~ End section 718 ~~~
