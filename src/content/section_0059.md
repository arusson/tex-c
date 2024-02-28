# Section 59

An entire string is output by calling *print*.
Note that if we are outputting the single standard ASCII character `c`, we could call *print('c')*, since `'c'` = 99 is the number of a single-character string, as explained above.
But *print_char('c')* is quicker, so $\TeX$ goes directly to the *print_char* routine when it knows that this is safe.
(The present implementation assumes that it is always safe to print a visible ASCII character.)

> ![NOTE]
> The original *print* procedure has been renamed *print_strnumber*.
> The *print* function is used to print to terminal or files (depending of the `selector`) only strings that are hardcoded in the source.
> Those have the null terminator, so it is safe to use.

```c io/basic_printing.c
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
```
