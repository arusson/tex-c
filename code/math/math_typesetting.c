// ~~~ Section 720 ~~~
// ~~~ Start file |math_typesetting.c|, 1382 ~~~
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

pointer clean_box(pointer p, small_number s) {
    pointer q;               // beginning of a list to be boxed
    small_number save_style; // |cur_style| to be restored
    pointer x;               // box to be returned
    pointer r;               // temporary pointer
    
    switch (math_type(p)) {
    case MATH_CHAR:
        cur_mlist = new_noad();
        mem[nucleus(cur_mlist)] = mem[p];
        break;
    
    case SUB_BOX:
        q = info(p);
        goto found;
    
    case SUB_MLIST:
        cur_mlist = info(p);
        break;
    
    default:
        q = new_null_box();
        goto found;
    }
    save_style = cur_style;
    cur_style = s;
    mlist_penalties = false;
    mlist_to_hlist();
    q = link(TEMP_HEAD); // recursive call
    cur_style = save_style; // restore the style
    // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
    if (cur_style < SCRIPT_STYLE) {
        cur_size = TEXT_SIZE;
    }
    else {
        cur_size = 16*((cur_style - TEXT_STYLE) / 2);
    }
    cur_mu = x_over_n(math_quad(cur_size), 18);
    // ~~~ End section 703 ~~~

found:
    if (is_char_node(q) || q == null) {
        x = hpack(q, NATURAL);
    }
    else if (link(q) == null
        && type(q) <= VLIST_NODE
        && shift_amount(q) == 0)
    {
        x = q; // it's already clean
    }
    else {
        x = hpack(q, NATURAL);
    }
    // ~~~ Simplify a trivial box, 721 ~~~
    q = list_ptr(x);
    if (is_char_node(q)) {
        r = link(q);
        if (r != null
            && link(r) == null
            && !is_char_node(r)
            && type(r) == KERN_NODE)
        {
            // unneeded italic correction
            free_node(r, SMALL_NODE_SIZE);
            link(q) = null;
        }
    }
    // ~~~ End section 721 ~~~
    return x;
}
// ~~~ End section 720 ~~~

// ~~~ Section 722 ~~~
// unpack the |MATH_CHAR| field |a|
void fetch(pointer a) {
    cur_c = character(a);
    cur_f = fam_fnt(fam(a) + cur_size);
    if (cur_f == NULL_FONT) {
        // ~~~ Complain about an undefined family and set |cur_i| null, 723 ~~~
        print_err("");
        print_size(cur_size);
        print_char(' ');
        print_int(fam(a));
        print(" is undefined (character ");
        print_strnumber(cur_c);
        print_char(')');
        help4("Somewhere in the math formula just ended, you used the")
            ("stated character from an undefined font family. For example,")
            ("plain TeX doesn't allow \\it or \\sl in subscripts. Proceed,")
            ("and I'll try to forget that I needed that character.");
        error();
        cur_i = null_character;
        math_type(a) = EMPTY;
        // ~~~ End section 723 ~~~
    }
    else {
        if (cur_c >= font_bc[cur_f] && cur_c <= font_ec[cur_f]) {
            cur_i = char_info(cur_f, cur_c);
        }
        else {
            cur_i = null_character;
        }
        if (!char_exists(cur_i)) {
            char_warning(cur_f, cur_c);
            math_type(a) = EMPTY;
            cur_i = null_character;
        }
    }
}
// ~~~ End section 722 ~~~

// ~~~ Section 726 ~~~
// ~~~ Declare math construction procedures, 734 ~~~
void make_over(pointer q) {
    info(nucleus(q)) = overbar(
        clean_box(nucleus(q), cramped_style(cur_style)),
        3*default_rule_thickness, default_rule_thickness
    );
    math_type(nucleus(q)) = SUB_BOX;
}

// ~~~ Section 735 ~~~
void make_under(pointer q) {
    pointer p, x, y; // temporary registers for box construction
    scaled delta;    // overall height plus depth
    x = clean_box(nucleus(q), cur_style);
    p = new_kern(3*default_rule_thickness);
    link(x) = p;
    link(p) = fraction_rule(default_rule_thickness);
    y = vpack(x, NATURAL);
    delta = height(y) + depth(y) + default_rule_thickness;
    height(y) = height(x);
    depth(y) = delta - height(y);
    info(nucleus(q)) = y;
    math_type(nucleus(q)) = SUB_BOX;
}
// ~~~ End section 735 ~~~

// ~~~ Section 736 ~~~
void make_vcenter(pointer q) {
    pointer v;    // the box that should be centered vertically
    scaled delta; // its height plus depth
    v = info(nucleus(q));
    if (type(v) != VLIST_NODE) {
        confusion("vcenter");
    }
    delta = height(v) + depth(v);
    height(v) = axis_height(cur_size) + half(delta);
    depth(v) = delta - height(v);
}
// ~~~ End section 736 ~~~

// ~~~ Section 737 ~~~
void make_radical(pointer q) {
    pointer x, y;      // temporary registers for box construction
    scaled delta, clr; // dimensions involved in the calculation
    x = clean_box(nucleus(q), cramped_style(cur_style));
    if (cur_style < TEXT_STYLE) {
        // display style
        clr = default_rule_thickness + abs(math_x_height(cur_size)) / 4;
    }
    else {
        clr = default_rule_thickness;
        clr += abs(clr) / 4;
    }
    y = var_delimiter(left_delimiter(q), cur_size, height(x) + depth(x) + clr + default_rule_thickness);
    delta = depth(y) - (height(x) + depth(x) + clr);
    if (delta > 0) {
        clr += half(delta); // increase the actual clearance
    }
    shift_amount(y) = -(height(x) + clr);
    link(y) = overbar(x, clr, height(y));
    info(nucleus(q)) = hpack(y, NATURAL);
    math_type(nucleus(q)) = SUB_BOX;
}
// ~~~ End section 737 ~~~

// ~~~ Section 738 ~~~
void make_math_accent(pointer q) {
    pointer p, x, y;        // temporary registers for box construction
    int a;                  // address of lig/kern instruction
    quarterword c;          // accent character
    internal_font_number f; // its font
    memory_word i;          // its |char_info|
    scaled s;               // amount to skew the accent to the right
    scaled h;               // height of character being accented
    scaled delta;           // space to remove between accent and accentee
    scaled w;               // width of the accentee, not including sub/superscripts
    
    fetch(accent_chr(q));
    if (char_exists(cur_i)) {
        i = cur_i;
        c = cur_c;
        f = cur_f;
        // ~~~ Compute the amount of skew, 741 ~~~
        s = 0;
        if (math_type(nucleus(q)) == MATH_CHAR) {
            fetch(nucleus(q));
            if (char_tag(cur_i) == LIG_TAG) {
                a = lig_kern_start(cur_f, cur_i);
                cur_i = font_info[a];
                if (skip_byte(cur_i) > STOP_FLAG) {
                    a = lig_kern_restart(cur_f, cur_i);
                    cur_i = font_info[a];
                }
                while(true) {
                    if (next_char(cur_i) == skew_char[cur_f]) {
                        if (op_byte(cur_i) >= KERN_FLAG && skip_byte(cur_i) <= STOP_FLAG) {
                            s = char_kern(cur_f, cur_i);
                        }
                        break; // goto done1
                    }
                    if (skip_byte(cur_i) >= STOP_FLAG) {
                        break; // goto done1
                    }
                    a += skip_byte(cur_i) + 1;
                    cur_i = font_info[a];
                }
            }
        }
        // done1:
        // ~~~ End section 741 ~~~
        x = clean_box(nucleus(q), cramped_style(cur_style));
        w = width(x);
        h = height(x);
        // ~~~ Switch to a larger accent if available and appropriate, 740 ~~~
        while(true) {
            if (char_tag(i) != LIST_TAG) {
                break; // goto done
            }
            y = rem_byte(i);
            i = char_info(f, y);
            if (!char_exists(i) || char_width(f, i) > w) {
                break; // goto done
            }
            c = y;
        }
        // done:
        // ~~~ End section 740 ~~~
        if (h < x_height(f)) {
            delta = h;
        }
        else {
            delta = x_height(f);
        }
        if ((math_type(supscr(q)) != EMPTY || math_type(subscr(q)) != EMPTY)
            && math_type(nucleus(q)) == MATH_CHAR)
        {
            // ~~~ Swap the subscript and superscript into box |x|, 742 ~~~
            flush_node_list(x);
            x = new_noad();
            mem[nucleus(x)] = mem[nucleus(q)];
            mem[supscr(x)] = mem[supscr(q)];
            mem[subscr(x)] = mem[subscr(q)];
            mem[supscr(q)] = empty_field;
            mem[subscr(q)] = empty_field;
            math_type(nucleus(q)) = SUB_MLIST;
            info(nucleus(q)) = x;
            x = clean_box(nucleus(q), cur_style);
            delta += height(x) - h;
            h = height(x);
            // ~~~ End section 742 ~~~
        }
        y = char_box(f, c);
        shift_amount(y) = s + half(w - width(y));
        width(y) = 0;
        p = new_kern(-delta);
        link(p) = x;
        link(y) = p;
        y = vpack(y, NATURAL);
        width(y) = width(x);
        if (height(y) < h) {
            // ~~~ Make the height of box |y| equal to |h|, 739 ~~~
            p = new_kern(h - height(y));
            link(p) = list_ptr(y);
            list_ptr(y) = p;
            height(y) = h;
            // ~~~ End section 739 ~~~
        }
        info(nucleus(q)) = y;
        math_type(nucleus(q)) = SUB_BOX;
    }
}
// ~~~ End section 738 ~~~

// ~~~ Section 743 ~~~
void make_fraction(pointer q) {
    pointer p, v, x, y, z; // temporary registers for box construction
    scaled delta, delta1, delta2, shift_up, shift_down, clr; // dimensions for box calculations
    if (thickness(q) == DEFAULT_CODE) {
        thickness(q) = default_rule_thickness;
    }

    // ~~~ Create equal-width boxes |x| and |z| for the numerator and denominator, and compute the default amounts |shift_up| and |shift_down| by which they are displaced from the baseline, 744 ~~~
    x = clean_box(numerator(q), num_style(cur_style));
    z = clean_box(denominator(q), denom_style(cur_style));
    if (width(x) < width(z)) {
        x = rebox(x, width(z));
    }
    else {
        z = rebox(z, width(x));
    }
    if (cur_style < TEXT_STYLE) {
        // display style
        shift_up = num1(cur_size);
        shift_down = denom1(cur_size);
    }
    else {
        shift_down = denom2(cur_size);
        if (thickness(q) != 0) {
            shift_up = num2(cur_size);
        }
        else {
            shift_up = num3(cur_size);
        }
    }
    // ~~~ End section 744 ~~~

    if (thickness(q) == 0) {
        // ~~~ Adjust |shift_up| and |shift_down| for the case of no fraction line, 745 ~~~
        if (cur_style < TEXT_STYLE) {
            clr = 7 * default_rule_thickness;
        }
        else {
            clr = 3 * default_rule_thickness;
        }
        delta = half(clr - ((shift_up - depth(x)) - (height(z) - shift_down)));
        if (delta > 0) {
            shift_up += delta;
            shift_down += delta;
        }
        // ~~~ End section 745 ~~~
    }
    else {
        // ~~~ Adjust |shift_up| and |shift_down| for the case of a fraction line, 746 ~~~
        if (cur_style < TEXT_STYLE) {
            clr = 3 * thickness(q);
        }
        else {
            clr = thickness(q);
        }
        delta = half(thickness(q));
        delta1 = clr - ((shift_up - depth(x)) - (axis_height(cur_size) + delta));
        delta2 = clr - ((axis_height(cur_size) - delta) - (height(z) - shift_down));
        if (delta1 > 0) {
            shift_up += delta1;
        }
        if (delta2 > 0) {
            shift_down += delta2;
        }
        // ~~~ End section 746 ~~~
    }

    // ~~~ Construct a vlist box for the fraction, according to |shift_up| and |shift_down|, 747 ~~~
    v = new_null_box();
    type(v) = VLIST_NODE;
    height(v) = shift_up + height(x);
    depth(v) = depth(z) + shift_down;
    width(v) = width(x); // this also equals |width(z)|
    if (thickness(q) == 0) {
        p = new_kern((shift_up - depth(x)) - (height(z) - shift_down));
        link(p) = z;
    }
    else {
        y = fraction_rule(thickness(q));
        p = new_kern((axis_height(cur_size) - delta) - (height(z) - shift_down));
        link(y) = p;
        link(p) = z;
        p = new_kern((shift_up - depth(x)) - (axis_height(cur_size) + delta));
        link(p) = y;
    }
    link(x) = p;
    list_ptr(v) = x;
    // ~~~ End section 747 ~~~

    // ~~~ Put the fraction into a box with its delimiters, and make |new_hlist(q)| point to it, 748 ~~~
    if (cur_style < TEXT_STYLE) {
        delta = delim1(cur_size);
    }
    else {
        delta = delim2(cur_size);
    }
    x = var_delimiter(left_delimiter(q), cur_size, delta);
    link(x) = v;
    z = var_delimiter(right_delimiter(q), cur_size, delta);
    link(v) = z;
    new_hlist(q) = hpack(x, NATURAL);
    // ~~~ End section 748 ~~~
}
// ~~~ End section 743 ~~~

// ~~~ Section 749 ~~~
scaled make_op(pointer q) {
    scaled delta;          // offset between subscript and superscript
    pointer p, v, x, y, z; // temporary registers for box construction
    quarterword c;         // registers for character examination
    memory_word i;               
    scaled shift_up, shift_down; // dimensions for box calculation
    
    if (subtype(q) == NORMAL && cur_style < TEXT_STYLE) {
        subtype(q) = LIMITS;
    }
    if (math_type(nucleus(q)) == MATH_CHAR) {
        fetch(nucleus(q));
        if (cur_style < TEXT_STYLE && char_tag(cur_i) == LIST_TAG) {
            // make it larger
            c = rem_byte(cur_i);
            i = char_info(cur_f, c);
            if (char_exists(i)) {
                cur_c = c;
                cur_i = i;
                character(nucleus(q)) = c;
            }
        }
        delta = char_italic(cur_f, cur_i);
        x = clean_box(nucleus(q), cur_style);
        if (math_type(subscr(q)) != EMPTY && subtype(q) != LIMITS) {
            // remove italic correction
            width(x) -= delta;
        }
        // center vertically
        shift_amount(x) = half(height(x) - depth(x)) - axis_height(cur_size);
        math_type(nucleus(q)) = SUB_BOX;
        info(nucleus(q)) = x;
    }
    else {
        delta = 0;
    }
    if (subtype(q) == LIMITS) {
        // ~~~ Construct a box with limits above and below it, skewed by |delta|, 750 ~~~
        x = clean_box(supscr(q), sup_style(cur_style));
        y = clean_box(nucleus(q), cur_style);
        z = clean_box(subscr(q), sub_style(cur_style));
        v = new_null_box();
        type(v) = VLIST_NODE;
        width(v) = width(y);
        if (width(x) > width(v)) {
            width(v) = width(x);
        }
        if (width(z) > width(v)) {
            width(v) = width(z);
        }
        x = rebox(x, width(v));
        y = rebox(y, width(v));
        z = rebox(z, width(v));
        shift_amount(x) = half(delta);
        shift_amount(z) = -shift_amount(x);
        height(v) = height(y);
        depth(v) = depth(y);
        // ~~~ Attach the limits to |y| and adjust |height(v)|, |depth(v)| to account for their presence, 751 ~~~
        if (math_type(supscr(q)) == EMPTY) {
            free_node(x, BOX_NODE_SIZE);
            list_ptr(v) = y;
        }
        else {
            shift_up = big_op_spacing3 - depth(x);
            if (shift_up < big_op_spacing1) {
                shift_up = big_op_spacing1;
            }
            p = new_kern(shift_up);
            link(p) = y;
            link(x) = p;
            p = new_kern(big_op_spacing5);
            link(p) = x;
            list_ptr(v) = p;
            height(v) += big_op_spacing5 + height(x) + depth(x) + shift_up;
        }
        if (math_type(subscr(q)) == EMPTY) {
            free_node(z, BOX_NODE_SIZE);
        }
        else {
            shift_down = big_op_spacing4 - height(z);
            if (shift_down < big_op_spacing2) {
                shift_down = big_op_spacing2;
            }
            p = new_kern(shift_down);
            link(y) = p;
            link(p) = z;
            p = new_kern(big_op_spacing5);
            link(z) = p;
            depth(v) += big_op_spacing5 + height(z) + depth(z) + shift_down;
        }
        // ~~~ End section 751 ~~~
        new_hlist(q) = v;
        // ~~~ End section 750 ~~~
    }
    return delta;
}
// ~~~ End section 749 ~~~

// ~~~ Section 752 ~~~
void make_ord(pointer q) {
    int a; // address of lig/kern instruction
    pointer p, r; // temporary registers for list manipulation
restart:
    if (math_type(subscr(q)) == EMPTY
        && math_type(supscr(q)) == EMPTY
        && math_type(nucleus(q)) == MATH_CHAR)
    {
        p = link(q);
        if (p != null
            && type(p) >= ORD_NOAD
            && type(p) <= PUNCT_NOAD
            && math_type(nucleus(p)) == MATH_CHAR
            && fam(nucleus(p)) == fam(nucleus(q)))
        {
            math_type(nucleus(q)) = MATH_TEXT_CHAR;
            fetch(nucleus(q));
            if (char_tag(cur_i) == LIG_TAG) {
                a = lig_kern_start(cur_f, cur_i);
                cur_c = character(nucleus(p));
                cur_i = font_info[a];
                if (skip_byte(cur_i) > STOP_FLAG) {
                    a = lig_kern_restart(cur_f, cur_i);
                    cur_i = font_info[a];
                }
                while(true) {
                    // ~~~ If instruction |cur_i| is a kern with |cur_c|, attach the kern after |q|; or if it is a ligature with |cur_c|, combine noads |q| and |p| appropriately; then |return| if the cursor has moved past a noad, or |goto restart|, 753 ~~~
                    if (next_char(cur_i) == cur_c && skip_byte(cur_i) <= STOP_FLAG) {
                        if (op_byte(cur_i) >= KERN_FLAG) {
                            p = new_kern(char_kern(cur_f, cur_i));
                            link(p) = link(q);
                            link(q) = p;
                            return;
                        }
                        check_interrupt; // allow a way out of infinite ligature loop
                        switch (op_byte(cur_i)) {
                        case 1:
                        case 5:
                            // =:|, =:|>
                            character(nucleus(q)) = rem_byte(cur_i);
                            break;
                        
                        case 2:
                        case 6:
                            // |=:, |=:>
                            character(nucleus(p)) = rem_byte(cur_i);
                            break;
                    
                        case 3:
                        case 7:
                        case 11: 
                            // |=:|, |=:|>, |=:|>>
                            r = new_noad();
                            character(nucleus(r)) = rem_byte(cur_i);
                            fam(nucleus(r)) = fam(nucleus(q));
                            link(q) = r;
                            link(r) = p;
                            if (op_byte(cur_i) < 11) {
                                math_type(nucleus(r)) = MATH_CHAR;
                            }
                            else {
                                // prevent combination
                                math_type(nucleus(r)) = MATH_TEXT_CHAR;
                            }
                            break;
                        
                        default:
                            // =:
                            link(q) = link(p);
                            character(nucleus(q)) = rem_byte(cur_i);
                            mem[subscr(q)] = mem[subscr(p)];
                            mem[supscr(q)] = mem[supscr(p)];
                            free_node(p, NOAD_SIZE);   
                        }
                        if (op_byte(cur_i) > 3) {
                            return;
                        }
                        math_type(nucleus(q)) = MATH_CHAR;
                        goto restart;
                    }
                    // ~~~ End section 753 ~~~

                    if (skip_byte(cur_i) >= STOP_FLAG) {
                        return;
                    }
                    a += skip_byte(cur_i) + 1;
                    cur_i = font_info[a];
                }
            }
        }
    }
}
// ~~~ End section 752 ~~~

// ~~~ Section 756 ~~~
void make_scripts(pointer q, scaled delta) {
    pointer p, x, y, z;               // temporary registers for box construction
    scaled shift_up, shift_down, clr; // dimensions in the calculation
    small_number t;                   // subsidiary size code
    
    p = new_hlist(q);
    if (is_char_node(p)) {
        shift_up = 0;
        shift_down = 0;
    }
    else {
        z = hpack(p, NATURAL);
        if (cur_style < SCRIPT_STYLE) {
            t = SCRIPT_SIZE;
        }
        else {
            t = SCRIPT_SCRIPT_SIZE;
        }
        shift_up = height(z) - sup_drop(t);
        shift_down = depth(z) + sub_drop(t);
        free_node(z, BOX_NODE_SIZE);
    }
    if (math_type(supscr(q)) == EMPTY) {
        // ~~~ Construct a subscript box |x| when there is no superscript, 757 ~~~
        x = clean_box(subscr(q), sub_style(cur_style));
        width(x) += script_space;
        if (shift_down < sub1(cur_size)) {
            shift_down = sub1(cur_size);
        }
        clr = height(x) - (abs(math_x_height(cur_size) * 4) / 5);
        if (shift_down < clr) {
            shift_down = clr;
        }
        shift_amount(x) = shift_down;
        // ~~~ End section 757 ~~~
    }
    else {
        // ~~~ Construct a superscript box |x|, 758 ~~~
        x = clean_box(supscr(q), sup_style(cur_style));
        width(x) += script_space;
        if (odd(cur_style)) {
            clr = sup3(cur_size);
        }
        else if (cur_style < TEXT_STYLE) {
            clr = sup1(cur_size);
        }
        else {
            clr = sup2(cur_size);
        }
        if (shift_up < clr) {
            shift_up = clr;
        }
        clr = depth(x) + (abs(math_x_height(cur_size)) / 4);
        if (shift_up < clr) {
            shift_up = clr;
        }
        // ~~~ End section 758 ~~~
        if (math_type(subscr(q)) == EMPTY) {
            shift_amount(x) = -shift_up;
        }
        else {
            // ~~~ Construct a sub/superscript combination box |x|, with the superscript offset by |delta|, 759 ~~~
            y = clean_box(subscr(q), sub_style(cur_style));
            width(y) += script_space;
            if (shift_down < sub2(cur_size)) {
                shift_down = sub2(cur_size);
            }
            clr = 4 * default_rule_thickness - ((shift_up - depth(x)) - (height(y) - shift_down));
            if (clr > 0) {
                shift_down += clr;
                clr = (abs(math_x_height(cur_size) * 4) / 5) - (shift_up - depth(x));
                if (clr > 0) {
                    shift_up += clr;
                    shift_down -= clr;
                }
            }
            shift_amount(x) = delta; // superscript is |delta| to the right of the subscript
            p = new_kern((shift_up - depth(x)) - (height(y) - shift_down));
            link(x) = p;
            link(p) = y;
            x = vpack(x, NATURAL);
            shift_amount(x) = shift_down;
            // ~~~ End section 759 ~~~
        }
    }
    if (new_hlist(q) == null) {
        new_hlist(q) = x;
    }
    else {
        p = new_hlist(q);
        while (link(p) != null) {
            p = link(p);
        }
        link(p) = x;
    }
}
// ~~~ End section 756 ~~~

// ~~~ Section 762 ~~~
small_number make_left_right(pointer q, small_number style, scaled max_d, scaled max_h) {
    scaled delta, delta1, delta2; // dimensions used in the calculation
    if (style < SCRIPT_STYLE) {
        cur_size = TEXT_SIZE;
    }
    else {
        cur_size = 16 * ((style - TEXT_STYLE) / 2);
    }
    delta2 = max_d + axis_height(cur_size);
    delta1 = max_h + max_d - delta2;
    if (delta2 > delta1) {
        // |delta1| is max distance from axis
        delta1 = delta2;
    }
    delta = (delta1 / 500) * delimiter_factor;
    delta2 = delta1 + delta1 - delimiter_shortfall;
    if (delta < delta2) {
        delta = delta2;
    }
    new_hlist(q) = var_delimiter(delimiter(q), cur_size, delta);
    return type(q) - (LEFT_NOAD - OPEN_NOAD); // |OPEN_NOAD| or |CLOSE_NOAD|
}
// ~~~ End section 762 ~~~
// ~~~ End section 734 ~~~

// ~~~ Declare |MATH_SPACING| for |mlist_to_hlist|, 764 ~~~
const char *MATH_SPACING = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";
// ~~~ End section 764 ~~~

void mlist_to_hlist() {
    pointer mlist;           // beginning of the given list
    bool penalties;          // should penalty nodes be inserted?
    small_number style;      // the given style
    small_number save_style; // holds |cur_style| during recursion
    pointer q;               // runs through the mlist
    pointer r;               // the most recent noad preceding |q|
    small_number r_type;     // the |type| of noad |r|, or |OP_NOAD| if |r = null|
    small_number t;          // the effective |type| of noad |q| during the second pass
    pointer p, x, y, z;      // temporary registers for list construction
    int pen;                 // a penalty to be inserted
    small_number s;          // the size of a noad to be deleted
    scaled max_h, max_d;     // maximum height and depth of the list translated so far
    scaled delta;            // offset between subscript and superscript

    p = null;
    x = null;
    mlist = cur_mlist;
    penalties = mlist_penalties;
    style = cur_style; // tuck global parameters away as local variables
    q = mlist;
    r = null;
    r_type = OP_NOAD;
    max_h = 0;
    max_d = 0;
    // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
    if (cur_style < SCRIPT_STYLE) {
        cur_size = TEXT_SIZE;
    }
    else {
        cur_size = 16*((cur_style - TEXT_STYLE) / 2);
    }
    cur_mu = x_over_n(math_quad(cur_size), 18);
    // ~~~ End section 703 ~~~
    while (q != null) {
        // ~~~ Process node-or-noad |q| as much as possible in preparation for the second pass of |mlist_to_hlist|, then move to the next item in the mlist, 727 ~~~
        // ~~~ Do first-pass processing based on |type(q)|; |goto done_with_noad| if a noad has been fully processed, |goto check_dimensions| if it has been translated into |new_hlist(q)|, or |goto done_with_node| if a node has been fully processed, 728 ~~~
reswitch:
        delta = 0;
        switch (type(q)) {
        case BIN_NOAD:
            switch (r_type) {
            case BIN_NOAD:
            case OP_NOAD:
            case REL_NOAD:
            case OPEN_NOAD:
            case PUNCT_NOAD:
            case LEFT_NOAD:
                type(q) = ORD_NOAD;
                goto reswitch;
        
            default:
                do_nothing;
            }
            break;
        
        case REL_NOAD:
        case CLOSE_NOAD:
        case PUNCT_NOAD:
        case RIGHT_NOAD:
            // ~~~ Convert a final |BIN_NOAD| to an |ORD_NOAD|, 729 ~~~
            if (r_type == BIN_NOAD) {
                type(r) = ORD_NOAD;
            }
            // ~~~ End section 729 ~~~
            if (type(q) == RIGHT_NOAD) {
                goto done_with_noad;
            }
            break;
        
        // ~~~ Cases for noads that can follow a |BIN_NOAD|, 733 ~~~
        case LEFT_NOAD:
            goto done_with_noad;
        
        case FRACTION_NOAD:
            make_fraction(q);
            goto check_dimensions;
        
        case OP_NOAD:
            delta = make_op(q);
            if (subtype(q) == LIMITS) {
                goto check_dimensions;
            }
            break;
        
        case ORD_NOAD:
            make_ord(q);
            break;
        
        case OPEN_NOAD:
        case INNER_NOAD:
            do_nothing;
            break;
        
        case RADICAL_NOAD:
            make_radical(q);
            break;
        
        case OVER_NOAD:
            make_over(q);
            break;
        
        case UNDER_NOAD:
            make_under(q);
            break;
        
        case ACCENT_NOAD:
            make_math_accent(q);
            break;
        
        case VCENTER_NOAD:
            make_vcenter(q);
            break;
        // ~~~ End section 733 ~~~
        
        // ~~~ Cases for nodes that can appear in an mlist, after which we |goto done_with_node|, 730 ~~~
        case STYLE_NODE:
            cur_style = subtype(q);
            // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
            if (cur_style < SCRIPT_STYLE) {
                cur_size = TEXT_SIZE;
            }
            else {
                cur_size = 16*((cur_style - TEXT_STYLE) / 2);
            }
            cur_mu = x_over_n(math_quad(cur_size), 18);
            // ~~~ End section 703 ~~~
            goto done_with_node;
        
        case CHOICE_NODE:
            // ~~~ Change this node to a style node followed by the correct choice, then |goto done_with_node|, 731 ~~~
            switch (cur_style / 2) {
            case 0:
                // |DISPLAY_STYLE = 0|
                choose_mlist(display_mlist);
                break;
            
            case 1:
                // |TEXT_STYLE = 2|
                choose_mlist(text_mlist);
                break;
            
            case 2:
                // |SCRIPT_STYLE = 4|
                choose_mlist(script_mlist);
                break;
            
            default:
                // case 3:
                // |SCRIPT_SCRIPT_STYLE = 6|
                choose_mlist(script_script_mlist);
            } // there are no other cases
            flush_node_list(display_mlist(q));
            flush_node_list(text_mlist(q));
            flush_node_list(script_mlist(q));
            flush_node_list(script_script_mlist(q));
            type(q) = STYLE_NODE;
            subtype(q) = cur_style;
            width(q) = 0;
            depth(q) = 0;
            if (p != null){
                z = link(q);
                link(q) = p;
                while (link(p) != null) {
                    p = link(p);
                }
                link(p) = z;
            }
            goto done_with_node;
            // ~~~ End section 731 ~~~
        
        case INS_NODE:
        case MARK_NODE:
        case ADJUST_NODE:
        case WHATSIT_NODE:
        case PENALTY_NODE:
        case DISC_NODE:
            goto done_with_node;
        
        case RULE_NODE:
            if (height(q) > max_h) {
                max_h = height(q);
            }
            if (depth(q) > max_d) {
                max_d = depth(q);
            }
            goto done_with_node;
        
        case GLUE_NODE:
            // ~~~ Convert math glue to ordinary glue, 732 ~~~
            if (subtype(q) == MU_GLUE) {
                x = glue_ptr(q);
                y = math_glue(x, cur_mu);
                delete_glue_ref(x);
                glue_ptr(q) = y;
                subtype(q) = NORMAL;
            }
            else if (cur_size != TEXT_SIZE && subtype(q) == COND_MATH_GLUE) {
                p = link(q);
                if (p != null
                    && (type(p) == GLUE_NODE || type(p) == KERN_NODE))
                {
                    link(q) = link(p);
                    link(p) = null;
                    flush_node_list(p);
                }
            }
            // ~~~ End section 732 ~~~
            goto done_with_node;
        
        case KERN_NODE:
            math_kern(q, cur_mu);
            goto done_with_node;
        // ~~~ End section 730 ~~~
        
        default:
            confusion("mlist1");
        }
        
        // ~~~ Convert |nucleus(q)| to an hlist and attach the sub/superscripts, 754 ~~~
        switch (math_type(nucleus(q))) {
        case MATH_CHAR:
        case MATH_TEXT_CHAR:
            // ~~~ Create a character node |p| for |nucleus(q)|, possibly followed by a kern node for the italic correction, and set |delta| to the italic correction if a subscript is present, 755 ~~~
            fetch(nucleus(q));
            if (char_exists(cur_i)) {
                delta = char_italic(cur_f, cur_i);
                p = new_character(cur_f, cur_c);
                if (math_type(nucleus(q)) == MATH_TEXT_CHAR && space(cur_f) != 0) {
                    // no italic correction in mid-word of text font
                    delta = 0;
                }
                if (math_type(subscr(q)) == EMPTY && delta != 0) {
                    link(p) = new_kern(delta);
                    delta = 0;
                }
            }
            else {
                p = null;
            }
            // ~~~ End section 755 ~~~
            break;
        
        case EMPTY:
            p = null;
            break;
        
        case SUB_BOX:
            p = info(nucleus(q));
            break;
        
        case SUB_MLIST:
            cur_mlist = info(nucleus(q));
            save_style = cur_style;
            mlist_penalties = false;
            mlist_to_hlist(); // recursive call
            cur_style = save_style;
            // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
            if (cur_style < SCRIPT_STYLE) {
                cur_size = TEXT_SIZE;
            }
            else {
                cur_size = 16*((cur_style - TEXT_STYLE) / 2);
            }
            cur_mu = x_over_n(math_quad(cur_size), 18);
            // ~~~ End section 703 ~~~
            p = hpack(link(TEMP_HEAD), NATURAL);
            break;
        
        default:
            confusion("mlist2");
        }
        new_hlist(q) = p;
        if (math_type(subscr(q)) == EMPTY && math_type(supscr(q)) == EMPTY) {
            goto check_dimensions;
        }
        make_scripts(q, delta);
        // ~~~ End section 754 ~~~
        // ~~~ End section 728 ~~~
        
check_dimensions:
        z = hpack(new_hlist(q), NATURAL);
        if (height(z) > max_h) {
            max_h = height(z);
        }
        if (depth(z) > max_d) {
            max_d = depth(z);
        }
        free_node(z, BOX_NODE_SIZE);
        
done_with_noad:
        r = q;
        r_type = type(r);
        
done_with_node:
        q = link(q);
        // ~~~ End section 727 ~~~
    }
    // ~~~ Convert a final |BIN_NOAD| to an |ORD_NOAD|, 729 ~~~
    if (r_type == BIN_NOAD) {
        type(r) = ORD_NOAD;
    }
    // ~~~ End section 729 ~~~
    // ~~~ Make a second pass over the mlist, removing all noads and inserting the proper spacing and penalties, 760 ~~~
    p = TEMP_HEAD;
    link(p) = null;
    q = mlist;
    r_type = 0;
    cur_style = style;
    // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
    if (cur_style < SCRIPT_STYLE) {
        cur_size = TEXT_SIZE;
    }
    else {
        cur_size = 16*((cur_style - TEXT_STYLE) / 2);
    }
    cur_mu = x_over_n(math_quad(cur_size), 18);
    // ~~~ End section 703 ~~~
    while (q != null) {
        // ~~~ If node |q| is a style node, change the style and |goto delete_q|; otherwise if it is not a noad, put it into the hlist, advance |q|, and |goto done|; otherwise set |s| to the size of noad |q|, set |t| to the associated type (|ORD_NOAD .. INNER_NOAD|), and set |pen| to the associated penalty, 761 ~~~
        t = ORD_NOAD;
        s = NOAD_SIZE;
        pen = INF_PENALTY;
        switch (type(q)) {
        case OP_NOAD:
        case OPEN_NOAD:
        case CLOSE_NOAD:
        case PUNCT_NOAD:
        case INNER_NOAD:
            t = type(q);
            break;
        
        case BIN_NOAD:
            t = BIN_NOAD;
            pen = bin_op_penalty;
            break;
        
        case REL_NOAD:
            t = REL_NOAD;
            pen = rel_penalty;
            break;
        
        case ORD_NOAD:
        case VCENTER_NOAD:
        case OVER_NOAD:
        case UNDER_NOAD:
            do_nothing;
            break;
        
        case RADICAL_NOAD:
            s = RADICAL_NOAD_SIZE;
            break;
        
        case ACCENT_NOAD:
            s = ACCENT_NOAD_SIZE;
            break;
        
        case FRACTION_NOAD:
            s = FRACTION_NOAD_SIZE;
            break;
        
        case LEFT_NOAD:
        case RIGHT_NOAD:
            t = make_left_right(q, style, max_d, max_h);
            break;
        
        case STYLE_NODE:
            // ~~~ Change the current style and |goto delete_q|, 763 ~~~
            cur_style = subtype(q);
            s = STYLE_NODE_SIZE;
            // ~~~ Set up the values of |cur_size| and |cur_mu|, based on |cur_style|, 703 ~~~
            if (cur_style < SCRIPT_STYLE) {
                cur_size = TEXT_SIZE;
            }
            else {
                cur_size = 16*((cur_style - TEXT_STYLE) / 2);
            }
            cur_mu = x_over_n(math_quad(cur_size), 18);
            // ~~~ End section 703 ~~~
            goto delete_q;
            // ~~~ End section 763 ~~~
        
        case WHATSIT_NODE:
        case PENALTY_NODE:
        case RULE_NODE:
        case DISC_NODE:
        case ADJUST_NODE:
        case INS_NODE:
        case MARK_NODE:
        case GLUE_NODE:
        case KERN_NODE:
            link(p) = q;
            p = q;
            q = link(q);
            link(p) = null;
            continue; // goto done
        
        default:
            confusion("mlist3");
        }
        // ~~~ End section 761 ~~~
    
        // ~~~ Append inter-element spacing based on |r_type| and |t|, 766 ~~~
        if (r_type > 0) {
            // not the first noad
            switch (MATH_SPACING[r_type * 8 + t - 9 * ORD_NOAD]) {
            case '0':
                x = 0;
                break;
            
            case '1':
                if (cur_style < SCRIPT_STYLE) {
                    x = THIN_MU_SKIP_CODE;
                }
                else {
                    x = 0;
                }
                break;
            
            case '2':
                x = THIN_MU_SKIP_CODE;
                break;
            
            case '3':
                if (cur_style < SCRIPT_STYLE) {
                    x = MED_MU_SKIP_CODE;
                }
                else {
                    x = 0;
                }
                break;
            
            case '4':
                if (cur_style < SCRIPT_STYLE) {
                    x = THICK_MU_SKIP_CODE;
                }
                else {
                    x = 0;
                }
                break;
            
            default:
                confusion("mlist4");
            }
        
            if (x != 0) {
                y = math_glue(glue_par(x), cur_mu);
                z = new_glue(y);
                glue_ref_count(y) = null;
                link(p) = z;
                p = z;
                subtype(z) = x + 1; // store a symbolic subtype
            }
        }
        // ~~~ End section 766 ~~~
    
        // ~~~ Append any |new_hlist| entries for |q|, and any appropriate penalties, 767 ~~~
        if (new_hlist(q) != null) {
            link(p) = new_hlist(q);
            do {
                p = link(p);
            } while (link(p) != null);
        }
        if (penalties
            && link(q) != null
            && pen < INF_PENALTY)
        {
            r_type = type(link(q));
            if (r_type != PENALTY_NODE && r_type != REL_NOAD) {
                z = new_penalty(pen);
                link(p) = z;
                p = z;
            }
        }
        // ~~~ End section 767 ~~~
        r_type = t;
delete_q:
        r = q;
        q = link(q);
        free_node(r, s);
    // done: (equivalent to continue the loop)
    }
    // ~~~ End section 760 ~~~
}
// ~~~ End section 726 ~~~
