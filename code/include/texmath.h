// ~~~ Section 681 ~~~
// ~~~ Start file |texmath.h|, 1381 ~~~
#ifndef MATH_H_
#define MATH_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define nucleus(X) ((X) + 1) // the |nucleus| field of a noad
#define supscr(X)  ((X) + 2) // the |supscr| field of a noad
#define subscr(X)  ((X) + 3) // the |subscr| field of a noad
#define math_type  link      // a |halfword| in |mem|
#define fam        font      // a |quarterword| in |mem|
// ~~~ End section 681 ~~~

// ~~~ Section 683 ~~~
#define left_delimiter(X)  ((X) + 4)         // first delimiter field of a noad
#define right_delimiter(X) ((X) + 5)         // second delimiter field of a fraction noad
#define small_fam(X)       qqqq_b0(mem[(X)]) // |fam| for "small" delimiter
#define small_char(X)      qqqq_b1(mem[(X)]) // |character| for "small" delimiter
#define large_fam(X)       qqqq_b2(mem[(X)]) // |fam| for "large" delimiter
#define large_char(X)      qqqq_b3(mem[(X)]) // |character| for "large" delimiter
#define thickness          width             // |thickness| field in a fraction noad
#define numerator          supscr            // |numerator| field in a fraction noad
#define denominator        subscr            // |denominator| field in a fraction noad
// ~~~ End section 683 ~~~

// ~~~ Section 687 ~~~
#define accent_chr(X)      ((X) + 4) // the |accent_chr| field of an accent noad
#define delimiter          nucleus   // |delimiter| field in left and right noads
#define scripts_allowed(X) (type((X)) >= ORD_NOAD && type((X)) < LEFT_NOAD)
// ~~~ End section 687 ~~~

// ~~~ Section 689 ~~~
#define display_mlist(X)       info((X) + 1) // mlist to be used in display style
#define text_mlist(X)          link((X) + 1) // mlist to be used in text style
#define script_mlist(X)        info((X) + 2) // mlist to be used in script style
#define script_script_mlist(X) link((X) + 2) // mlist to be used in scriptscript style
// ~~~ End section 689 ~~~

// ~~~ Section 700 ~~~
#define mathsy(X, Y)     font_info[(X) + param_base[fam_fnt(2 + (Y))]].sc
#define math_x_height(X) mathsy(5, (X))  // height of 'x'
#define math_quad(X)     mathsy(6, (X))  // 18mu
#define num1(X)          mathsy(8, (X))  // numerator shift-up in display styles
#define num2(X)          mathsy(9, (X))  // numerator shift-up in non - display, non-\atop
#define num3(X)          mathsy(10, (X)) // numerator shift-up in non-display \atop
#define denom1(X)        mathsy(11, (X)) // denominator shift-down in display styles
#define denom2(X)        mathsy(12, (X)) // denominator shift-down in non-display styles
#define sup1(X)          mathsy(13, (X)) // superscript shift-up in uncramped display style
#define sup2(X)          mathsy(14, (X)) // superscript shift-up in uncramped non-display
#define sup3(X)          mathsy(15, (X)) // superscript shift-up in cramped styles
#define sub1(X)          mathsy(16, (X)) // subscript shift-down if superscript is absent
#define sub2(X)          mathsy(17, (X)) // subscript shift-down if superscript is present
#define sup_drop(X)      mathsy(18, (X)) // superscript baseline below top of large box
#define sub_drop(X)      mathsy(19, (X)) // subscript baseline below bottom of large box
#define delim1(X)        mathsy(20, (X)) // size of \atopwithdelims delimiters in display styles
#define delim2(X)        mathsy(21, (X)) // size of \atopwithdelims delimiters in non - displays
#define axis_height(X)   mathsy(22, (X)) // height of fraction lines above the baseline
// ~~~ End section 700 ~~~

// ~~~ Section 701 ~~~
#define mathex(X)              font_info[(X) + param_base[fam_fnt(3 + cur_size)]].sc
#define default_rule_thickness mathex(8)  // thickness of \\over} bars
#define big_op_spacing1        mathex(9)  // minimum clearance above a displayed op
#define big_op_spacing2        mathex(10) // minimum clearance below a displayed op
#define big_op_spacing3        mathex(11) // minimum baselineskip above displayed op
#define big_op_spacing4        mathex(12) // minimum baselineskip below displayed op
#define big_op_spacing5        mathex(13) // padding above and below displayed limits
// ~~~ End section 701 ~~~

// ~~~ Section 702 ~~~
#define cramped_style(X) (2*((X) / 2) + CRAMPED)                   // cramp the style
#define sub_style(X)     (2*((X) / 4) + SCRIPT_STYLE + CRAMPED)    // smaller and cramped
#define sup_style(X)     (2*((X) / 4) + SCRIPT_STYLE + ((X) % 2))  // smaller
#define num_style(X)     ((X) + 2 - 2*((X) / 6))                   // smaller unless already script-script
#define denom_style(X)   (2*((X) / 2) + CRAMPED + 2 - 2*((X) / 6)) // smaller, cramped
// ~~~ End section 702 ~~~

// ~~~ Section 716 ~~~
#define mu_mult(X) nx_plus_y(n, (X), xn_over_d((X), f, 0x10000))
// ~~~ End section 716 ~~~

// ~~~ Section 725 ~~~
#define new_hlist(X) mem[nucleus((X))].integer // the translation of an mlist
// ~~~ End section 725 ~~~

// ~~~ Section 731 ~~~
#define choose_mlist(X) p = X(q); X(q) = null
// ~~~ End section 731 ~~~

// ~~~ Section 1151 ~~~
#define fam_in_range (cur_fam >= 0 && cur_fam < 16)
// ~~~ End section 1151 ~~~

// ~~~ Section 1381 ~~~
pointer new_noad();

// create a style node
pointer new_style(small_number s);

// create a choice node
pointer new_choice();

// construct the bar for a fraction
pointer fraction_rule(scaled t);

pointer overbar(pointer b, scaled k, scaled t);

pointer var_delimiter(pointer d, small_number s, scaled v);

pointer char_box(internal_font_number f, quarterword c);

pointer rebox(pointer b, scaled w);

pointer math_glue(pointer g, scaled m);

void math_kern(pointer p, scaled m);

void flush_math();

void mlist_to_hlist();

void init_math();

void start_eq_no();

void scan_math(pointer p);

void set_math_char(int c);

void math_limit_switch();

void math_radical();

void math_ac();

void append_choices();

void build_choices();

void sub_sup();

void math_fraction();

pointer fin_mlist(pointer p);

void math_left_right();

void after_math();

void resume_after_display();
#endif
// ~~~ End section 1381 ~~~
