// ~~~ Section 532 ~~~
// ~~~ Start file |dvi.h|, 1381 ~~~
#ifndef DVI_H_
#define DVI_H_

#include "io.h"
#include "parser.h"
// ~~~ End section 1381 ~~~

#define ensure_dvi_open                                            \
    do {                                                           \
        if (output_file_name == 0) {                               \
            if (job_name == 0) {                                   \
                open_log_file();                                   \
            }                                                      \
            pack_job_name(DVI_EXT);                                \
            while (!b_open_out(&dvi_file)) {                        \
                prompt_file_name("file name for output", DVI_EXT); \
            }                                                      \
            output_file_name = make_name_string();                 \
        }                                                          \
    } while (0)
// ~~~ End section 532 ~~~

// ~~~ Section 598 ~~~
#define dvi_out(X)                  \
    do {                            \
        dvi_buf[dvi_ptr] = (X);     \
        incr(dvi_ptr);              \
        if (dvi_ptr == dvi_limit) { \
            dvi_swap();             \
        }                           \
    } while (0)
// ~~~ End section 598 ~~~

// ~~~ Section 605 ~~~
#define location(X) mem[(X) + 2].integer // `DVI` byte number for a movement command
// ~~~ End section 605 ~~~

// ~~~ Section 616 ~~~
#define synch_h                              \
    do {                                     \
        if (cur_h != dvi_h) {                \
            movement(cur_h - dvi_h, RIGHT1); \
            dvi_h = cur_h;                   \
        }                                    \
    } while (0)


#define synch_v                             \
    do {                                    \
        if (cur_v != dvi_v) {               \
            movement(cur_v - dvi_v, DOWN1); \
            dvi_v = cur_v;                  \
        }                                   \
    } while (0)
// ~~~ End section 616 ~~~

// ~~~ Section 625 ~~~
#define vet_glue(X)                      \
    do {                                 \
        glue_temp = (X);                 \
        if (glue_temp > BILLION) {       \
            glue_temp = BILLION;         \
        }                                \
        else if (glue_temp < -BILLION) { \
            glue_temp = -BILLION;        \
        }                                \
    } while (0)
// ~~~ End section 625 ~~~

// ~~~ Section 1381 ~~~
void write_dvi(int a, int b);

void dvi_swap();

void dvi_four(int x);

void dvi_font_def(internal_font_number f);

void movement(scaled w, eight_bits o);

void vlist_out();

// output the box |p|
void ship_out(pointer p);

void out_what(pointer p);
#endif
// ~~~ End section 1381 ~~~
