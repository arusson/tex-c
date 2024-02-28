// ~~~ Section 105 ~~~
// ~~~ Start file |arithmetic.h|, 1381 ~~~
#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "tex.h"
// ~~~ End section 1381 ~~~

#define nx_plus_y(A, B, C)  mult_and_add((A), (B), (C), 0x3fffffff)
#define mult_integers(A, B) mult_and_add((A), (B), 0, 0x7fffffff)
// ~~~ End section 105 ~~~

// ~~~ Section 109 ~~~
#define set_glue_ratio_zero(X) (X) = 0.0 // store the representation of zero ratio
#define set_glue_ratio_one(X)  (X) = 1.0 // store the representation of unit ratio
// ~~~ End section 109 ~~~

// ~~~ Section 1381 ~~~
int half(int x);

// converts a decimal fraction
scaled round_decimals(small_number k);

scaled mult_and_add(int n, scaled x, scaled y, scaled max_answer);

scaled x_over_n(scaled x, int n);

scaled xn_over_d(scaled x, int n, int d);

// compute badness, given |t >= 0|
halfword badness(scaled t, scaled s);
#endif
// ~~~ End section 1381 ~~~
