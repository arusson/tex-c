// ~~~ Section 120 ~~~
// ~~~ Start file |memory.c|, 1382 ~~~
#include "datastructures.h"
#include "texerror.h"
#include "extensions.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

// single-word node allocation
pointer get_avail() {
    pointer p; // the new node being got
    p = avail; // get top location in the |avail| stack
    if (p != null) {
        // and pop-it off
        avail = link(avail);
    }
    else if (mem_end < MEM_MAX) {
        // or go into virgin directory
        incr(mem_end);
        p = mem_end;
    }
    else {
        decr(hi_mem_min);
        p = hi_mem_min;
        if (hi_mem_min <= lo_mem_max) {
            // if memory is exhausted, display possible runaway text
            runaway();
            // quit; all one-word nodes are busy
            overflow("main memory size", MEM_MAX + 1 - MEM_MIN);
        }
    }
    link(p) = null; // provide an oft-desired initialization of the new node
    incr_dyn_used; // maintain statistics
    return p;
}
// ~~~ End section 120 ~~~

// ~~~ Section 123 ~~~
// makes list of single-word nodes
void flush_list(pointer p) {
    pointer q, r; // list traversers
    if (p != null) {
        r = p;
        do {
            q = r;
            r = link(r);
            decr_dyn_used;
        } while (r != null);
        // now |q| is the last node on the list
        link(q) = avail;
        avail = p;
    }
}
// ~~~ End section 123 ~~~

// ~~~ Section 125 ~~~
// variable-size node allocation
pointer get_node(int s) {
    pointer p; // the node currently under inspection
    pointer q; // the node physically after node |p|
    int r;     // the newly allocated node, or a candidate for this honor
    int t;     // temporary register

restart:
    p = rover; // start at some free node in the ring
    do {
        // ~~~ Try to allocate within node |p| and its physical successors, and |goto found| if allocation was possible, 127 ~~~
        q = p + node_size(p); // find the physical successor
        while(is_empty(q)) {
            // merge node |p| with node |q|
            t = rlink(q);
            if (q == rover) {
                rover = t;
            }
            llink(t) = llink(q);
            rlink(llink(q)) = t;
            q += node_size(q);
        }
        r = q - s;
        if (r > p + 1) {
            // ~~~ Allocate from the top of node |p| and |goto found|, 128 ~~~
            node_size(p) = r - p; // store the remaining size
            rover = p; // start searching here next time
            goto found;
            // ~~~ End section 128 ~~~
        }
        if (r == p && rlink(p) != p) {
            // ~~~ Allocate entire node |p| and |goto found|, 129 ~~~
            rover = rlink(p);
            t = llink(p);
            llink(rover) = t;
            rlink(t) = rover;
            goto found;
            // ~~~ End section 129 ~~~
        }
        node_size(p) = q - p; // reset the size in case it grew
        // ~~~ End section 127 ~~~
        p = rlink(p); // move to the next node in the ring
    } while (p != rover); // repeat until the whole list has been traversed
    
    if (s == 0x40000000) {
        return MAX_HALFWORD;
    }
    if (lo_mem_max + 2 < hi_mem_min
        && lo_mem_max + 2 <= MEM_BOT + MAX_HALFWORD)
    {
        // ~~~ Grow more variable-size memory and |goto restart|, 126 ~~~
        if (hi_mem_min - lo_mem_max >= 1998) {
            t = lo_mem_max + 1000;
        }
        else {
            // |lo_mem_max + 2 <= t < hi_mem_min|
            t = lo_mem_max + 1 + (hi_mem_min - lo_mem_max) / 2;
        }
        p = llink(rover);
        q = lo_mem_max;
        rlink(p) = q;
        llink(rover) = q;
        
        if (t > MEM_BOT + MAX_HALFWORD) {
            t = MEM_BOT + MAX_HALFWORD;
        }
        rlink(q) = rover;
        llink(q) = p;
        link(q) = EMPTY_FLAG;
        node_size(q) = t - lo_mem_max;
        lo_mem_max = t;
        link(lo_mem_max) = null;
        info(lo_mem_max) = null;
        rover = q;
        goto restart;
        // ~~~ End section 126 ~~~
    }
    // sorry, nothing satisfactory is left
    overflow("main memory size", MEM_MAX + 1 - MEM_MIN);

found:
    link(r) = null; // this node is now nonempty
#ifdef STAT
    var_used += s; // maintain usage statistics
#endif
    return r;
}
// ~~~ End section 125 ~~~

// ~~~ Section 130 ~~~
// variable-size node liberation
void free_node(pointer p, halfword s) {
    pointer q; // |llink(rover)|
    // set both links
    node_size(p) = s;
    link(p) = EMPTY_FLAG;
    q = llink(rover);
    llink(p) = q;
    rlink(p) = rover;
    // insert |p| into the ring
    llink(rover) = p;
    rlink(q) = p;
#ifdef STAT
    var_used -= s; // maintain statistics
#endif
}
// ~~~ End section 130 ~~~

// ~~~ Section 131 ~~~
#ifdef INIT
// sorts the available variable-size nodes by location
void sort_avail() {
    pointer p, q, r;   // indices into |mem|
    pointer old_rover; // initial |rover| setting
    p = get_node(0x40000000); // merge adjacent free areas
    p = rlink(rover);
    rlink(rover) = MAX_HALFWORD;
    old_rover = rover;
    while (p != old_rover) {
        // ~~~ Sort |p| into the list starting at |rover| and advance |p| to |rlink(p)|, 132 ~~~
        if (p < rover) {
            q = p;
            p = rlink(q);
            rlink(q) = rover;
            rover = q;
        }
        else {
            q = rover;
            while (rlink(q) < p) {
                q = rlink(q);
            }
            r = rlink(p);
            rlink(p) = rlink(q);
            rlink(q) = p;
            p = r;
        }
        // ~~~ End section 132 ~~~
    }
    p = rover;
    while (rlink(p) != MAX_HALFWORD) {
        llink(rlink(p)) = p;
        p = rlink(p);
    }
    rlink(p) = rover;
    llink(rover) = p;
}
#endif
// ~~~ End section 131 ~~~

// ~~~ Section 167 ~~~
#ifdef DEBUG
void check_mem(bool print_locs) {
    pointer p, q;   // current locations of interest in |mem|
    bool clobbered; // is something amiss?
    for(p = MEM_MIN; p <= lo_mem_max; p++) {
        free_cells[p] = false; // you can probably do this faster
    }
    for(p = hi_mem_min; p <= mem_end; p++) {
        free_cells[p] = false; // ditto
    }
    // ~~~ Check single-word |avail| list, 168 ~~~
    p = avail;
    q = null;
    while (p != null) {
        if (p > mem_end
            || p < hi_mem_min
            || free_cells[p])
        {
            print_nl("AVAIL list clobbered at ");
            print_int(q);
            break; // Goto done1
        }
        free_cells[p] = true;
        q = p;
        p = link(q);
    }
    // done1:
    // ~~~ End section 168 ~~~
    // ~~~ Check variable-size |avail| list, 169 ~~~
    p = rover;
    q = null;
    do {
        if (p >= lo_mem_max
            || p < MEM_MIN
            || rlink(p) >= lo_mem_max
            || rlink(p) < MEM_MIN
            || !is_empty(p)
            || node_size(p) < 2
            || p + node_size(p) > lo_mem_max
            || llink(rlink(p)) != p)
        {
            print_nl("Double-AVAIL list clobbered at ");
            print_int(q);
            goto done2;
        }
        for(q = p;  q < (p + node_size(p)); q++) {
            if (free_cells[q]) {
                print_nl("Doubly free location at ");
                print_int(q);
                goto done2;
            }
            free_cells[q] = true;
        }
        q = p;
        p = rlink(p);
    } while (p != rover);
done2:
    // ~~~ End section 169 ~~~
    // ~~~ Check flags of unavailable nodes, 170 ~~~
    p = MEM_MIN;
    while (p <= lo_mem_max) {
        // node |p| should not be empty
        if (is_empty(p)) {
            print_nl("Bad flag at ");
            print_int(p);
        }
        while (p <= lo_mem_max && !free_cells[p]) {
            incr(p);
        }
        while (p <= lo_mem_max && free_cells[p]) {
            incr(p);
        }
    }
    // ~~~ End section 170 ~~~
    if (print_locs) {
        // ~~~ Print newly busy locations, 171 ~~~
        print_nl("New busy locs:");
        for(p = MEM_MIN;  p <= lo_mem_max; p++) {
            if (!free_cells[p]
                && (p > was_lo_max || was_free[p]))
            {
                print_char(' ');
                print_int(p);
            }
        }
        for(p = hi_mem_min; p <= mem_end; p++) {
            if (!free_cells[p] && (p < was_hi_min
                || p > was_mem_end
                || was_free[p]))
            {
                print_char(' ');
                print_int(p);
            }
        }
        // ~~~ End section 171 ~~~
    }
    for(p = MEM_MIN; p <= lo_mem_max; p++) {
        was_free[p] = free_cells[p];
    }
    for(p = hi_mem_min; p <= mem_end; p++) {
        was_free[p] = free_cells[p];
    }
    was_mem_end = mem_end;
    was_lo_max = lo_mem_max;
    was_hi_min = hi_mem_min;
}
#endif
// ~~~ End section 167 ~~~

// ~~~ Section 172 ~~~
#ifdef DEBUG
// look for pointers to |p|
void search_mem(pointer p) {
    int q; // current position being searched
    for(q = MEM_MIN; q <= lo_mem_max; q++) {
        if (link(q) == p) {
            print_nl("LINK(");
            print_int(q);
            print_char(')');
        }
        if (info(q) == p) {
            print_nl("INFO(");
            print_int(q);
            print_char(')');
        }
    }
    for(q = hi_mem_min; q <= mem_end; q++) {
        if (link(q) == p) {
            print_nl("LINK(");
            print_int(q);
            print_char(')');
        }
        if (info(q) == p) {
            print_nl("INFO(");
            print_int(q);
            print_char(')');
        }
    }

    // ~~~ Search |eqtb| for equivalents equal to |p|, 255 ~~~
    for(q = ACTIVE_BASE; q <= BOX_BASE + 255; q++) {
        if (equiv(q) == p) {
            print_nl("EQUIV(");
            print_int(q);
            print_char(')');
        }
    }
    // ~~~ End section 255 ~~~
    // ~~~ Search |save_stack| for equivalents that point to |p|, 285 ~~~
    if (save_ptr > 0) {
        for(q = 0; q < save_ptr; q++) {
            if (equiv_field(save_stack[q]) == p) {
                print_nl("SAVE(");
                print_int(q);
                print_char(')');
            }
        }
    }
    // ~~~ End section 285 ~~~
    // ~~~ Search |hyph_list| for pointers to |p|, 933 ~~~
    for(q = 0; q <= HYPH_SIZE; q++) {
        if (hyph_list[q] == p) {
            print_nl("HYPH(");
            print_int(q);
            print_char(')');
        }
    }
    // ~~~ End section 933 ~~~
}
#endif
// ~~~ End section 172 ~~~

// ~~~ Section 200 ~~~
// |p| points to the reference count of a token list that is losing one reference
void delete_token_ref(pointer p) {
    if (token_ref_count(p) == null) {
        flush_list(p);
    }
    else {
        decr(token_ref_count(p));
    }
}
// ~~~ End section 200 ~~~

// ~~~ Section 201 ~~~
// |p| points to a glue specification
void delete_glue_ref(pointer p) {
    fast_delete_glue_ref(p);
}
// ~~~ End section 201 ~~~

// ~~~ Section 202 ~~~
// erase list of nodes starting at |p|
void flush_node_list(pointer p) {
    pointer q; // successor to node |p|
    while (p != null) {
        q = link(p);
        if (is_char_node(p)) {
            free_avail(p);
        }
        else  {
            switch(type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case UNSET_NODE:
                flush_node_list(list_ptr(p));
                free_node(p, BOX_NODE_SIZE);
                goto done;
            
            case RULE_NODE:
                free_node(p, RULE_NODE_SIZE);
                goto done;
            
            case INS_NODE:
                flush_node_list(ins_ptr(p));
                delete_glue_ref(split_top_ptr(p));
                free_node(p, INS_NODE_SIZE);
                goto done;
            
            case WHATSIT_NODE:
                // ~~~ Wipe out the whatsit node |p| and |goto done|, 1358 ~~~
                switch (subtype(p)) {
                case OPEN_NODE:
                    free_node(p, OPEN_NODE_SIZE);
                    break;
                
                case WRITE_NODE:
                case SPECIAL_NODE:
                    delete_token_ref(write_tokens(p));
                    free_node(p, WRITE_NODE_SIZE);
                    goto done;
                
                case CLOSE_NODE:
                case LANGUAGE_NODE:
                    free_node(p, SMALL_NODE_SIZE);
                    break;
                
                default:
                    confusion("ext3");
                }
                goto done;
                // ~~~ End section 1358 ~~~
            
            case GLUE_NODE:
                fast_delete_glue_ref(glue_ptr(p));
                if (leader_ptr(p) != null) {
                    flush_node_list(leader_ptr(p));
                }
                break;
            
            case KERN_NODE:
            case MATH_NODE:
            case PENALTY_NODE:
                do_nothing;
                break;
            
            case LIGATURE_NODE:
                flush_node_list(lig_ptr(p));
                break;
            
            case MARK_NODE:
                delete_token_ref(mark_ptr(p));
                break;
            
            case DISC_NODE:
                flush_node_list(pre_break(p));
                flush_node_list(post_break(p));
                break;
            
            case ADJUST_NODE:
                flush_node_list(adjust_ptr(p));
                break;
            
            // ~~~ Cases of |flush_node_list| that arise in mlists only, 698 ~~~
            case STYLE_NODE:
                free_node(p, STYLE_NODE_SIZE);
                goto done;
            
            case CHOICE_NODE:
                flush_node_list(display_mlist(p));
                flush_node_list(text_mlist(p));
                flush_node_list(script_mlist(p));
                flush_node_list(script_script_mlist(p));
                free_node(p, STYLE_NODE_SIZE);
                goto done;
            
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
                if (math_type(nucleus(p)) >= SUB_BOX) {
                    flush_node_list(info(nucleus(p)));
                }
                if (math_type(supscr(p)) >= SUB_BOX) {
                    flush_node_list(info(supscr(p)));
                }
                if (math_type(subscr(p)) >= SUB_BOX) {
                    flush_node_list(info(subscr(p)));
                }
                if (type(p) == RADICAL_NOAD) {
                    free_node(p, RADICAL_NOAD_SIZE);
                }
                else if (type(p) == ACCENT_NOAD) {
                    free_node(p, ACCENT_NOAD_SIZE);
                }
                else {
                    free_node(p, NOAD_SIZE);
                }
                goto done;
            
            case LEFT_NOAD:
            case RIGHT_NOAD:
                free_node(p, NOAD_SIZE);
                goto done;
            
            case FRACTION_NOAD:
                flush_node_list(info(numerator(p)));
                flush_node_list(info(denominator(p)));
                free_node(p, FRACTION_NOAD_SIZE);
                goto done;
            // ~~~ End section 698 ~~~

            default:
                confusion("flushing");
            }
            free_node(p, SMALL_NODE_SIZE);
done:
        }
        p = q;
    }
}
// ~~~ End section 202 ~~~

// ~~~ Section 204 ~~~
// makes a duplicate of the node list that starts at |p|
// and returns a pointer to the new list
pointer copy_node_list(pointer p) {
    pointer h;        // temporary head of copied list
    pointer q;        // previous position in new list
    pointer r = null; // current node being fabricated for new list
    int words;        // number of words remaining to be copied
    h = get_avail();
    q = h;
    while(p != null) {
        // ~~~ Make a copy of node |p| in node |r|, 205 ~~~
        words = 1; // this setting occurs in more branches than any other
        if (is_char_node(p)) {
            r = get_avail();
        }
        else {
            // ~~~ Case statement to copy different types and set |words| to the number of initial words not yet copied, 206 ~~~
            switch(type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case UNSET_NODE:
                r = get_node(BOX_NODE_SIZE);
                mem[r + 6] = mem[p + 6];
                mem[r + 5] = mem[p + 5]; // copy the last two words
                list_ptr(r) = copy_node_list(list_ptr(p)); // this affects |mem[r+5]|
                words = 5;
                break;
            
            case RULE_NODE:
                r = get_node(RULE_NODE_SIZE);
                words = RULE_NODE_SIZE;
                break;
            
            case INS_NODE:
                r = get_node(INS_NODE_SIZE);
                mem[r + 4] = mem[p + 4];
                add_glue_ref(split_top_ptr(p));
                ins_ptr(r) = copy_node_list(ins_ptr(p)); // this affects |mem[r+4]|
                words = INS_NODE_SIZE - 1;
                break;
            
            case WHATSIT_NODE:
                // ~~~ Make a partial copy of the whatsit node |p| and make |r| point to it; set |words| to the number of initial words not yet copied, 1357 ~~~
                switch (subtype(p)) {
                case OPEN_NODE:
                    r = get_node(OPEN_NODE_SIZE);
                    words = OPEN_NODE_SIZE;
                    break;
                
                case WRITE_NODE:
                case SPECIAL_NODE:
                    r = get_node(WRITE_NODE_SIZE);
                    add_token_ref(write_tokens(p));
                    words = WRITE_NODE_SIZE;
                    break;
                
                case CLOSE_NODE:
                case LANGUAGE_NODE:
                    r = get_node(SMALL_NODE_SIZE);
                    words = SMALL_NODE_SIZE;
                    break;
                
                default:
                    confusion("ext2");
                }
                // ~~~ End section 1357 ~~~
                break;
            
            case GLUE_NODE:
                r = get_node(SMALL_NODE_SIZE);
                add_glue_ref(glue_ptr(p));
                glue_ptr(r) = glue_ptr(p);
                leader_ptr(r) = copy_node_list(leader_ptr(p));
                break;
            
            case KERN_NODE:
            case MATH_NODE:
            case PENALTY_NODE:
                r = get_node(SMALL_NODE_SIZE);
                words = SMALL_NODE_SIZE;
                break;
            
            case LIGATURE_NODE:
                r = get_node(SMALL_NODE_SIZE);
                mem[lig_char(r)] = mem[lig_char(p)]; // copy font and character
                lig_ptr(r) = copy_node_list(lig_ptr(p));
                break;
            
            case DISC_NODE:
                r = get_node(SMALL_NODE_SIZE);
                pre_break(r) = copy_node_list(pre_break(p));
                post_break(r) = copy_node_list(post_break(p));
                break;
            
            case MARK_NODE:
                r = get_node(SMALL_NODE_SIZE);
                add_token_ref(mark_ptr(p));
                words = SMALL_NODE_SIZE;
                break;
            
            case ADJUST_NODE:
                r = get_node(SMALL_NODE_SIZE);
                adjust_ptr(r) = copy_node_list(adjust_ptr(p));
                // words = 1 = SMALL_NODE_SIZE - 1
                break;
            
            default:
                confusion("copying");
            }
            // ~~~ End section 206 ~~~
        }
        while (words > 0) {
          decr(words);
          mem[r + words] = mem[p + words];
        }
        // ~~~ End section 205 ~~~
        link(q) = r;
        q = r;
        p = link(p);
    }
    link(q) = null;
    q = link(h);
    free_avail(h);
    return q;
}
// ~~~ End section 204 ~~~
