# Section 366: Expanding the next token

Only a dozen or so command codes *> MAX_COMMAND* can possibly be returned by *get_next*;
in increasing order, they are *UNDEFINED_CS*, *EXPAND_AFTER*, *NO_EXPAND*, *INPUT*, *IF_TEST*, *FI_OR_ELSE*, *CS_NAME*, *CONVERT*, *THE*, *TOP_BOT_MARK*, *CALL*, *LONG_CALL*, *OUTER_CALL*, *LONG_OUTER_CALL*, and *END_TEMPLATE*.

The *expand* subroutine is used when *cur_cmd* $>$ *MAX_COMMAND*.
It removes a "call" or a conditional or one of the other special operations just listed.
It follows that *expand* might invoke itself recursively.
In all cases, *expand* destroys the current token, but it sets things up so that the next *get_next* will deliver the appropriate next token.
The value of *cur_tok* need not be known when *expand* is called.

Since several of the basic scanning routines communicate via global variables, their values are saved as local variables of *expand* so that recursive calls don't invalidate them.

```c parser/expand_next_token.c
// << Start file |expand_next_token.c| >>

void expand() {
    halfword t;      // token that is being ``expanded after''
    pointer p, q, r; // for list manipulation
    int j;           // index into |buffer|
    int cv_backup;   // to save the global quantity |cur_val|
    small_number cvl_backup, radix_backup, co_backup; // to save |cur_val_level|, etc.
    pointer backup_backup; // to save |link(BACKUP_HEAD)|
    small_number save_scanner_status; // temporary storage of |scanner_status|
    
    cv_backup = cur_val;
    cvl_backup = cur_val_level;
    radix_backup = radix;
    co_backup = cur_order;
    backup_backup = link(BACKUP_HEAD);
    if (cur_cmd < CALL) {
        // << Expand a nonmacro >>
    }
    else if (cur_cmd < END_TEMPLATE) {
        macro_call();
    }
    else {
        // << Insert a token containing |FROZEN_ENDV| >>
    }
    cur_val = cv_backup;
    cur_val_level = cvl_backup;
    radix = radix_backup;
    cur_order = co_backup;
    link(BACKUP_HEAD) = backup_backup;
}
```
