// ~~~ Section 57 ~~~
// ~~~ Start file |basic_printing.c|, 1382 ~~~
#include <math.h>
#include <string.h>
#include "datastructures.h"
#include "io.h"
// ~~~ End section 1382 ~~~

// prints an end-of-line
void print_ln() {
    switch(selector) {
    case TERM_AND_LOG:
        wterm_cr;
        wlog_cr;
        term_offset = 0;
        file_offset = 0;
        break;
    
    case LOG_ONLY:
        wlog_cr;
        file_offset = 0;
        break;

    case TERM_ONLY:
        wterm_cr;
        term_offset = 0;
        break;
    
    case NO_PRINT:
    case PSEUDO:
    case NEW_STRING:
        do_nothing;
        break;
    
    default:
        write_ln(write_file[selector], "");
    }
    // |tally| is not affected
}
// ~~~ End section 57 ~~~

// ~~~ Section 58 ~~~
// prints a single character
void print_char(ASCII_code s) {
    // Section 244 (first condition)
    if (s == new_line_char && selector < PSEUDO) {
        print_ln();
        return;
    }
    switch(selector) {
    case TERM_AND_LOG:
        wterm_char(XCHR[s]);
        incr(term_offset);
        if (term_offset == MAX_PRINT_LINE) {
            wterm_cr;
            term_offset = 0;
        }
        wlog_char(XCHR[s]);
        incr(file_offset);
        if (file_offset == MAX_PRINT_LINE) {
            wlog_cr;
            file_offset = 0;
        }
        break;

    case LOG_ONLY:
        wlog_char(XCHR[s]);
        incr(file_offset);
        if (file_offset == MAX_PRINT_LINE) {
            print_ln();
        }
        break;

    case TERM_ONLY:
        wterm_char(XCHR[s]);
        incr(term_offset);
        if (term_offset == MAX_PRINT_LINE) {
            print_ln();
        }
        break;
        
    case NO_PRINT:
        do_nothing;
        break;

    case PSEUDO:
        if (tally < trick_count) {
            trick_buf[tally % ERROR_LINE] = s;
        }
        break;

    case NEW_STRING:
        // we drop characters if the string space is full
        if (pool_ptr < POOL_SIZE) {
            append_char(s);
        }
        break;

    default:
        write_char(write_file[selector], XCHR[s]);
    }
    incr(tally);
}
// ~~~ End section 58 ~~~

// ~~~ Section 59 ~~~
void print(char *s) {
    int l = strlen(s);
    int i;
    for (i = 0; i < l; i++) {
        print_char(s[i]);
    }
}

// prints string s
void print_strnumber(int s) {
    pool_pointer j; // current character code position
    int nl;         // new-line character to restore

    if (s >= str_ptr) {
        print("???"); // This can't happen.
    }
    else if (s < 256) {
        if (selector > PSEUDO) {
            print_char(s);
            return;
            // internal strings are not expanded
        }
        // Section 244 (first condition)
        if (s == new_line_char && selector < PSEUDO) {
            print_ln();
            return;
        }
        nl = new_line_char;
        new_line_char = -1; // temporary disable new-line character
        j = str_start[s];
        while (j < str_start[s + 1]) {
            print_char(str_pool[j]);
            incr(j);
        }
        new_line_char = nl;
        return;
    }
    j = str_start[s];
    while (j < str_start[s +1]) {
        print_char(str_pool[j]);
        incr(j);
    }
}
// ~~~ End section 59 ~~~

// ~~~ Section 60 ~~~
// prints string s
void slow_print(int s) {
    pool_pointer j; // current character code position
    if (s >= str_ptr || s < 256) {
        print_strnumber(s);
    }
    else {
        j = str_start[s];
        while (j < str_start[s + 1]) {
            print_strnumber(str_pool[j]);
            incr(j);
        }
    }
}
// ~~~ End section 60 ~~~

// ~~~ Section 62 ~~~
void print_nl(char *s) {
    if ((term_offset > 0 && odd(selector))
        || (file_offset > 0 && selector >= LOG_ONLY))
    {
        print_ln();
    }
    print(s);
}

// prints string |s| at beginning of line
void print_nl_strnumber(str_number s) {
    if ((term_offset > 0 && odd(selector))
        || (file_offset > 0 && selector >= LOG_ONLY))
    {
        print_ln();
    }
    print_strnumber(s);
}
// ~~~ End section 62 ~~~

// ~~~ Section 63 ~~~
void print_esc(char *s) {
    int c;
    // ~~~ Set variable |c| to the current escape character, 243 ~~~
    c = escape_char;
    // ~~~ End section 243 ~~~
    if (c >= 0 && c < 256) {
        print_strnumber(c);
    }
    print(s);
}

// prints escape character, then |s|
void print_esc_strnumber(str_number s) {
    int c; // the escape character code
    // ~~~ Set variable |c| to the current escape character, 243 ~~~
    c = escape_char;
    // ~~~ End section 243 ~~~
    if (c >= 0 && c < 256) {
        print_strnumber(c);
    }
    slow_print(s);
}
// ~~~ End section 63 ~~~

// ~~~ Section 64 ~~~
// prints |dig[k - 1]| ... |dig[0]|
void print_the_digs(eight_bits k) {
    while (k > 0) {
        decr(k);
        if (dig[k] < 10) {
            print_char('0' + dig[k]);
        }
        else {
            print_char('A' - 10 + dig[k]);
        }
    }
}
// ~~~ End section 64 ~~~

// ~~~ Section 65 ~~~
// prints an integer in decimal form
void print_int(int n) {
    int k = 0; // index to current digit; we assume that |n| < 10^{23}
    int m;     // used to negate |n| in possibly dangerous cases
    if (n < 0) {
        print_char('-');
        if (n > -100000000) {
            negate(n);
        }
        else {
            m = -1 - n;
            n = m / 10;
            m = (m % 10) + 1;
            k = 1;
            if (m < 10) {
                dig[0] = m;
            }
            else {
                dig[0] = 0;
                incr(n);
            }
        }
    }
    do {
        dig[k] = n % 10;
        n /= 10;
        incr(k);
    } while (n != 0);
    print_the_digs(k);
}
// ~~~ End section 65 ~~~

// ~~~ Section 66 ~~~
// prints two least significant digits
void print_two(int n) {
    n = abs(n) % 100;
    print_char('0' + (n / 10));
    print_char('0' + (n % 10));
}
// ~~~ End section 66 ~~~

// ~~~ Section 67 ~~~
// prints a positive integer in hexadecimal form
void print_hex(int n) {
    int k = 0; // index to current digit; we assume that 0 <= n < 16^{22}
    print_char('"');
    do {
        dig[k] = n % 16;
        n /= 16;
        incr(k);
    } while (n != 0);
    print_the_digs(k);
}
// ~~~ End section 67 ~~~

// ~~~ Section 69 ~~~
void print_roman_int(int n) {
    char *s = "m2d5c2l5x2v5i";
    int j = 0, k;    // mysterious indices into |s|
    int u, v = 1000; // mysterious numbers
    while(true) {
        while (n >= v) {
            print_char(s[j]);
            n -= v;
        }
        if (n <= 0) {
            break; // nonpositive input produces no output
        }
        k = j + 2;
        u = v / (s[k - 1] - '0');
        if (s[k - 1] == '2') {
            k += 2;
            u /= (s[k - 1] - '0');
        }
        if (n + u >= v) {
            print_char(s[k]);
            n += u;
        }
        else {
            j += 2;
            v /= (s[j - 1] - '0');
        }
    }
}
// ~~~ End section 69 ~~~

// ~~~ Section 70 ~~~
// prints a yet-unmade string
void print_current_string() {
    pool_pointer j; // points to current character code
    j = str_start[str_ptr];
    while (j < pool_ptr) {
        print_char(str_pool[j]);
        incr(j);
    }
}
// ~~~ End section 70 ~~~

// ~~~ Section 103 ~~~
// prints scaled real, rounded to five digits
void print_scaled(scaled s) {
    scaled delta; // amount of allowable inaccuracy
    if (s < 0) {
        // print the sign, if negative
        print_char('-');
        negate(s);
    }
    print_int(s / UNITY); // print the integer part
    print_char('.');
    s = (s % UNITY)*10 + 5;
    delta = 10;
    do {
        if (delta > UNITY) {
            s += 32768 - 50000; // round the last digit
        }
        print_char('0' + (s / UNITY));
        s = 10 * (s % UNITY);
        delta *= 10;
    } while (s > delta);
}
// ~~~ End section 103 ~~~

// ~~~ Section 114 ~~~
#ifdef DEBUG
// prints |w| in all ways
void print_word(memory_word w) {
    print_int(w.integer);
    print_char(' ');
    print_scaled(w.sc);
    print_char(' ');
    print_scaled((scaled)round(w.gr * UNITY));
    print_ln();
    print_int(hh_lh(w));
    print_char('=');
    print_int(hh_b0(w));
    print_char(':');
    print_int(hh_b1(w));
    print_char(';');
    print_int(hh_rh(w));
    print_char(' ');
    print_int(qqqq_b0(w));
    print_char(':');
    print_int(qqqq_b1(w));
    print_char(':');
    print_int(qqqq_b2(w));
    print_char(':');
    print_int(qqqq_b3(w));
}
#endif
// ~~~ End section 114 ~~~

// ~~~ Section 262 ~~~
// prints a purported control sequence
void print_cs(int p) {
    if (p < HASH_BASE) {
        // single character
        if (p >= SINGLE_BASE) {
            if (p == NULL_CS) {
                print_esc("csname");
                print_esc("endcsname");
                print_char(' ');
            }
            else {
                print_esc_strnumber(p - SINGLE_BASE);
                if (cat_code(p - SINGLE_BASE) == LETTER) {
                    print_char(' ');
                }
            }
        }
        else if (p < ACTIVE_BASE) {
            print_esc("IMPOSSIBLE.");
        }
        else {
            print_strnumber(p - ACTIVE_BASE);
        }
    }
    else if (p >= UNDEFINED_CONTROL_SEQUENCE) {
        print_esc("IMPOSSIBLE.");
    }
    else if (text(p) < 0 || text(p) >= str_ptr) {
        print_esc("NONEXISTENT.");
    }
    else {
        print_esc_strnumber(text(p));
        print_char(' ');
    }
}
// ~~~ End section 262 ~~~

// ~~~ Section 263 ~~~
// prints a control sequence
void sprint_cs(pointer p) {
    if (p < HASH_BASE) {
        if (p < SINGLE_BASE) {
            print_strnumber(p - ACTIVE_BASE);
        }
        else if (p < NULL_CS) {
            print_esc_strnumber(p - SINGLE_BASE);
        }
        else {
            print_esc("csname");
            print_esc("endcsname");
        }
    }
    else {
        print_esc_strnumber(text(p));
    }
}
// ~~~ End section 263 ~~~

// ~~~ Section 518 ~~~
void print_file_name(int n, int a, int e) {
    slow_print(a);
    slow_print(n);
    slow_print(e);
}
// ~~~ End section 518 ~~~
