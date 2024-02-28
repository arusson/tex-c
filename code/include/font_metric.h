// ~~~ Section 545 ~~~
// ~~~ Start file |font_metric.h|, 1381 ~~~
#ifndef FONT_METRIC_H_
#define FONT_METRIC_H_

#include "datastructures.h"
#include "texerror.h"
// ~~~ End section 1381 ~~~

#define skip_byte(X) qqqq_b0((X))
#define next_char(X) qqqq_b1((X))
#define op_byte(X)   qqqq_b2((X))
#define rem_byte(X)  qqqq_b3((X))
// ~~~ End section 545 ~~~

// ~~~ Section 546 ~~~
#define ext_top(X) qqqq_b0((X)) // |top| piece in a recipe
#define ext_mid(X) qqqq_b1((X)) // |mid| piece in a recipe
#define ext_bot(X) qqqq_b2((X)) // |bot| piece in a recipe
#define ext_rep(X) qqqq_b3((X)) // |rep| piece in a recipe
// ~~~ End section 546 ~~~

// ~~~ Section 554 ~~~
#define char_info(X,Y)   font_info[char_base[(X)] + (Y)]
#define char_width(X,Y)  font_info[width_base[(X)] + qqqq_b0((Y))].sc
#define char_exists(X)   (qqqq_b0((X)) > MIN_QUARTERWORD)
#define char_italic(X,Y) font_info[italic_base[(X)] + qqqq_b2((Y))/4].sc
#define height_depth(X)  qqqq_b1((X))
#define char_height(X,Y) font_info[height_base[(X)] + (Y) / 16].sc
#define char_depth(X,Y)  font_info[depth_base[(X)] + (Y) % 16].sc
#define char_tag(X)      (qqqq_b2((X)) % 4)
// ~~~ End section 554 ~~~

// ~~~ Section 557 ~~~
#define char_kern(X,Y)        (font_info[kern_base[X] + 256*op_byte((Y)) + rem_byte((Y))].sc)
// beginning of lig/kern program:
#define lig_kern_start(X,Y)   (lig_kern_base[(X)] + rem_byte((Y))) 
#define lig_kern_restart(X,Y) (lig_kern_base[(X)] + 256*op_byte((Y)) + rem_byte((Y)) + 32768 - KERN_BASE_OFFSET)
// ~~~ End section 557 ~~~

// ~~~ Section 558 ~~~
#define param(X,Y)       (font_info[(X) + param_base[(Y)]].sc)
#define slant(X)         param(SLANT_CODE,(X))         // slant to the right, per unit distance upward
#define space(X)         param(SPACE_CODE,(X))         // normal space between words
#define space_stretch(X) param(SPACE_STRETCH_CODE,(X)) // stretch between words
#define space_shrink(X)  param(SPACE_SHRINK_CODE,(X))  // shrink between words
#define x_height(X)      param(X_HEIGHT_CODE,(X))      // one ex
#define quad(X)          param(QUAD_CODE,(X))          // one em
#define extra_space(X)   param(EXTRA_SPACE_CODE,(X))   // additional space at end of sentence
// ~~~ End section 558 ~~~

// ~~~ Section 560 ~~~
#define abort goto bad_tfm // do this when the `TFM` data is wrong
// ~~~ End section 560 ~~~

// ~~~ Section 561 ~~~
#define start_font_error_message                  \
    do {                                          \
        print_err("Font ");                       \
        sprint_cs(u);                             \
        print_char('=');                          \
        print_file_name(nom, aire, EMPTY_STRING); \
        if (s >= 0) {                             \
            print(" at ");                        \
            print_scaled(s);                      \
            print("pt");                          \
        }                                         \
        else if (s != -1000) {                    \
            print(" scaled ");                    \
            print_int(-s);                        \
        }                                         \
    } while (0)
// ~~~ End section 561 ~~~

// ~~~ Section 564 ~~~
#define fget(X)                \
    do {                       \
        (X) = fgetc(tfm_file); \
        if (feof(tfm_file)) {  \
            abort;             \
        }                      \
    } while (0)

#define read_sixteen(X) \
    fget(temp);         \
    if (temp > 127) {   \
        abort;          \
    }                   \
    fget((X));          \
    (X) += temp*256

#define store_four_quarters(X) \
    fget(a);                   \
    qqqq_b0(qw) = a;           \
    fget(b);                   \
    qqqq_b1(qw) = b;           \
    fget(c);                   \
    qqqq_b2(qw) = c;           \
    fget(d);                   \
    qqqq_b3(qw) = d;           \
    (X) = qw
// ~~~ End section 564 ~~~

// ~~~ Section 570 ~~~
#define check_byte_range(X)         \
    do {                            \
        if ((X) < bc || (X) > ec) { \
            abort;                  \
        }                           \
    } while (0)

#define current_character_being_worked_on (k + bc - fmem_ptr)
// ~~~ End section 570 ~~~

// ~~~ Section 571 ~~~
#define store_scaled(X)                                      \
    do {                                                     \
        fget(a);                                             \
        fget(b);                                             \
        fget(c);                                             \
        fget(d);                                             \
        sw = (((((d*z) / 256) + (c*z)) / 256) + (b*z))/beta; \
        if (a == 0) {                                        \
            (X) = sw;                                        \
        }                                                    \
        else if (a == 255) {                                 \
            (X) = sw - alpha;                                \
        }                                                    \
        else {                                               \
            abort;                                           \
        }                                                    \
    } while (0)
// ~~~ End section 571 ~~~

// ~~~ Section 573 ~~~
#define check_existence(X)                              \
    do {                                                \
        check_byte_range((X));                          \
        qw = char_info(f, (X)); /* N.B.: not |qi(X)| */ \
        if (!char_exists(qw)) {                         \
            abort;                                      \
        }                                               \
    } while (0)
// ~~~ End section 573 ~~~

// ~~~ Section 1381 ~~~
// input a `TFM` file
internal_font_number read_font_info(pointer u, str_number nom, str_number aire, scaled s);

void char_warning(internal_font_number f, eight_bits c);

pointer new_character(internal_font_number f, eight_bits c);

#endif
// ~~~ End section 1381 ~~~
