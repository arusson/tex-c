// ~~~ Section 819 ~~~
// ~~~ Start file |breaker.h|, 1381 ~~~
#ifndef BREAKER_H_
#define BREAKER_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define fitness           subtype              // |VERY_LOOSE_FIT .. TIGHT_FIT| on final line for this break
#define break_node        rlink                // pointer to the corresponding passive node
#define line_number       llink                // line that begins at this breakpoint
#define total_demerits(X) mem[(X) + 2].integer // the quantity that TeX minimizes
// ~~~ End section 819 ~~~

// ~~~ Section 821 ~~~
#define cur_break  rlink // in passive node, points to position of this breakpoint
#define prev_break llink // points to passive node that should precede this one
#define serial     info  // serial number for symbolic identification
// ~~~ End section 821 ~~~

// ~~~ Section 823 ~~~
#define do_all_six(X) X(1); X(2); X(3); X(4); X(5); X(6)
// ~~~ End section 823 ~~~

// ~~~ Section 825 ~~~
#define check_shrinkage(X)                                     \
    do {                                                       \
        if (shrink_order((X)) != NORMAL && shrink((X)) != 0) { \
            (X) = finite_shrink((X));                          \
        }                                                      \
    } while (0)
// ~~~ End section 825 ~~~

// ~~~ Section 829 ~~~
#define copy_to_cur_active(X) cur_active_width[(X)] = active_width[(X)]
// ~~~ End section 829 ~~~

// ~~~ Section 832 ~~~
#define update_width(X) cur_active_width[(X)] += mem[r + (X)].sc
// ~~~ End section 832 ~~~

// ~~~ Section 837 ~~~
#define set_break_width_to_background(X) break_width[(X)] = background[(X)]
// ~~~ End section 837 ~~~

// ~~~ Section 843 ~~~
#define convert_to_break_width(X)   mem[prev_r + (X)].sc += (-cur_active_width[(X)] + break_width[(X)])
#define store_break_width(X)        active_width[(X)] = break_width[(X)]
#define new_delta_to_break_width(X) mem[q + (X)].sc = break_width[(X)] - cur_active_width[(X)]
// ~~~ End section 843 ~~~

// ~~~ Section 844 ~~~
#define new_delta_from_break_width(X) mem[q + (X)].sc = cur_active_width[(X)] - break_width[(X)]
// ~~~ End section 844 ~~~

// ~~~ Section 860 ~~~
#define combine_two_deltas(X) mem[prev_r + (X)].sc += mem[r + (X)].sc
#define downdate_width(X)     cur_active_width[(X)] -= mem[prev_r + (X)].sc
// ~~~ End section 860 ~~~

// ~~~ Section 861 ~~~
#define update_active(X) active_width[(X)] += mem[r + (X)].sc
// ~~~ End section 861 ~~~

// ~~~ Section 864 ~~~
#define store_background(X) active_width[(X)] = background[(X)]
// ~~~ End section 864 ~~~

// ~~~ Section 866 ~~~
#define act_width active_width[1] // length from first active node to current node
#define kern_break                             \
    do {                                       \
        if (!is_char_node(link(cur_p))         \
            && auto_breaking                   \
            && type(link(cur_p)) == GLUE_NODE) \
        {                                      \
            try_break(0, UNHYPHENATED);        \
        }                                      \
        act_width += width(cur_p);             \
    } while (0)
// ~~~ End section 866 ~~~

// ~~~ Section 877 ~~~
#define next_break prev_break // new name for |prev_break| after links are reversed
// ~~~ End section 877 ~~~

// ~~~ Section 908 ~~~
#define append_charnode_to_t(X) \
    link(t) = get_avail();      \
    t = link(t);                \
    font(t) = hf;               \
    character(t) = (X)

#define set_cur_r              \
    do {                       \
        if (j < n) {           \
            cur_r = hu[j + 1]; \
        }                      \
        else {                 \
            cur_r = bchar;     \
        }                      \
        if (odd(hyf[j])) {     \
            cur_rh = hchar;    \
        }                      \
        else {                 \
            cur_rh = NON_CHAR; \
        }                      \
    } while (0)
// ~~~ End section 908 ~~~

// ~~~ Section 910 ~~~
#define wrap_lig(X)                                   \
    do {                                              \
        if (ligature_present) {                       \
            p = new_ligature(hf, cur_l, link(cur_q)); \
            if (lft_hit) {                            \
                subtype(p) = 2;                       \
                lft_hit = false;                      \
            }                                         \
            if ((X) && lig_stack == null) {           \
                incr(subtype(p));                     \
                rt_hit = false;                       \
            }                                         \
            link(cur_q) = p;                          \
            t = p;                                    \
            ligature_present = false;                 \
        }                                             \
    } while (0)

#define pop_lig_stack                                \
    do {                                             \
        if (lig_ptr(lig_stack) > null) {             \
            /* this is a charnode for |hu[j + 1]| */ \
            link(t) = lig_ptr(lig_stack);            \
            t = link(t);                             \
            incr(j);                                 \
        }                                            \
        p = lig_stack;                               \
        lig_stack = link(p);                         \
        free_node(p, SMALL_NODE_SIZE);               \
        if (lig_stack == null) {                     \
            set_cur_r;                               \
        }                                            \
        else {                                       \
            cur_r = character(lig_stack);            \
        }                                            \
    } while (0)
// if |lig_stack| isn't |null| we have |cur_rh = NON_CHAR|
// ~~~ End section 910 ~~~

// ~~~ Section 914 ~~~
#define advance_major_tail major_tail = link(major_tail); incr(r_count)
// ~~~ End section 914 ~~~

// ~~~ Section 921 ~~~
#define trie_link(X) hh_rh(trie[(X)]) // "downward" link in a trie
#define trie_char(X) hh_b1(trie[(X)]) // character matched at this trie location
#define trie_op(X)   hh_b0(trie[(X)]) // program for hyphenation at this trie location
// ~~~ End section 921 ~~~

// ~~~ Section 970 ~~~
#define active_height      active_width           // new name for the six distance variables
#define cur_height         active_height[1]       // the natural height
#define set_height_zero(X) active_height[(X)] = 0 // initialize the height to zero
// ~~~ End section 970 ~~~

// ~~~ Section 1381 ~~~
void line_break(int final_widow_penalty);

void hyphenate();

void init_trie();

// adjust top after page break
pointer prune_page_top(pointer p);

// finds optimum page break
pointer vert_break(pointer p, scaled h, scaled d);

// extracts a page of height |h| from box |n|
pointer vsplit(eight_bits n, scaled h);

#endif
// ~~~ End section 1381 ~~~
