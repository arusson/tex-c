# Section 389

After parameter scanning is complete, the parameters are moved to the *param_stack*.
Then the macro body is fed to the scanner; in other words, *macro_call* places the defined text of the control sequence at the top of $\TeX$'s input stack, so that *get_next* will proceed to read it next.

The global variable *cur_cs* contains the *eqtb* address of the control sequence being expanded, when *macro_call* begins.
If this control sequence has not been declared `\long`, i.e., if its command code in the *eq_type* field is not *LONG_CALL* or *LONG_OUTER_CALL*, its parameters are not allowed to contain the control sequence `\par`.
If an illegal `\par` appears, the macro call is aborted, and the `\par` will be rescanned.

```c parser/expand_next_token.c
// invokes a user-defined control sequence
void macro_call() {
    pointer r;                 // current node in the macro's token list
    pointer p = null;          // current node in parameter token list being built
    pointer q;                 // new node being put into the token list
    pointer s;                 // backup pointer for parameter matching
    pointer t;                 // cycle pointer for backup recovery
    pointer u, v;              // auxiliary pointers for backup recovery
    pointer rbrace_ptr = null; // one step before the last |RIGHT_BRACE| token
    small_number n;            // the number of parameters scanned
    halfword unbalance;        // unmatched left braces in current parameter
    halfword m = 0;            // the number of tokens or groups (usually)
    pointer ref_count;         // start of the token list
    small_number save_scanner_status; // |scanner_status| upon entry
    pointer save_warning_index;       // |warning_index| upon entry
    ASCII_code match_chr;             // character used in parameter
    
    save_scanner_status = scanner_status;
    save_warning_index = warning_index;
    warning_index = cur_cs;
    ref_count = cur_chr;
    r = link(ref_count);
    n = 0;
    if (tracing_macros > 0) {
        // << Show the text of the macro being expanded >>
    }
    if (info(r) != END_MATCH_TOKEN) {
        // << Scan the parameters and make |link(r)| point to the macro body; but |return| if an illegal \par is detected >>
    }
    // << Feed the macro body and its parameters to the scanner >>
end:
    scanner_status = save_scanner_status;
    warning_index = save_warning_index;
}
```
