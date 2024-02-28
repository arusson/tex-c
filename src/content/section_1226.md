# Section 1226

The token-list parameters, `\output` and `\everypar`, etc., receive their values in the following way.
(For safety's sake, we place an enclosing pair of braces around an `\output` list.)

```c << Assignments >>+=
case TOKS_REGISTER:
case ASSIGN_TOKS:
    q = cur_cs;
    if (cur_cmd == TOKS_REGISTER) {
        scan_eight_bit_int();
        p = TOKS_BASE + cur_val;
    }
    else {
        p = cur_chr; // |p = EVERY_PAR_LOC| or |OUTPUT_ROUTINE_LOC| or...
    }
    scan_optional_equals();
    // << Get the next non-blank non-relax non-call token >>
    if (cur_cmd != LEFT_BRACE) {
        // << If the right-hand side is a token parameter or token register, finish the assignment and |goto done| >>
    }
    back_input();
    cur_cs = q;
    q = scan_toks(false, false);
    if (link(def_ref) == null) {
         // empty list: revert to the default
        define(p, UNDEFINED_CS, null);
        free_avail(def_ref);
    }
    else {
        if (p == OUTPUT_ROUTINE_LOC) {
            // enclose in curlies
            link(q) = get_avail();
            q = link(q);
            info(q) = RIGHT_BRACE_TOKEN + '}';
            q = get_avail();
            info(q) = LEFT_BRACE_TOKEN + '{';
            link(q) = link(def_ref);
            link(def_ref) = q;
        }
        define(p, CALL, def_ref);
    }
    break;
```
