# Section 382

A control sequence that has been `\def`'ed by the user is expanded by $\TeX$'s *macro_call* procedure.

Before we get into the details of *macro_call*, however, let's consider the treatment of primitives like `\topmark`, since they are essentially macros without parameters.
The token lists for such marks are kept in a global array of five pointers; we refer to the individual entries of this array by symbolic names *top_mark*, etc.
The value of *top_mark* is either *null* or a pointer to the reference count of a token list.

```c include/constants.h
#define TOP_MARK_CODE         0 // the mark in effect at the previous page break
#define FIRST_MARK_CODE       1 // the first mark between |top_mark| and |bot_mark|
#define BOT_MARK_CODE         2 // the mark in effect at the current page break
#define SPLIT_FIRST_MARK_CODE 3 // the first mark found by \vsplit
#define SPLIT_BOT_MARK_CODE   4 // the last mark found by \vsplit
```

```c include/parser.h
#define top_mark         cur_mark[TOP_MARK_CODE]
#define first_mark       cur_mark[FIRST_MARK_CODE]
#define bot_mark         cur_mark[BOT_MARK_CODE]
#define split_first_mark cur_mark[SPLIT_FIRST_MARK_CODE]
#define split_bot_mark   cur_mark[SPLIT_BOT_MARK_CODE]
```

```c << Global variables >>+=
pointer cur_mark[SPLIT_BOT_MARK_CODE + 1]; // token lists for marks
```
