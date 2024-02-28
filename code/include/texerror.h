// ~~~ Section 73 ~~~
// ~~~ Start file |texerror.h|, 1381 ~~~
#ifndef ERROR_H_
#define ERROR_H_

#include "io.h"
// ~~~ End section 1381 ~~~

#define print_err(X) print_nl("! "); print((X))
// ~~~ End section 73 ~~~

// ~~~ Section 79 ~~~
#define hlp1(X) help_line[0] = (X)
#define hlp2(X) help_line[1] = (X); hlp1
#define hlp3(X) help_line[2] = (X); hlp2
#define hlp4(X) help_line[3] = (X); hlp3
#define hlp5(X) help_line[4] = (X); hlp4
#define hlp6(X) help_line[5] = (X); hlp5
#define help0   help_ptr = 0       // sometimes there might be no help
#define help1   help_ptr = 1; hlp1 // use this with one help line
#define help2   help_ptr = 2; hlp2 // use this with two help lines
#define help3   help_ptr = 3; hlp3 // use this with three help lines
#define help4   help_ptr = 4; hlp4 // use this with four help lines
#define help5   help_ptr = 5; hlp5 // use this with five help lines
#define help6   help_ptr = 6; hlp6 // use this with six help lines
// ~~~ End section 79 ~~~

// ~~~ Section 96 ~~~
#define check_interrupt               \
    do {                              \
        if (interrupt != 0) {         \
            pause_for_instructions(); \
        }                             \
    } while (0)
// ~~~ End section 96 ~~~

// ~~~ Section 1381 ~~~
void error();

void int_error(int n);

void normalize_selector();

void succumb();
// prints |s| and that's it
void fatal_error(char *s);

// stop due to finiteness
void overflow(char *s, int n);

// consistency check violated; |s| tells where
void confusion(char *s);

void pause_for_instructions();

void mu_error();

void give_err_help();

void clear_for_error_prompt();
#endif
// ~~~ End section 1381 ~~~
