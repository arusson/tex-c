// ~~~ Section 769 ~~~
// ~~~ Start file |alignment.h|, 1381 ~~~
#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define u_part(X)     mem[(X) + HEIGHT_OFFSET].integer // pointer to <u_j> token list
#define v_part(X)     mem[(X) + DEPTH_OFFSET].integer  // pointer to <v_j> token list
#define extra_info(X) info(X + LIST_OFFSET)            // info to remember during template
// ~~~ End section 769 ~~~

// ~~~ Section 770 ~~~
#define preamble link(ALIGN_HEAD) // the current preamble list
// ~~~ End section 770 ~~~

// ~~~ Section 1381 ~~~
void init_align();

void align_peek();

void init_row();

void init_span(pointer p);

void init_col();

bool fin_col();

void fin_row();

void fin_align();
#endif
// ~~~ End section 1381 ~~~
