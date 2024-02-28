# Section 323

Here is a procedure that starts a new level of token-list input, given a token list *p* and its type *t*.
If *t = MACRO*, the calling routine should set *name* and *loc*.

```c include/datastructures.h
#define back_list(X) begin_token_list((X), BACKED_UP) // backs up a simple token list
#define ins_list(X)  begin_token_list((X), INSERTED)  // inserts a simple token list
```

```c datastructures/stack.c
void begin_token_list(pointer p, quarterword t) {
    push_input;
    state = TOKEN_LIST;
    start = p;
    token_type = t;
    if (t >= MACRO) {
        // the token list starts with a reference count
        add_token_ref(p);
        if (t == MACRO) {
            param_start = param_ptr;
        }
        else {
            loc = link(p);
            if (tracing_macros > 1) {
                begin_diagnostic();
                print_nl("");
                switch (t) {
                case MARK_TEXT:
                    print_esc("mark");
                    break;
                
                case WRITE_TEXT:
                    print_esc("write");
                    break;
                
                default:
                    print_cmd_chr(ASSIGN_TOKS, t - OUTPUT_TEXT + OUTPUT_ROUTINE_LOC);
                }
                print("->");
                token_show(p);
                end_diagnostic(false);
            }
        }
    }
    else {
        loc = p;
    }
}
```
