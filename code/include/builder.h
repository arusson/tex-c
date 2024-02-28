// ~~~ Section 644 ~~~
// ~~~ Start file |builder.h|, 1381 ~~~
#ifndef BUILDER_H_
#define BUILDER_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define EXACTLY    0             // a box dimension is pre-specified
#define ADDITIONAL 1             // a box dimension is increased from the natural one
#define NATURAL    0, ADDITIONAL // shorthand for parameters to |hpack| and |vpack|
// ~~~ End section 644 ~~~

// ~~~ Section 668 ~~~
// special case of unconstrained depth
#define vpack(...) vpackage(__VA_ARGS__, MAX_DIMEN) 
// ~~~ End section 668 ~~~

// ~~~ Section 981 ~~~
#define broken_ptr(X)   link((X) + 1) // an insertion for this class will break here if anywhere
#define broken_ins(X)   info((X) + 1) // this insertion might break at |broken_ptr|
#define last_ins_ptr(X) link((X) + 2) // the most recent insertion for this |subtype|
#define best_ins_ptr(X) info((X) + 2) // the optimum most recent insertion
// ~~~ End section 981 ~~~

// ~~~ Section 982 ~~~
#define page_goal   page_so_far[0] // desired height of information on page being built
#define page_total  page_so_far[1] // height of the current page
#define page_shrink page_so_far[6] // shrinkability of the current page
#define page_depth  page_so_far[7] // depth of the current page
// ~~~ End section 982 ~~~

// ~~~ Section 987 ~~~
#define set_page_so_far_zero(X) page_so_far[(X)] = 0
// ~~~ End section 987 ~~~

// ~~~ Section 995 ~~~
#define contrib_tail nest[0].tail_field // tail of the contribution list
// ~~~ End section 995 ~~~

// ~~~ Section 1034 ~~~
#define adjust_space_factor             \
    do {                                \
        main_s = sf_code(cur_chr);      \
        if (main_s == 1000) {           \
            space_factor = 1000;        \
        }                               \
        else if (main_s < 1000) {       \
            if (main_s > 0) {           \
                space_factor = main_s;  \
            }                           \
        }                               \
        else if (space_factor < 1000) { \
            space_factor = 1000;        \
        }                               \
        else {                          \
            space_factor = main_s;      \
        }                               \
    } while (0)
// ~~~ End section 1034 ~~~

// ~~~ Section 1035 ~~~
// the parameter is either |rt_hit| or |false|
#define pack_lig(X)                                    \
    main_p = new_ligature(main_f, cur_l, link(cur_q)); \
    if (lft_hit) {                                     \
        subtype(main_p) = 2;                           \
        lft_hit = false;                               \
    }                                                  \
    if ((X) && lig_stack == null) {                    \
        incr(subtype(main_p));                         \
        rt_hit = false;                                \
    }                                                  \
    link(cur_q) = main_p;                              \
    tail = main_p;                                     \
    ligature_present = false

#define wrapup(X)                                           \
    do {                                                    \
        if (cur_l < NON_CHAR) {                             \
            if (link(cur_q) > null                          \
                && character(tail) == hyphen_char[main_f])  \
            {                                               \
                ins_disc = true;                            \
            }                                               \
            if (ligature_present) {                         \
                pack_lig((X));                              \
            }                                               \
            if (ins_disc) {                                 \
                ins_disc = false;                           \
                if (mode > 0) {                             \
                    tail_append(new_disc());                \
                }                                           \
            }                                               \
        }                                                   \
    } while (0)
// ~~~ End section 1035 ~~~

// ~~~ Section 1045 ~~~
// for mode-independent commands
#define any_mode(X)   \
    case VMODE + (X): \
    case HMODE + (X): \
    case MMODE + (X)
// ~~~ End section 1045 ~~~

// ~~~ Section 1046 ~~~
#define non_math(X)   \
    case VMODE + (X): \
    case HMODE + (X)
// ~~~ End section 1046 ~~~

// ~~~ Section 1214 ~~~
#define global (a >= 4)
#define define(...)                  \
    do {                             \
        if (global) {                \
            geq_define(__VA_ARGS__); \
        }                            \
        else {                       \
            eq_define(__VA_ARGS__);  \
        }                            \
    } while (0)

#define word_define(...)                  \
    do {                                  \
        if (global) {                     \
            geq_word_define(__VA_ARGS__); \
        }                                 \
        else {                            \
            eq_word_define(__VA_ARGS__);  \
        }                                 \
    } while (0)
// ~~~ End section 1214 ~~~

// ~~~ Section 1381 ~~~
pointer hpack(pointer p, scaled w, small_number m);

pointer vpackage(pointer p, scaled h, small_number m, scaled l);

void append_to_vlist(pointer b);

void box_error(eight_bits n);

void build_page();

void main_control();

void you_cant();

void report_illegal_case();

void append_glue();

void append_kern();

void off_save();

void handle_right_brace();

void extra_right_brace();

void normal_paragraph();

void begin_box(int box_context);

// the next input should specify a box or perhaps a rule
void scan_box(int box_context);

void package(small_number c);

small_number norm_min(int h);
void new_graf(bool indented);

void indent_in_hmode();

void head_for_vmode();

void end_graf();

void begin_insert_or_adjust();

void make_mark();

void append_penalty();

void delete_last();

void unpackage();

void append_italic_correction();

void append_discretionary();

void build_discretionary();

void make_accent();

void align_error();

void do_endv();

void prefixed_command();

void do_assignments();

void open_or_close_in();

void issue_message();

void shift_case();
#endif
// ~~~ End section 1381 ~~~
