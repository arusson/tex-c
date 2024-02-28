// ~~~ Section 597 ~~~
// ~~~ Start file |dvi.c|, 1382 ~~~
#include <math.h>
#include "dvi.h"
#include "texerror.h"
#include "extensions.h"
#include "font_metric.h"
// ~~~ End section 1382 ~~~

void write_dvi(int a, int b) {
    int k;
    for(k = a; k <= b; k++) {
        write_byte(dvi_file, dvi_buf[k]);
    }
}
// ~~~ End section 597 ~~~

// ~~~ Section 598 ~~~
// outputs half of the buffer
void dvi_swap() {
    if (dvi_limit == DVI_BUF_SIZE) {
        write_dvi(0, half_buf - 1);
        dvi_limit = half_buf;
        dvi_offset += DVI_BUF_SIZE;
        dvi_ptr = 0;
    }
    else {
        write_dvi(half_buf, DVI_BUF_SIZE - 1);
        dvi_limit = DVI_BUF_SIZE;
    }
    dvi_gone += half_buf;
}
// ~~~ End section 598 ~~~

// ~~~ Section 600 ~~~
void dvi_four(int x) {
    if (x >= 0) {
        dvi_out(x / 0x1000000);
    }
    else {
        x += 0x40000000;
        x += 0x40000000;
        dvi_out(x / 0x1000000 + 128);
    }
    x %= 0x1000000;
    dvi_out(x / 0x10000);
    x %= 0x10000;
    dvi_out(x / 256);
    dvi_out(x % 256);
}
// ~~~ End section 600 ~~~

// ~~~ Section 601 ~~~
void dvi_pop(int l) {
    if (l == dvi_offset + dvi_ptr && dvi_ptr > 0) {
        decr(dvi_ptr);
    }
    else {
        dvi_out(POP);
    }
}
// ~~~ End section 601 ~~~

// ~~~ Section 602 ~~~
void dvi_font_def(internal_font_number f) {
    int k; // index into |str_pool|
    dvi_out(FNT_DEF1);
    dvi_out(f - FONT_BASE - 1);
    dvi_out(qqqq_b0(font_check[f]));
    dvi_out(qqqq_b1(font_check[f]));
    dvi_out(qqqq_b2(font_check[f]));
    dvi_out(qqqq_b3(font_check[f]));
    dvi_four(font_size[f]);
    dvi_four(font_dsize[f]);
    dvi_out(length(font_area[f]));
    dvi_out(length(font_name[f]));
    // ~~~ Output the font name whose internal number is |f|, 603 ~~~
    for(k = str_start[font_area[f]]; k < str_start[font_area[f] + 1]; k++) {
        dvi_out(str_pool[k]);
    }
    for(k = str_start[font_name[f]]; k < str_start[font_name[f] + 1]; k++) {
        dvi_out(str_pool[k]);
    }
    // ~~~ End section 603 ~~~
}
// ~~~ End section 602 ~~~

// ~~~ Section 607 ~~~
void movement(scaled w, eight_bits o) {
    small_number mstate; // have we seen a |y| or |z|?
    pointer p, q; // current and top nodes on the stack
    int k; // index into |dvi_buf|, modulo |DVI_BUF_SIZE|

    q = get_node(MOVEMENT_NODE_SIZE); // new node for the top of the stack
    width(q) = w;
    location(q) = dvi_offset + dvi_ptr;
    if (o == DOWN1) {
        link(q) = down_ptr;
        down_ptr = q;
    }
    else {
        link(q) = right_ptr;
        right_ptr = q;
    }
    
    // ~~~ Look at the other stack entries until deciding what sort of DVI command to generate; |goto found| if node |p| is a "hit", 611 ~~~
    p = link(q);
    mstate = NONE_SEEN;
    while (p != null) {
        if (width(p) == w) {
            // ~~~ Consider a node with matching width; |goto found| if it's a hit, 612 ~~~
            switch (mstate + info(p)) {
            case NONE_SEEN + YZ_OK:
            case NONE_SEEN + Y_OK:
            case Z_SEEN + YZ_OK:
            case Z_SEEN + Y_OK:
                if (location(p) < dvi_gone) {
                    goto not_found;
                }
                else {
                    // ~~~ Change buffered instruction to |y| or |w| and |goto found|, 613 ~~~
                    k = location(p) - dvi_offset;
                    if (k < 0) {
                        k += DVI_BUF_SIZE;
                    }
                    dvi_buf[k] += Y1 - DOWN1;
                    info(p) = Y_HERE;
                    goto found;
                    // ~~~ End section 613 ~~~
                }
                break;
            
            case NONE_SEEN + Z_OK:
            case Y_SEEN + YZ_OK:
            case Y_SEEN + Z_OK:
                if (location(p) < dvi_gone) {
                    goto not_found;
                }
                else {
                    // ~~~ Change buffered instruction to |z| or |x| and |goto found|, 614 ~~~
                    k = location(p) - dvi_offset;
                    if (k < 0) {
                        k += DVI_BUF_SIZE;
                    }
                    dvi_buf[k] += Z1 - DOWN1;
                    info(p) = Z_HERE;
                    goto found;
                    // ~~~ End section 614 ~~~
                }
                break;
            
            case NONE_SEEN + Y_HERE:
            case NONE_SEEN + Z_HERE:
            case Y_SEEN + Z_HERE:
            case Z_SEEN + Y_HERE:
                goto found;
            
            default:
                do_nothing;
            }
            // ~~~ End section 612 ~~~
        }
        else {
            switch (mstate + info(p)) {
            case NONE_SEEN + Y_HERE:
                mstate = Y_SEEN;
                break;
            
            case NONE_SEEN + Z_HERE:
                mstate = Z_SEEN;
                break;
            
            case Y_SEEN + Z_HERE:
            case Z_SEEN + Y_HERE:
                goto not_found;
            
            default:
                do_nothing;
            }
        }
        p = link(p);
    }
not_found:
    // ~~~ End section 611 ~~~
    
    // ~~~ Generate a |DOWN| or |RIGHT| command for |w| and |return|, 610 ~~~
    info(q) = YZ_OK;
    if (abs(w) >= 0x800000) {
        dvi_out(o + 3); // |DOWN4| or |RIGHT4|
        dvi_four(w);
        return;
    }
    if (abs(w) >= 0x8000 ) {
        dvi_out(o + 2); // |DOWN3| or |RIGHT3|
        if (w < 0) {
            w += 0x1000000;
        }
        dvi_out(w / 0x10000);
        w %= 0x10000;
        goto label_2;
    }
    if (abs(w) >= 128) {
        dvi_out(o + 1); // |DOWN2| or |RIGHT2|
        if (w < 0) {
            w += 0x10000;
        }
        goto label_2;
    }
    dvi_out(o); // |DOWN1| or |RIGHT1|
    if (w < 0) {
        w += 256;
    }
    goto label_1;
label_2:
    dvi_out(w / 256);
label_1:
    dvi_out(w % 256);
    return;
    // ~~~ End section 610 ~~~

found:
    // ~~~ Generate a |Y0| or |Z0| command in order to reuse a previous appearance of |w|, 609 ~~~
    info(q) = info(p);
    if (info(q) == Y_HERE) {
        dvi_out(o + Y0 - DOWN1); // |Y0| or |W0|
        while (link(q) != p) {
            q = link(q);
            switch (info(q)) {
            case YZ_OK:
                info(q) = Z_OK;
                break;
            
            case Y_OK:
                info(q) = D_FIXED;
                break;
            
            default:
                do_nothing;
            }
        }
    }
    else {
        dvi_out(o + Z0 - DOWN1); // |Z0| or |X0|
        while (link(q) != p) {
            q = link(q);
            switch (info(q)) {
            case YZ_OK:
                info(q) = Y_OK;
                break;
            
            case Z_OK:
                info(q) = D_FIXED;
                break;
            
            default:
                do_nothing;
            }
        }
    }
    // ~~~ End section 609 ~~~
}
// ~~~ End section 607 ~~~

// ~~~ Section 615 ~~~
// delete movement nodes with |location >= l|
void prune_movements(int l) {
    pointer p; // node being deleted
    while (down_ptr != null) {
        if (location(down_ptr) < l) {
            break; // goto done
        }
        p = down_ptr;
        down_ptr = link(p);
        free_node(p, MOVEMENT_NODE_SIZE);
    }
    // done:
    while (right_ptr != null) {
        if (location(right_ptr) < l) {
            break; // return
        }
        p = right_ptr;
        right_ptr = link(p);
        free_node(p, MOVEMENT_NODE_SIZE);
    }
}
// ~~~ End section 615 ~~~

// ~~~ Section 619 ~~~
// ~~~ Declare procedures needed in |hlist_out|, |vlist_out|, 1368 ~~~
void special_out(pointer p) {
    int old_setting; // holds print |selector|
    int k;           // index into |str_pool|
    synch_h;
    synch_v;
    old_setting = selector;
    selector = NEW_STRING;
    show_token_list(link(write_tokens(p)), null, POOL_SIZE - pool_ptr);
    selector = old_setting;
    str_room(1);
    if (cur_length < 256) {
        dvi_out(XXX1);
        dvi_out(cur_length);
    }
    else {
        dvi_out(XXX4);
        dvi_four(cur_length);
    }
    for(k = str_start[str_ptr]; k <= pool_ptr - 1; k++) {
        dvi_out(str_pool[k]);
    }
    pool_ptr = str_start[str_ptr]; // erase the string
}

// ~~~ Section 1370 ~~~
void write_out(pointer p) {
    int old_setting; // holds print |selector|
    int old_mode;    // saved |mode|
    small_number j;  // write stream number
    pointer q, r;    // temporary variables for list manipulation
    
    // ~~~ Expand macros in the token list and make |link(def_ref)| point to the result, 1371 ~~~
    q = get_avail();
    info(q) = RIGHT_BRACE_TOKEN + '}';
    r = get_avail();
    link(q) = r;
    info(r) = END_WRITE_TOKEN;
    ins_list(q);
    begin_token_list(write_tokens(p), WRITE_TEXT);
    q = get_avail();
    info(q) = LEFT_BRACE_TOKEN + '{';
    ins_list(q);
    // now we're ready to scan '{<token list>} \endwrite'
    old_mode = mode;
    mode = 0; // disable \prevdepth, \spacefactor, \lastskip, \prevgraf
    cur_cs = write_loc;
    q = scan_toks(false, true); // expand macros, etc.
    get_token();
    if (cur_tok != END_WRITE_TOKEN) {
        // ~~~ Recover from an unbalanced write command, 1372 ~~~
        print_err("Unbalanced write command");
        help2("On this page there's a \\write with fewer real {'s than }'s.")
            ("I can't handle that very well; good luck.");
        error();
        do {
            get_token();
        } while (cur_tok != END_WRITE_TOKEN);
        // ~~~ End section 1372 ~~~
    }
    mode = old_mode;
    end_token_list(); // conserve stack space
    // ~~~ End section 1371 ~~~
    old_setting = selector;
    j = write_stream(p);
    if (write_open[j]) {
        selector = j;
    }
    else {
        // write to the terminal if file isn't open
        if (j == 17 && selector == TERM_AND_LOG) {
            selector = LOG_ONLY;
        }
        print_nl("");
    }
    token_show(def_ref);
    print_ln();
    flush_list(def_ref);
    selector = old_setting;
}
// ~~~ End section 1370 ~~~

// ~~~ Section 1373 ~~~
void out_what(pointer p) {
    small_number j; // write stream number
    switch (subtype(p)) {
    case OPEN_NODE:
    case WRITE_NODE:
    case CLOSE_NODE:
        // ~~~ Do some work that has been queued up for \write, 1374 ~~~
        if (!doing_leaders) {
            j = write_stream(p);
            if (subtype(p) == WRITE_NODE) {
                write_out(p);
            }
            else {
                if (write_open[j]) {
                    a_close(write_file[j]);
                }
                if (subtype(p) == CLOSE_NODE) {
                    write_open[j] = false;
                }
                else if (j < 16) {
                    cur_name = open_name(p);
                    cur_area = open_area(p);
                    cur_ext = open_ext(p);
                    if (cur_ext == EMPTY_STRING) {
                        cur_ext = TEX_EXT; // ".tex"
                    }
                    pack_cur_name;
                    while (!a_open_out(&write_file[j])) {
                        prompt_file_name("output file name", TEX_EXT);
                    }
                    write_open[j] = true;
                }
            }
        }
        // ~~~ End section 1374 ~~~
        break;
    
    case SPECIAL_NODE:
        special_out(p);
        break;
    
    case LANGUAGE_NODE:
        do_nothing;
        break;
    
    default:
        confusion("ext4");
    }
}
// ~~~ End section 1373 ~~~
// ~~~ End section 1368 ~~~

// output an |HLIST_NODE| box
void hlist_out() {
    scaled base_line;         // the baseline coordinate for this box
    scaled left_edge;         // the left coordinate for this box
    scaled save_h, save_v;    // what |dvi_h| and |dvi_v| should pop to
    pointer this_box;         // pointer to containing box
    int g_order;              // applicable order of infinity for glue
    int g_sign;               // selects type of glue
    pointer p;                // current position in the hlist
    int save_loc;             // `DVI` byte location upon entry
    pointer leader_box;       // the leader box being replicated
    scaled leader_wd;         // width of leader box being replicated
    scaled lx;                // extra space between leader boxes
    bool outer_doing_leaders; // were we doing leaders?
    scaled edge;              // left edge of sub-box, or right edge of leader space
    double glue_temp;         // glue value before rounding
    double cur_glue;          // glue seen so far
    scaled cur_g;             // rounded equivalent of |cur_glue| times the glue ratio
    
    cur_g = 0;
    cur_glue = 0.0;
    this_box = temp_ptr;
    g_order = glue_order(this_box);
    g_sign = glue_sign(this_box);
    p = list_ptr(this_box);
    incr(cur_s);
    if (cur_s > 0) {
        dvi_out(PUSH);
    }
    if (cur_s > max_push) {
        max_push = cur_s;
    }
    save_loc = dvi_offset + dvi_ptr;
    base_line = cur_v;
    left_edge = cur_h;
    while (p != null) {
        // ~~~ Output node |p| for |hlist_out| and move to the next node, maintaining the condition |cur_v = base_line|, 620 ~~~
reswitch:
        if (is_char_node(p)) {
            synch_h;
            synch_v;
            do {
                f = font(p);
                c = character(p);
                if (f != dvi_f) {
                    // ~~~ Change font |dvi_f| to |f|, 621 ~~~
                    if (!font_used[f]) {
                        dvi_font_def(f);
                        font_used[f] = true;
                    }
                    if (f <= 64 + FONT_BASE) {
                        dvi_out(f - FONT_BASE - 1 + FNT_NUM_0);
                    }
                    else {
                        dvi_out(FNT1);
                        dvi_out(f - FONT_BASE - 1);
                    }
                    dvi_f = f;
                    // ~~~ End section 621 ~~~
                }
                if (c >= 128) {
                    dvi_out(SET1);
                }
                dvi_out(c);
                cur_h += char_width(f, char_info(f, c));
                p = link(p);
          } while (is_char_node(p));
          dvi_h = cur_h;
        }
        else {
            // ~~~ Output the non-|CHAR_NODE| |p| for |hlist_out| and move to the next node, 622 ~~~
            switch (type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
                // ~~~ Output a box in an hlist, 623 ~~~
                if (list_ptr(p) == null) {
                    cur_h += width(p);
                }
                else {
                    save_h = dvi_h;
                    save_v = dvi_v;
                    cur_v = base_line + shift_amount(p); // shift the box down
                    temp_ptr = p;
                    edge = cur_h;
                    if (type(p) == VLIST_NODE) {
                        vlist_out();
                    }
                    else {
                        hlist_out();
                    }
                    dvi_h = save_h;
                    dvi_v = save_v;
                    cur_h = edge + width(p);
                    cur_v = base_line;
                }
                // ~~~ End section 623 ~~~
                break;
            
            case RULE_NODE:
                rule_ht = height(p);
                rule_dp = depth(p);
                rule_wd = width(p);
                goto fin_rule;
            
            case WHATSIT_NODE:
                // ~~~ Output the whatsit node |p| in an hlist, 1367 ~~~
                out_what(p);
                // ~~~ End section 1367 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ Move right or output leaders, 625 ~~~
                g = glue_ptr(p);
                rule_wd = width(g) - cur_g;
                if (g_sign != NORMAL) {
                    if (g_sign == STRETCHING) {
                        if (stretch_order(g) == g_order) {
                            cur_glue += stretch(g);
                            vet_glue(glue_set(this_box)*cur_glue);
                            cur_g = (scaled)round(glue_temp);
                        }
                    }
                    else if (shrink_order(g) == g_order) {
                        cur_glue -= shrink(g);
                        vet_glue(glue_set(this_box)*cur_glue);
                        cur_g = (scaled)round(glue_temp);
                    }
                }
                rule_wd += cur_g;
                if (subtype(p) >= A_LEADERS) {
                    // ~~~ Output leaders in an hlist, |goto fin_rule| if a rule or to |next_p| if done, 626 ~~~
                    leader_box = leader_ptr(p);
                    if (type(leader_box) == RULE_NODE) {
                        rule_ht = height(leader_box);
                        rule_dp = depth(leader_box);
                        goto fin_rule;
                    }
                    leader_wd = width(leader_box);
                    if (leader_wd > 0 && rule_wd > 0) {
                        rule_wd += 10; // compensate for floating - point rounding
                        edge = cur_h + rule_wd;
                        lx = 0;
                        // ~~~ Let |cur_h| be the position of the first box, and set |leader_wd + lx| to the spacing between corresponding parts of boxes, 627 ~~~
                        if (subtype(p) == A_LEADERS) {
                            save_h = cur_h;
                            cur_h = left_edge + leader_wd*((cur_h - left_edge) / leader_wd);
                            if (cur_h < save_h) {
                                cur_h += leader_wd;
                            }
                        }
                        else {
                            lq = rule_wd / leader_wd; // the number of box copies
                            lr = rule_wd % leader_wd; // the remaining space
                            if (subtype(p) == C_LEADERS) {
                                cur_h += lr / 2;
                            }
                            else {
                                lx = lr / (lq + 1);
                                cur_h += (lr - (lq - 1) * lx) / 2;
                            }
                        }
                        // ~~~ End section 627 ~~~
                        while (cur_h + leader_wd <= edge) {
                            // ~~~ Output a leader box at |cur_h|, then advance |cur_h| by |leader_wd + lx|, 628 ~~~
                            cur_v = base_line + shift_amount(leader_box);
                            synch_v;
                            save_v = dvi_v;
                            synch_h;
                            save_h = dvi_h;
                            temp_ptr = leader_box;
                            outer_doing_leaders = doing_leaders;
                            doing_leaders = true;
                            if (type(leader_box) == VLIST_NODE) {
                                vlist_out();
                            }
                            else {
                                hlist_out();
                            }
                            doing_leaders = outer_doing_leaders;
                            dvi_v = save_v;
                            dvi_h = save_h;
                            cur_v = base_line;
                            cur_h = save_h + leader_wd + lx;
                            // ~~~ End section 628 ~~~
                        }
                        cur_h = edge - 10;
                        goto next_p;
                    }
                    // ~~~ End section 626 ~~~
                }
                goto move_past;
                // ~~~ End section 625 ~~~
            
            case KERN_NODE:
            case MATH_NODE:
                cur_h += width(p);
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
            goto next_p;
            
fin_rule:
            // ~~~ Output a rule in an hlist, 624 ~~~
            if (is_running(rule_ht)) {
                rule_ht = height(this_box);
            }
            if (is_running(rule_dp)) {
                rule_dp = depth(this_box);
            }
            rule_ht += rule_dp; // this is the rule thickness
            if (rule_ht > 0 && rule_wd > 0) {
                // we don't output empty rules
                synch_h;
                cur_v = base_line + rule_dp;
                synch_v;
                dvi_out(SET_RULE);
                dvi_four(rule_ht);
                dvi_four(rule_wd);
                cur_v = base_line;
                dvi_h += rule_wd;
            }
            // ~~~ End section 624 ~~~
            
move_past:
            cur_h += rule_wd;
            
next_p:
            p = link(p);
            // ~~~ End section 622 ~~~
        }
        // ~~~ End section 620 ~~~
    }
    prune_movements(save_loc);
    if (cur_s > 0) {
        dvi_pop(save_loc);
    }
    decr(cur_s);
}
// ~~~ End section 619 ~~~

// ~~~ Section 629 ~~~
// output a |VLIST_NODE| box
void vlist_out() {
    scaled left_edge;         // the left coordinate for this box
    scaled top_edge;          // the top coordinate for this box
    scaled save_h, save_v;    // what |dvi_h| and |dvi_v| should pop to
    pointer this_box;         // pointer to containing box
    int g_order;              // applicable order of infinity for glue
    int g_sign;               // selects type of glue
    pointer p;                // current position in the vlist
    int save_loc;             // `DVI` byte location upon entry
    pointer leader_box;       // the leader box being replicated
    scaled leader_ht;         // height of leader box being replicated
    scaled lx;                // extra space between leader boxes
    bool outer_doing_leaders; // were we doing leaders?
    scaled edge;              // bottom boundary of leader space
    double glue_temp;         // glue value before rounding
    double cur_glue;          // glue seen so far
    scaled cur_g;             // rounded equivalent of |cur_glue| times the glue ratio
    
    cur_g = 0;
    cur_glue = 0.0;
    this_box = temp_ptr;
    g_order = glue_order(this_box);
    g_sign = glue_sign(this_box);
    p = list_ptr(this_box);
    incr(cur_s);
    if (cur_s > 0) {
        dvi_out(PUSH);
    }
    if (cur_s > max_push) {
        max_push = cur_s;
    }
    save_loc = dvi_offset + dvi_ptr;
    left_edge = cur_h;
    cur_v -= height(this_box);
    top_edge = cur_v;
    while (p != null) {
        // ~~~ Output node |p| for |vlist_out| and move to the next node, maintaining the condition |cur_h = left_edge|, 630 ~~~
        if (is_char_node(p)) {
            confusion("vlistout");
        }
        else {
            // ~~~ Output the non-|CHAR_NODE| |p| for |vlist_out|, 631 ~~~
            switch (type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
                // ~~~ Output a box in a vlist, 632 ~~~
                if (list_ptr(p) == null) {
                    cur_v += height(p) + depth(p);
                }
                else {
                    cur_v += height(p);
                    synch_v;
                    save_h = dvi_h;
                    save_v = dvi_v;
                    cur_h = left_edge + shift_amount(p); // shift the box right
                    temp_ptr = p;
                    if (type(p) == VLIST_NODE) {
                        vlist_out();
                    }
                    else {
                        hlist_out();
                    }
                    dvi_h = save_h;
                    dvi_v = save_v;
                    cur_v = save_v + depth(p);
                    cur_h = left_edge;
                }
                // ~~~ End section 632 ~~~
                break;
            
            case RULE_NODE:
                rule_ht = height(p);
                rule_dp = depth(p);
                rule_wd = width(p);
                goto fin_rule;
            
            case WHATSIT_NODE:
                // ~~~ Output the whatsit node |p| in a vlist, 1366 ~~~
                out_what(p);
                // ~~~ End section 1366 ~~~
                break;
            
            case GLUE_NODE:
                // ~~~ Move down or output leaders, 634 ~~~
                g = glue_ptr(p);
                rule_ht = width(g) - cur_g;
                if (g_sign != NORMAL) {
                    if (g_sign == STRETCHING) {
                        if (stretch_order(g) == g_order) {
                            cur_glue += stretch(g);
                            vet_glue(glue_set(this_box)*cur_glue);
                            cur_g = (scaled)round(glue_temp);
                        }
                    }
                    else if (shrink_order(g) == g_order) {
                        cur_glue -= shrink(g);
                        vet_glue(glue_set(this_box)*cur_glue);
                        cur_g = (scaled)round(glue_temp);
                    }
                }
                rule_ht += cur_g;
                if (subtype(p) >= A_LEADERS) {
                    // ~~~ Output leaders in a vlist, |goto fin_rule| if a rule or to |next_p| if done, 635 ~~~
                    leader_box = leader_ptr(p);
                    if (type(leader_box) == RULE_NODE) {
                        rule_wd = width(leader_box);
                        rule_dp = 0;
                        goto fin_rule;
                    }
                    leader_ht = height(leader_box) + depth(leader_box);
                    if (leader_ht > 0 && rule_ht > 0) {
                        rule_ht += 10; // compensate for floating - point rounding
                        edge = cur_v + rule_ht;
                        lx = 0;
                        // ~~~ Let |cur_v| be the position of the first box, and set |leader_ht + lx| to the spacing between corresponding parts of boxes, 636 ~~~
                        if (subtype(p) == A_LEADERS) {
                            save_v = cur_v;
                            cur_v = top_edge + leader_ht*((cur_v - top_edge) / leader_ht);
                            if (cur_v < save_v) {
                                cur_v += leader_ht;
                            }
                        }
                        else {
                            lq = rule_ht / leader_ht; // the number of box copies
                            lr = rule_ht % leader_ht; // the remaining space
                            if (subtype(p) == C_LEADERS) {
                                cur_v += lr / 2;
                            }
                            else {
                                lx = lr / (lq + 1);
                                cur_v += (lr - (lq - 1) * lx)/2;
                            }
                        }
                        // ~~~ End section 636 ~~~
                        while (cur_v + leader_ht <= edge) {
                            // ~~~ Output a leader box at |cur_v|, then advance |cur_v| by |leader_ht + lx|, 637 ~~~
                            cur_h = left_edge + shift_amount(leader_box);
                            synch_h;
                            save_h = dvi_h;
                            cur_v += height(leader_box);
                            synch_v;
                            save_v = dvi_v;
                            temp_ptr = leader_box;
                            outer_doing_leaders = doing_leaders;
                            doing_leaders = true;
                            if (type(leader_box) == VLIST_NODE) {
                                vlist_out();
                            }
                            else {
                                hlist_out();
                            }
                            doing_leaders = outer_doing_leaders;
                            dvi_v = save_v;
                            dvi_h = save_h;
                            cur_h = left_edge;
                            cur_v = save_v - height(leader_box) + leader_ht + lx;
                            // ~~~ End section 637 ~~~
                        }
                        cur_v = edge - 10;
                        goto next_p;
                    }
                    // ~~~ End section 635 ~~~
                }
                goto move_past;
                // ~~~ End section 634 ~~~
            
            case KERN_NODE:
                cur_v += width(p);
                break;
            
            default:
                do_nothing;
            }
            goto next_p;
            
fin_rule:
            // ~~~ Output a rule in a vlist, |goto next_p|, 633 ~~~
            if (is_running(rule_wd)) {
                rule_wd = width(this_box);
            }
            rule_ht += rule_dp; // this is the rule thickness
            cur_v += rule_ht;
            if (rule_ht > 0 && rule_wd > 0) {
                // we don't output empty rules
                synch_h;
                synch_v;
                dvi_out(PUT_RULE);
                dvi_four(rule_ht);
                dvi_four(rule_wd);
            }
            goto next_p;
            // ~~~ End section 633 ~~~
            
move_past:
            cur_v += rule_ht;
            // ~~~ End section 631 ~~~
        }
next_p:
        p = link(p);
        // ~~~ End section 630 ~~~
    }
    prune_movements(save_loc);
    if (cur_s > 0) {
        dvi_pop(save_loc);
    }
    decr(cur_s);
}
// ~~~ End section 629 ~~~

// ~~~ Section 638 ~~~
// output the box |p|
void ship_out(pointer p) {
    int page_loc;    // location of the current |BOP|
    int j, k;        // indices to first ten count registers
    pool_pointer s;  // index into |str_pool|
    int old_setting; // saved |selector| setting
    
    if (tracing_output > 0) {
        print_nl("");
        print_ln();
        print("Completed box being shipped out");
    }
    if (term_offset > MAX_PRINT_LINE - 9) {
        print_ln();
    }
    else if (term_offset > 0 || file_offset > 0) {
        print_char(' ');
    }
    print_char('[');
    j = 9;
    while (count(j) == 0 && j > 0) {
        decr(j);
    }
    for(k = 0; k <= j; k++) {
        print_int(count(k));
        if (k < j) {
            print_char('.');
        }
    }
    update_terminal;
    if (tracing_output > 0) {
        print_char(']');
        begin_diagnostic();
        show_box(p);
        end_diagnostic(true);
    }
    // ~~~ Ship box |p| out, 640 ~~~
    // ~~~ Update the values of |max_h| and |max_v|; but if the page is too large, |goto done|, 641 ~~~
    if (height(p) > MAX_DIMEN
        || depth(p) > MAX_DIMEN
        || height(p) + depth(p) + v_offset > MAX_DIMEN
        || width(p) + h_offset > MAX_DIMEN)
    {
        print_err("Huge page cannot be shipped out");
        help2("The page just created is more than 18 feet tall or")
            ("more than 18 feet wide, so I suspect something went wrong.");
        error();
        if (tracing_output <= 0) {
            begin_diagnostic();
            print_nl("The following box has been deleted:");
            show_box(p);
            end_diagnostic(true);
        }
        goto done;
    }
    if (height(p) + depth(p) + v_offset > max_v) {
        max_v = height(p) + depth(p) + v_offset;
    }
    if (width(p) + h_offset > max_h) {
        max_h = width(p) + h_offset;
    }
    // ~~~ End section 641 ~~~
    // ~~~ Initialize variables as |ship_out| begins, 617 ~~~
    dvi_h = 0;
    dvi_v = 0;
    cur_h = h_offset;
    dvi_f = NULL_FONT;
    ensure_dvi_open;
    if (total_pages == 0) {
        dvi_out(PRE);
        dvi_out(ID_BYTE); // output the preamble
        dvi_four(25400000);
        dvi_four(473628672); // conversion ratio for sp
        prepare_mag();
        dvi_four(mag); // magnification factor is frozen
        old_setting = selector;
        selector = NEW_STRING;
        print(" TeX output ");
        print_int(year);
        print_char('.');
        print_two(month);
        print_char('.');
        print_two(day);
        print_char(':');
        print_two(time_ / 60);
        print_two(time_ % 60);
        selector = old_setting;
        dvi_out(cur_length);
        for(s = str_start[str_ptr]; s < pool_ptr; s++) {
            dvi_out(str_pool[s]);
        }
        pool_ptr = str_start[str_ptr]; // flush the current string
    }
    // ~~~ End section 617 ~~~
    page_loc = dvi_offset + dvi_ptr;
    dvi_out(BOP);
    for(k = 0; k <= 9; k++) {
        dvi_four(count(k));
    }
    dvi_four(last_bop);
    last_bop = page_loc;
    cur_v = height(p) + v_offset;
    temp_ptr = p;
    if (type(p) == VLIST_NODE) {
        vlist_out();
    }
    else {
        hlist_out();
    }
    dvi_out(EOP);
    incr(total_pages);
    cur_s = -1;
done:
    // ~~~ End section 640 ~~~
    if (tracing_output <= 0) {
        print_char(']');
    }
    dead_cycles = 0;
    update_terminal; // progress report
    // ~~~ Flush the box from memory, showing statistics if requested, 639 ~~~
#ifdef STAT
    if (tracing_stats > 1) {
        print_nl("Memory usage before: ");
        print_int(var_used);
        print_char('&');
        print_int(dyn_used);
        print_char(';');
    }
#endif
    flush_node_list(p);
#ifdef STAT
    if (tracing_stats > 1) {
        print(" after: ");
        print_int(var_used);
        print_char('&');
        print_int(dyn_used);
        print("; still untouched: ");
        print_int(hi_mem_min - lo_mem_max - 1);
        print_ln();
    }
#endif
    // ~~~ End section 639 ~~~
}
// ~~~ End section 638 ~~~
