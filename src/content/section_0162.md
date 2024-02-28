# Section 162: Memory layout

Some areas of *mem* are dedicated to fixed usage, since static allocation is more efficient than dynamic allocation when we can get away with it.
For example, locations *MEM_BOT* to *MEM_BOT + 3* are always used to store the specification for glue that is `0pt plus 0pt minus 0pt`.
The following macro definitions accomplish the static allocation by giving symbolic names to the fixed positions. Static variable-size nodes appear in locations *MEM_BOT* through *LO_MEM_STAT_MAX*, and static single-word nodes appear in locations *HI_MEM_STAT_MIN* through *MEM_TOP*, inclusive.
It is harmless to let *LIG_TRICK* and *GARBAGE* share the same location of *mem*.

```c include/constants.h
#define ZERO_GLUE       MEM_BOT                      // specification for 0pt plus 0pt minus 0pt
#define FIL_GLUE        (ZERO_GLUE + GLUE_SPEC_SIZE) // 0pt plus 1fil minus 0pt
#define FILL_GLUE       (FIL_GLUE + GLUE_SPEC_SIZE)  // 0pt plus 1fill minus 0pt
#define SS_GLUE         (FILL_GLUE + GLUE_SPEC_SIZE) // 0pt plus 1fil minus 1fil
#define FIL_NEG_GLUE    (SS_GLUE + GLUE_SPEC_SIZE)   // 0pt plus -1fil minus 0pt
// largest statically allocated word in the variable-size |mem|
#define LO_MEM_STAT_MAX (FIL_NEG_GLUE + GLUE_SPEC_SIZE - 1) 

#define PAGE_INS_HEAD     MEM_TOP        // list of insertion data for current page
#define CONTRIB_HEAD      (MEM_TOP - 1)  // vlist of items not yet on current page
#define PAGE_HEAD         (MEM_TOP - 2)  // vlist for current page
#define TEMP_HEAD         (MEM_TOP - 3)  // head of a temporary list of some kind
#define HOLD_HEAD         (MEM_TOP - 4)  // head of a temporary list of another kind
#define ADJUST_HEAD       (MEM_TOP - 5)  // head of adjustment list returned by |hpack|
#define ACTIVE            (MEM_TOP - 7)  // head of active list in |line_break|, needs two words
#define ALIGN_HEAD        (MEM_TOP - 8)  // head of preamble list for alignments
#define END_SPAN          (MEM_TOP - 9)  // tail of spanned - width lists
#define OMIT_TEMPLATE     (MEM_TOP - 10) // a constant token list
#define NULL_LIST         (MEM_TOP - 11) // permanently empty list
#define LIG_TRICK         (MEM_TOP - 12) // a ligature masquerading as a |CHAR_NODE|
#define GARBAGE           (MEM_TOP - 12) // used for scrap information
#define BACKUP_HEAD       (MEM_TOP - 13) // head of token list built by |scan_keyword|
#define HI_MEM_STAT_MIN   (MEM_TOP - 13) // smallest statically allocated word in the one-word |mem|
#define HI_MEM_STAT_USAGE 14             // the number of one-word nodes always present
```
