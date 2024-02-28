// ~~~ Section 1341 ~~~
// ~~~ Start file |extensions.h|, 1381 ~~~
#ifndef EXTENSIONS_H_
#define EXTENSIONS_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define what_lang(X)    link((X) + 1)    // language number, in the range |0 .. 255|
#define what_lhm(X)     type((X) + 1)    // minimum left fragment, in the range |1 .. 63|
#define what_rhm(X)     subtype((X) + 1) // minimum right fragment, in the range |1 .. 63|
#define write_tokens(X) link((X) + 1)    // reference count of token list to write
#define write_stream(X) info((X) + 1)    // stream number (0 to 17)
#define open_name(X)    link((X) + 1)    // string number of file name to open
#define open_area(X)    info((X) + 2)    // string number of file area for |open_name|
#define open_ext(X)     link((X) + 2)    // string number of file extension for |open_name|
// ~~~ End section 1341 ~~~

// ~~~ Section 1362 ~~~
#define adv_past(X)                          \
    do {                                     \
        if (subtype((X)) == LANGUAGE_NODE) { \
            cur_lang = what_lang((X));       \
            l_hyf = what_lhm((X));           \
            r_hyf = what_rhm((X));           \
        }                                    \
    } while(0)
// ~~~ End section 1362 ~~~

// ~~~ Section 1381 ~~~
void do_extension();

void new_whatsit(small_number s, small_number w);
#endif
// ~~~ End section 1381 ~~~
