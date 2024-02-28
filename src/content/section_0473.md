# Section 473

Now we can't postpone the difficulties any longer; we must bravely tackle *scan_toks*. This function returns a pointer to the tail of a new token list, and it also makes *def_ref* point to the reference count at the head of that list.

There are two boolean parameters, *macro_def* and *xpand*.
If *macro_def* is true, the goal is to create the token list for a macro definition;
otherwise the goal is to create the token list for some other $\TeX$ primitive:
`\mark`, `\output`, `\everypar`, `\lowercase`, `\uppercase`, `\message`, `\errmessage`, `\write`, or `\special`.
In the latter cases a left brace must be scanned next;
this left brace will not be part of the token list, nor will the matching right brace that comes at the end.
If *xpand* is false, the token list will simply be copied from the input using *get_token*.
Otherwise all expandable tokens will be expanded until unexpandable tokens are left, except that the results of expanding '`\the`' are not expanded further.
If both *macro_def* and *xpand* are true, the expansion applies only to the macro body (i.e., to the material following the first *LEFT_BRACE* character).

The value of *cur_cs* when *scan_toks* begins should be the *eqtb* address of the control sequence to display in "runaway" error messages.

```c parser/build_tokens.c
pointer scan_toks(bool macro_def, bool xpand) {
    halfword t;          // token representing the highest parameter number
    halfword s;          // saved token
    pointer p;           // tail of the token list being built
    pointer q;           // new node being added to the token list via |store_new_token|
    halfword unbalance;  // number of unmatched left braces
    halfword hash_brace; // possible '#{' token
    if (macro_def) {
        scanner_status = DEFINING;
    }
    else {
        scanner_status = ABSORBING;
    }
    warning_index = cur_cs;
    def_ref = get_avail();
    token_ref_count(def_ref) = null;
    p = def_ref;
    hash_brace = 0;
    t = ZERO_TOKEN;
    if (macro_def) {
        // << Scan and build the parameter part of the macro definition >>
    }
    else {
        scan_left_brace(); // remove the compulsory left brace
    }
    // << Scan and build the body of the token list; |goto found| when finished >>
found:
    scanner_status = NORMAL;
    if (hash_brace != 0) {
        store_new_token(hash_brace);
    }
    return p;
}
```
