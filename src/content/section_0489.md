# Section 489

Conditions can be inside conditions, and this nesting has a stack that is independent of the *save_stack*.

Four global variables represent the top of the condition stack:
*cond_ptr* points to pushed-down entries, if any;
*if_limit* specifies the largest code of a *FI_OR_ELSE* command that is syntactically legal;
*cur_if* is the name of the current type of conditional;
and *if_line* is the line number at which it began.

If no conditions are currently in progress, the condition stack has the special state *cond_ptr = null*, *if_limit = NORMAL*, *cur_if = 0*, *if_line = 0*.
Otherwise *cond_ptr* points to a two-word node; the *type*, *subtype*, and *link* fields of the first word contain *if_limit*, *cur_if*, and *cond_ptr* at the next level, and the second word contains the corresponding *if_line*.

```c include/constants.h
#define IF_NODE_SIZE 2 // number of words in stack entry for conditionals
#define IF_CODE      1 // code for \if... being evaluated
#define FI_CODE      2 // code for \f
#define ELSE_CODE    3 // code for \else
#define OR_CODE      4 // code for \or
```

```c include/conditional.h
// << Start file |conditional.h| >>

#define if_line_field(X) mem[(X) + 1].integer
```

```c << Global variables >>+=
pointer cond_ptr;    // top of the condition stack
int if_limit;        // upper bound on |fi_or_else| codes
small_number cur_if; // type of conditional being worked on
int if_line;         // line where that conditional began
```
