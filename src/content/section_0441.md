# Section 441

```c << Get the next non-blank non-sign token; set |negative| appropriately >>=
negative = false;
do {
    // << Get the next non-blank non-call token >>
    if (cur_tok == OTHER_TOKEN + '-') {
        negative = !negative;
        cur_tok = OTHER_TOKEN + '+';
    }
} while (cur_tok == OTHER_TOKEN + '+');
```
