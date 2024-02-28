# Section 222

Many locations in *eqtb* have symbolic names.
The purpose of the next paragraphs is to define these names, and to set up the initial values of the equivalents.

In the first region we have 256 equivalents for "active characters" that act as control sequences, followed by 256 equivalents for single-character control sequences.

Then comes region 2, which corresponds to the hash table that we will define later.
The maximum address in this region is used for a dummy control sequence that is perpetually undefined.
There also are several locations for control sequences that are perpetually defined (since they are used in error recovery).

```c include/constants.h
#define ACTIVE_BASE                1                                // beginning of region 1, for active character equivalents
#define SINGLE_BASE                (ACTIVE_BASE + 256)              // equivalents of one-character control sequences
#define NULL_CS                    (SINGLE_BASE + 256)              // equivalent of \csname\endcsname
#define HASH_BASE                  (NULL_CS + 1)                    // beginning of region 2, for the hash table
#define FROZEN_CONTROL_SEQUENCE    (HASH_BASE + HASH_SIZE)          // for error recovery
#define FROZEN_PROTECTION          FROZEN_CONTROL_SEQUENCE          // inaccessible but definable
#define FROZEN_CR                  (FROZEN_CONTROL_SEQUENCE + 1)    // permanent `\cr'
#define FROZEN_END_GROUP           (FROZEN_CONTROL_SEQUENCE + 2)    // permanent `\endgroup'
#define FROZEN_RIGHT               (FROZEN_CONTROL_SEQUENCE + 3)    // permanent `\right'
#define FROZEN_FI                  (FROZEN_CONTROL_SEQUENCE + 4)    // permanent `\fi'
#define FROZEN_END_TEMPLATE        (FROZEN_CONTROL_SEQUENCE + 5)    // permanent `\endtemplate'
#define FROZEN_ENDV                (FROZEN_CONTROL_SEQUENCE + 6)    // second permanent `\endtemplate'
#define FROZEN_RELAX               (FROZEN_CONTROL_SEQUENCE + 7)    // permanent `\relax'
#define END_WRITE                  (FROZEN_CONTROL_SEQUENCE + 8)    // permanent `\endwrite'
#define FROZEN_DONT_EXPAND         (FROZEN_CONTROL_SEQUENCE + 9)    // permanent `\notexpanded:'
#define FROZEN_NULL_FONT           (FROZEN_CONTROL_SEQUENCE + 10)   // permanent `\nullfont'
#define FONT_ID_BASE               (FROZEN_NULL_FONT - FONT_BASE)   // begins table of 257 permanent font identifiers
#define UNDEFINED_CONTROL_SEQUENCE (FROZEN_NULL_FONT + 257)         // dummy location
#define GLUE_BASE                  (UNDEFINED_CONTROL_SEQUENCE + 1) // beginning of region 3
```

```c << Initialize table entries (done by INITEX only) >>+=
eq_type(UNDEFINED_CONTROL_SEQUENCE) = UNDEFINED_CS;
equiv(UNDEFINED_CONTROL_SEQUENCE) = null;
eq_level(UNDEFINED_CONTROL_SEQUENCE) = LEVEL_ZERO;
for(k = ACTIVE_BASE; k < UNDEFINED_CONTROL_SEQUENCE; k++) {
    eqtb[k] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
}
```
