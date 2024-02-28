# Section 445

> ![NOTE]
> *INFINITY* is already defined in library header *math.h*, so it is called *INFINITY_* here.

```c include/constants.h
#define INFINITY_     0x7fffffff           // the largest positive value that TeX knows
#define ZERO_TOKEN    (OTHER_TOKEN + '0')  // zero, the smallest digit
#define A_TOKEN       (LETTER_TOKEN + 'A') // the smallest special hex digit
#define OTHER_A_TOKEN (OTHER_TOKEN + 'A')  // special hex digit of type |OTHER_CHAR|
```

```c << Accumulate the constant until |cur_tok| is not a suitable digit >>=
while(true) {
    if (cur_tok < ZERO_TOKEN + radix
        && cur_tok >= ZERO_TOKEN
        && cur_tok <= ZERO_TOKEN + 9)
    {
        d = cur_tok - ZERO_TOKEN;
    }
    else if (radix == 16) {
        if (cur_tok <= A_TOKEN + 5 && cur_tok >= A_TOKEN) {
            d = cur_tok - A_TOKEN + 10;
        }
        else if (cur_tok <= OTHER_A_TOKEN + 5 && cur_tok >= OTHER_A_TOKEN) {
            d = cur_tok - OTHER_A_TOKEN + 10;
        }
        else {
            break; // Goto done
        }
    }
    else {
        break; // Goto done
    }
    vacuous = false;
    if (cur_val >= m
        && (cur_val > m || d > 7 || radix != 10))
    {
        if (ok_so_far) {
            print_err("Number too big");
            help2("I can only go up to 2147483647='17777777777=\"7FFFFFFF,")
                ("so I'm using that number instead of yours.");
            error();
            cur_val = INFINITY_;
            ok_so_far = false;
        }
    }
    else {
        cur_val = cur_val * radix + d;
    }
    get_x_token();
}
// done:
```
