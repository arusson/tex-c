# Section 256: The hash table

Control sequences are stored and retrieved by means of a fairly standard hash table algorithm called the method of "coalescing lists" (cf. Algorithm 6.4C in *The Art of Computer Programming*).
Once a control sequence enters the table, it is never removed, because there are complicated situations involving `\gdef` where the removal of a control sequence at the end of a group would be a mistake preventable only by the introduction of a complicated reference-count mechanism.

The actual sequence of letters forming a control sequence identifier is stored in the *str_pool* array together with all the other strings.
An auxiliary array *hash* consists of items with two halfword fields per word.
The first of these, called *next(p)*, points to the next identifier belonging to the same coalesced list as the identifier corresponding to&nbsp;*p*;
and the other, called *text(p)*, points to the *str_start* entry for *p*'s identifier.
If position&nbsp;*p* of the hash table is empty, we have *text(p) = 0*;
if position *p* is either empty or the end of a coalesced hash list, we have *next(p) = 0*.
An auxiliary pointer variable called *hash_used* is maintained in such a way that all locations *p* $\geq$ *hash_used* are nonempty.
The global variable *cs_count* tells how many multiletter control sequences have been defined, if statistics are being kept.

A global boolean variable called *no_new_control_sequence* is set to *true* during the time that new hash table entries are forbidden.

```c include/datastructures.h
#define next(X)         hh_lh(hash[(X)]) // link for coalesced lists
#define text(X)         hh_rh(hash[(X)]) // string number for control sequence name
#define hash_is_full    (hash_used == HASH_BASE) // test if all positions are occupied
#define font_id_text(X) text(FONT_ID_BASE + (X)) // a frozen font identifier's name
```

```c << Global variables >>+=
memory_word hash0[UNDEFINED_CONTROL_SEQUENCE - HASH_BASE]; // the hash table
memory_word *hash = hash0 - HASH_BASE;
pointer hash_used;            // allocation pointer for |hash|
bool no_new_control_sequence; // are new identifiers legal?
int cs_count;                 // total number of known identifiers
```
