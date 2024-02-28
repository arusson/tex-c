// ~~~ Section 100 ~~~
// ~~~ Start file |arithmetic.c|, 1382 ~~~
#include "tex.h"
// ~~~ End section 1382 ~~~

int half(int x) {
    int res;
    if (odd(x)) {
        res = (x + 1) / 2;
    }
    else {
        res = x / 2;
    }
    return res;
}
// ~~~ End section 100 ~~~

// ~~~ Section 102 ~~~
// converts a decimal fraction
scaled round_decimals(small_number k) {
    int a = 0; // the accumulator
    while (k > 0) {
        decr(k);
        a = (a + dig[k] * TWO) / 10;
    }
    return (a + 1) / 2;
}
// ~~~ End section 102 ~~~

// ~~~ Section 105 ~~~
scaled mult_and_add(int n, scaled x, scaled y, scaled max_answer) {
    scaled res;
    if (n < 0) {
        negate(x);
        negate(n);
    }
    if (n == 0) {
        res = y;
    }
    else if ((x <= (max_answer - y) / n)
        && (-x <= (max_answer + y) / n))
    {
        res  = n * x + y;
    }
    else {
        arith_error = true;
        res = 0;
    }
    return res;
}
// ~~~ End section 105 ~~~

// ~~~ Section 106 ~~~
scaled x_over_n(scaled x, int n) {
    bool negative = false;  // should |remainder_| be negated?
    scaled quotient;
    if (n == 0) {
        arith_error = true;
        quotient = 0;
        remainder_ = x;
    }
    else {
        if (n < 0) {
            negate(x);
            negate(n);
            negative = true;
        }
        if (x >= 0) {
            quotient = x / n;
            remainder_ = x % n;
        }
        else {
            quotient = -((-x) / n);
            remainder_ = -((-x) % n);
        }
    }
    if (negative) {
        negate(remainder_);
    }
    return quotient;
}
// ~~~ End section 106 ~~~

// ~~~ Section 107 ~~~
scaled xn_over_d(scaled x, int n, int d) {
    bool positive = true; // was |x >= 0|?
    int t, u, v;          // intermediate quantities
    scaled quotient;
    if (x < 0) {
        negate(x);
        positive = false;
    }

    t = (x % 32768) * n;
    u = (x / 32768) * n + (t / 32768);
    v = (u % d) * 32768 + (t % 32768);
    if (u / d >= 32768) {
        arith_error = true;
    }
    else {
        u = 32768 * (u / d) + (v / d);
    }
    if (positive) {
        quotient = u;
        remainder_ = v % d;
    }
    else {
        quotient = -u;
        remainder_ = -(v % d);
    }
    return quotient;
}
// ~~~ End section 107 ~~~

// ~~~ Section 108 ~~~
// compute badness, given |t >= 0|
halfword badness(scaled t, scaled s) {
    int r; // approximation to \alpha*t/s, where alpha^3\approx 100*2^{18}
    halfword badness;
    if (t == 0) {
        badness = 0;
    }
    else if (s <= 0) {
        badness = INF_BAD;
    }
    else {
        if (t <= 7230584) {
            r = (t * 297) / s; // 297^3 = 99.94 * 2^{18}
        }
        else if (s >= 1663497) {
            r = t / (s / 297);
        }
        else {
            r = t;
        }

        if (r > 1290) {
            badness = INF_BAD; // 1290^3 < 2^{31} < 1291^3
        }
        else {
            badness = (r*r*r + 0x20000) / 0x40000;
        }
    } // that was r^3/2^{18}, rounded to the nearest integer
    return badness;
}
// ~~~ End section 108 ~~~
