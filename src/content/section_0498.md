# Section 498

A condition is started when the *expand* procedure encounters an *IF_TEST* command; in that case *expand* reduces to *conditional*, which is a recursive procedure.

```c parser/conditional.c
void conditional() {
    bool b = false;  // is the condition true?
    unsigned char r; // relation to be evaluated
    int m, n;        // to be tested against the second operand
    pointer p, q;    // for traversing token lists in \\ifx} tests
    small_number save_scanner_status; // |scanner_status| upon entry
    pointer save_cond_ptr;            // |cond_ptr| corresponding to this conditional
    small_number this_if;             // type of this conditional

    // << Push the condition stack >>
    save_cond_ptr = cond_ptr;
    this_if = cur_chr;
    // << Either process \ifcase or set |b| to the value of a boolean condition >>
    if (tracing_commands > 1) {
        // << Display the value of |b| >>
    }
    if (b) {
        change_if_limit(ELSE_CODE, save_cond_ptr);
        return; // wait for \else} or \fi
    }
    // << Skip to \else or \fi, then |goto common_ending| >>

common_ending:
    if (cur_chr == FI_CODE) {
        // << Pop the condition stack >>
    }
    else {
        if_limit = FI_CODE; // wait for \fi
    }
}
```
