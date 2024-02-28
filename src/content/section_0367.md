# Section 367

```c << Expand a nonmacro >>=
if (tracing_commands > 1) {
    show_cur_cmd_chr();
}
switch (cur_cmd) {
case TOP_BOT_MARK:
    // << Insert the appropriate mark text into the scanner >>
    break;

case EXPAND_AFTER:
    // << Expand the token after the next token >>
    break;

case NO_EXPAND:
    // << Suppress expansion of the next token >>
    break;

case CS_NAME:
    // << Manufacture a control sequence name >>
    break;

case CONVERT:
    conv_toks();
    break; // this procedure is discussed in Part 27 below

case THE:
    ins_the_toks();
    break; // this procedure is discussed in Part 27 below

case IF_TEST:
    conditional();
    break; // this procedure is discussed in Part 28 below

case FI_OR_ELSE:
    // << Terminate the current conditional and skip to \fi >>
    break;

case INPUT:
    // << Initiate or terminate input from a file >>
    break;

default:
    // << Complain about an undefined macro >>
}
```
