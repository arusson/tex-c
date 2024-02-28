# Section 210

The remaining command codes are extra special, since they cannot get through $\TeX$'s scanner to the main control routine.
They have been given values higher than *MAX_COMMAND* so that their special nature is easily discernible.
The "expandable" commands come first.

```c include/constants.h
#define UNDEFINED_CS    (MAX_COMMAND + 1)  // initial state of most |eq_type| fields
#define EXPAND_AFTER    (MAX_COMMAND + 2)  // special expansion (\expandafter)
#define NO_EXPAND       (MAX_COMMAND + 3)  // special nonexpansion (\noexpand)
#define INPUT           (MAX_COMMAND + 4)  // input a source file (\input, \endinput)
#define IF_TEST         (MAX_COMMAND + 5)  // conditional text (\if, \ifcase, etc.)
#define FI_OR_ELSE      (MAX_COMMAND + 6)  // delimiters for conditionals (\else, etc.)
#define CS_NAME         (MAX_COMMAND + 7)  // make a control sequence from tokens (\csname)
#define CONVERT         (MAX_COMMAND + 8)  // convert to text (\number, \string, etc.)
#define THE             (MAX_COMMAND + 9)  // expand an internal quantity (\the)
#define TOP_BOT_MARK    (MAX_COMMAND + 10) // inserted mark (\topmark, etc.)
#define CALL            (MAX_COMMAND + 11) // non-long, non-outer control sequence
#define LONG_CALL       (MAX_COMMAND + 12) // long, non-outer control sequence
#define OUTER_CALL      (MAX_COMMAND + 13) // non-long, outer control sequence
#define LONG_OUTER_CALL (MAX_COMMAND + 14) // long, outer control sequence
#define END_TEMPLATE    (MAX_COMMAND + 15) // end of an alignment template
#define DONT_EXPAND     (MAX_COMMAND + 16) // the following token was marked by \noexpand
#define GLUE_REF        (MAX_COMMAND + 17) // the equivalent points to a glue specification
#define SHAPE_REF       (MAX_COMMAND + 18) // the equivalent points to a parshape specification
#define BOX_REF         (MAX_COMMAND + 19) // the equivalent points to a box node, or is |null|
#define DATA            (MAX_COMMAND + 20) // the equivalent is simply a halfword number
```
