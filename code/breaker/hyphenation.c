// ~~~ Section 895 ~~~
// ~~~ Start file |hyphenation.c|, 1382 ~~~
#include "breaker.h"
#include "font_metric.h"
// ~~~ End section 1382 ~~~

// ~~~ Declare the function called |reconstitute|, 906 ~~~
small_number reconstitute(small_number j, small_number n, halfword bchar, halfword hchar) {
    pointer p;          // temporary register for list manipulation
    pointer t;          // a node being appended to
    memory_word q;      // character information or a lig/kern instruction
    halfword cur_rh;    // hyphen character for ligature testing
    halfword test_char; // hyphen or other character for ligature testing
    scaled w;           // amount of kerning
    font_index k;       // position of current lig/kern instruction
    
    hyphen_passed = 0;
    t = HOLD_HEAD;
    w = 0;
    link(HOLD_HEAD) = null;
    // at this point |ligature_present = lft_hit = rt_hit = false|
    // ~~~ Set up data structures with the cursor following position |j|, 908 ~~~
    cur_l = hu[j];
    cur_q = t;
    if (j == 0) {
        ligature_present = init_lig;
        p = init_list;
        if (ligature_present) {
            lft_hit = init_lft;
        }
        while (p > null) {
            append_charnode_to_t(character(p));
            p = link(p);
        }
    }
    else if (cur_l < NON_CHAR) {
        append_charnode_to_t(cur_l);
    }
    lig_stack = null;
    set_cur_r;
    // ~~~ End section 908 ~~~
continue_lbl:
    // ~~~ If there's a ligature or kern at the cursor position, update the data structures, possibly advancing |j|; continue until the cursor moves, 909 ~~~
    if (cur_l == NON_CHAR) {
        k = bchar_label[hf];
        if (k == NON_ADDRESS) {
            goto done;
        }
        else {
            q = font_info[k];
        }
    }
    else {
        q = char_info(hf, cur_l);
        if (char_tag(q) != LIG_TAG) {
            goto done;
        }
        k = lig_kern_start(hf, q);
        q = font_info[k];
        if (skip_byte(q) > STOP_FLAG) {
            k = lig_kern_restart(hf, q);
            q = font_info[k];
        }
    } // now |k| is the starting address of the lig/kern program
    if (cur_rh < NON_CHAR) {
        test_char = cur_rh;
    }
    else {
        test_char = cur_r;
    }
    while(true) {
        if (next_char(q) == test_char && skip_byte(q) <= STOP_FLAG) {
            if (cur_rh < NON_CHAR) {
                hyphen_passed = j;
                hchar = NON_CHAR;
                cur_rh = NON_CHAR;
                goto continue_lbl;
            }
            else {
                if (hchar < NON_CHAR && odd(hyf[j])) {
                    hyphen_passed = j;
                    hchar = NON_CHAR;
                }
                if (op_byte(q) < KERN_FLAG) {
                    // ~~~ Carry out a ligature replacement, updating the cursor structure and possibly advancing |j|; |goto continue| if the cursor doesn't advance, otherwise |goto done|, 911 ~~~
                    if (cur_l == NON_CHAR) {
                        lft_hit = true;
                    }
                    if (j == n && lig_stack == null) {
                        rt_hit = true;
                    }
                    check_interrupt; // allow a way out in case there's an infinite ligature loop
                    switch (op_byte(q)) {
                    case 1:
                    case 5:
                        cur_l = rem_byte(q); // =:|, =:|>
                        ligature_present = true;
                        break;
                    
                    case 2:
                    case 6:
                        cur_r = rem_byte(q); // |=:, |=:>
                        if (lig_stack > null) {
                            character(lig_stack) = cur_r;
                        }
                        else {
                            lig_stack = new_lig_item(cur_r);
                            if (j == n) {
                                bchar = NON_CHAR;
                            }
                            else {
                                p = get_avail();
                                lig_ptr(lig_stack) = p;
                                character(p) = hu[j + 1];
                                font(p) = hf;
                            }
                        }
                        break;
                    
                    case 3:
                        cur_r = rem_byte(q); // |=:|}
                        p = lig_stack;
                        lig_stack = new_lig_item(cur_r);
                        link(lig_stack) = p;
                        break;
                    
                    case 7:
                    case 11:
                        wrap_lig(false); // |=:|>, |=:|>>
                        cur_q = t;
                        cur_l = rem_byte(q);
                        ligature_present = true;
                        break;
                    
                    default:
                        cur_l = rem_byte(q);
                        ligature_present = true; // =:
                        if (lig_stack > null) {
                            pop_lig_stack;
                        }
                        else if (j == n) {
                            goto done;
                        }
                        else {
                            append_charnode_to_t(cur_r);
                            incr(j);
                            set_cur_r;
                        }
                    }
                    if (op_byte(q) > 4 && op_byte(q) != 7) {
                        goto done;
                    }
                    goto continue_lbl;
                    // ~~~ End section 911 ~~~
                }
                w = char_kern(hf, q);
                goto done; // this kern will be inserted below
            }
        }
        if (skip_byte(q) >= STOP_FLAG) {
            if (cur_rh == NON_CHAR) {
                goto done;
            }
            else {
                cur_rh = NON_CHAR;
                goto continue_lbl;
            }
        }
        k += skip_byte(q) + 1;
        q = font_info[k];
    }
done:
    // ~~~ End section 909 ~~~
    // ~~~ Append a ligature and/or kern to the translation; |goto continue| if the stack of inserted ligatures is nonempty, 910 ~~~
    wrap_lig(rt_hit);
    if (w != 0) {
        link(t) = new_kern(w);
        t = link(t);
        w = 0;
    }
    if (lig_stack > null) {
        cur_q = t;
        cur_l = character(lig_stack);
        ligature_present = true;
        pop_lig_stack;
        goto continue_lbl;
    }
    // ~~~ End section 910 ~~~
    return j;
}
// ~~~ End section 906 ~~~

void hyphenate() {
    // ~~~ Local variables for hyphenation, 901 ~~~
    int i, j, l;     // indices into |hc| or |hu|
    pointer q, r, s; // temporary registers for list manipulation
    halfword bchar;  // boundary character of hyphenated word, or |NON_CHAR|
    
    // ~~~ Section 912 ~~~
    pointer major_tail, minor_tail; // the end of lists in the main and discretionary branches being reconstructed
    ASCII_code c = 0;               // character temporarily replaced by a hyphen
    int c_loc;                      // where that character came from
    int r_count;                    // replacement count for discretionary
    pointer hyf_node;               // the hyphen, if it exists
    // ~~~ End section 912 ~~~
    
    // ~~~ Section 922 ~~~
    int z; // an index into |trie|
    int v; // an index into |hyf_distance|, etc.
    // ~~~ End section 922 ~~~
    
    // ~~~ Section 929 ~~~
    int h;          // an index into |hyph_word| and |hyph_list|
    str_number k;   // an index into |str_start|
    pool_pointer u; // an index into |str_pool|
    // ~~~ End section 929 ~~~
    // ~~~ End section 901 ~~~
    // ~~~ Find hyphen locations for the word in |hc|, or |return|, 923 ~~~
    for(j = 0; j <= hn; j++) {
        hyf[j] = 0;
    }
    // ~~~ Look for the word |hc[1..hn]| in the exception table, and |goto found| (with |hyf| containing the hyphens) if an entry is found, 930 ~~~
    h = hc[1];
    incr(hn);
    hc[hn] = cur_lang;
    for(j = 2; j <= hn; j++) {
        h = (h + h + hc[j]) % HYPH_SIZE;
    }
    while(true) {
        // ~~~ If the string |hyph_word[h]| is less than |hc[1..hn]|, |goto not_found|; but if the two strings are equal, set |hyf| to the hyphen positions and |goto found|, 931 ~~~
        k = hyph_word[h];
        if (k == 0 || length(k) < hn) {
            goto not_found;
        }
        if (length(k) == hn) {
            j = 1;
            u = str_start[k];
            do {
                if (str_pool[u] < hc[j]) {
                    goto not_found;
                }
                if (str_pool[u] > hc[j]) {
                    goto done;
                }
                incr(j);
                incr(u);
            } while (j <= hn);
            // ~~~ Insert hyphens as specified in |hyph_list[h]|, 932 ~~~
            s = hyph_list[h];
            while (s != null) {
                hyf[info(s)] = 1;
                s = link(s);
            }
            // ~~~ End section 932 ~~~
            decr(hn);
            goto found;
        }
done:
        // ~~~ End section 931 ~~~
        if (h > 0) {
            decr(h);
        }
        else {
            h = HYPH_SIZE;
        }
    }
not_found:
    decr(hn);
    // ~~~ End section 930 ~~~
    if (trie_char(cur_lang + 1) != cur_lang) {
        return; // no patterns for |cur_lang|
    }
    hc[0] = 0;
    hc[hn + 1] = 0;
    hc[hn + 2] = 256; // insert delimiters
    for(j = 0; j <= hn - r_hyf + 1; j++) {
        z = trie_link(cur_lang + 1) + hc[j];
        l = j;
        while (hc[l] == trie_char(z)) {
            if (trie_op(z) != MIN_QUARTERWORD) {
                // ~~~ Store maximum values in the |hyf| table, 924 ~~~
                v = trie_op(z);
                do {
                    v += op_start[cur_lang];
                    i = l - hyf_distance[v];
                    if (hyf_num[v] > hyf[i]) {
                        hyf[i] = hyf_num[v];
                    }
                    v = hyf_next[v];
                } while (v != MIN_QUARTERWORD);
                // ~~~ End section 924 ~~~
            }
            incr(l);
            z = trie_link(z) + hc[l];
        }
    }
found:
    for(j = 0; j <= l_hyf - 1; j++) {
        hyf[j] = 0;
    }
    for(j = 0; j <= r_hyf - 1; j++) {
        hyf[hn - j] = 0;
    }
    // ~~~ End section 923 ~~~
    // ~~~ If no hyphens were found, |return|, 902 ~~~
    for(j = l_hyf; j <= hn - r_hyf; j++) {
        if (odd(hyf[j])) {
            goto found1;
        }
    }
    return;
found1:
    // ~~~ End section 902 ~~~
    // ~~~ Replace nodes |ha..hb| by a sequence of nodes that includes the discretionary hyphens, 903 ~~~
    q = link(hb);
    link(hb) = null;
    r = link(ha);
    link(ha) = null;
    bchar = hyf_bchar;
    if (is_char_node(ha)) {
        if (font(ha) != hf) {
            goto found2;
        }
        else {
            init_list = ha;
            init_lig = false;
            hu[0] = character(ha);
        }
    }
    else if (type(ha) == LIGATURE_NODE) {
        if (font(lig_char(ha)) != hf) {
            goto found2;
        }
        else {
            init_list = lig_ptr(ha);
            init_lig = true;
            init_lft = (subtype(ha) > 1);
            hu[0] = character(lig_char(ha));
            if (init_list == null && init_lft) {
                hu[0] = 256;
                init_lig = false;
            } // in this case a ligature will be reconstructed from scratch
            free_node(ha, SMALL_NODE_SIZE);
        }
    }
    else {
        // no punctuation found; look for left boundary
        if (!is_char_node(r) && type(r) == LIGATURE_NODE && subtype(r) > 1) {
            goto found2;
        }
        j = 1;
        s = ha;
        init_list = null;
        goto common_ending;
    }
    s = cur_p; // we have |cur_p != ha| because |type(cur_p) = GLUE_NODE|
    while (link(s) != ha) {
        s = link(s);
    }
    j = 0;
    goto common_ending;
found2:
    s = ha;
    j = 0;
    hu[0] = 256;
    init_lig = false;
    init_list = null;
common_ending:
    flush_node_list(r);
    // ~~~ Reconstitute nodes for the hyphenated word, inserting discretionary hyphens, 913 ~~~
    do {
        l = j;
        j = reconstitute(j, hn, bchar, hyf_char) + 1;
        if (hyphen_passed == 0) {
            link(s) = link(HOLD_HEAD);
            while (link(s) > null) {
                s = link(s);
            }
            if (odd(hyf[j - 1])) {
                l = j;
                hyphen_passed = j - 1;
                link(HOLD_HEAD) = null;
            }
        }
        if (hyphen_passed > 0) {
            // ~~~ Create and append a discretionary node as an alternative to the unhyphenated word, and continue to develop both branches until they become equivalent, 914 ~~~
            do {
                r = get_node(SMALL_NODE_SIZE);
                link(r) = link(HOLD_HEAD);
                type(r) = DISC_NODE;
                major_tail = r;
                r_count = 0;
                while (link(major_tail) > null) {
                    advance_major_tail;
                }
                i = hyphen_passed;
                hyf[i] = 0;
                // ~~~ Put the characters |hu[l..i]| and a hyphen into |pre_break(r)|, 915 ~~~
                minor_tail = null;
                pre_break(r) = null;
                hyf_node = new_character(hf, hyf_char);
                if (hyf_node != null) {
                    incr(i);
                    c = hu[i];
                    hu[i] = hyf_char;
                    free_avail(hyf_node);
                }
                while (l <= i) {
                    l = reconstitute(l, i, font_bchar[hf], NON_CHAR) + 1;
                    if (link(HOLD_HEAD) > null) {
                        if (minor_tail == null) {
                            pre_break(r) = link(HOLD_HEAD);
                        }
                        else {
                            link(minor_tail) = link(HOLD_HEAD);
                        }
                        minor_tail = link(HOLD_HEAD);
                        while (link(minor_tail) > null) {
                            minor_tail = link(minor_tail);
                        }
                    }
                }
                if (hyf_node != null) {
                    hu[i] = c; // restore the character in the hyphen position
                    l = i;
                    decr(i);
                }
                // ~~~ End section 915 ~~~
                // ~~~ Put the characters |hu[i + 1..]| into |post_break(r)|, appending to this list and to |major_tail| until synchronization has been achieved, 916 ~~~
                minor_tail = null;
                post_break(r) = null;
                c_loc = 0;
                if (bchar_label[hf] != NON_ADDRESS) {
                    // put left boundary at beginning of new line
                    decr(l);
                    c = hu[l];
                    c_loc = l;
                    hu[l] = 256;
                }
                while (l < j) {
                    do {
                        l = reconstitute(l, hn, bchar, NON_CHAR) + 1;
                        if (c_loc > 0) {
                            hu[c_loc] = c;
                            c_loc = 0;
                        }
                        if (link(HOLD_HEAD) > null) {
                            if (minor_tail == null) {
                                post_break(r) = link(HOLD_HEAD);
                            }
                            else {
                                link(minor_tail) = link(HOLD_HEAD);
                            }
                            minor_tail = link(HOLD_HEAD);
                            while (link(minor_tail) > null) {
                                minor_tail = link(minor_tail);
                            }
                        }
                    } while (l < j);
                    while (l > j) {
                        // ~~~ Append characters of |hu[j..]| to |major_tail|, advancing |j|, 917 ~~~
                        j = reconstitute(j, hn, bchar, NON_CHAR) + 1;
                        link(major_tail) = link(HOLD_HEAD);
                        while (link(major_tail) > null) {
                            advance_major_tail;
                        }
                        // ~~~ End section 917 ~~~
                    }
                }
                // ~~~ End section 916 ~~~
                // ~~~ Move pointer |s| to the end of the current list, and set |replace_count(r)| appropriately, 918 ~~~
                if (r_count > 127) {
                    // we have to forget the discretionary hyphen
                    link(s) = link(r);
                    link(r) = null;
                    flush_node_list(r);
                }
                else {
                    link(s) = r;
                    replace_count(r) = r_count;
                }
                s = major_tail;
                // ~~~ End section 918 ~~~
                hyphen_passed = j - 1;
                link(HOLD_HEAD) = null;
            } while (odd(hyf[j - 1]));
            // ~~~ End section 914 ~~~
        }
    } while (j <= hn);
    link(s) = q;
    // ~~~ End section 913 ~~~
    flush_list(init_list);
    // ~~~ End section 903 ~~~
}
// ~~~ End section 895 ~~~
