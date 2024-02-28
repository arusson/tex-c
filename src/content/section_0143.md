# Section 143

A *LIGATURE_NODE*, which occurs only in horizontal lists, specifies a character that was fabricated from the interaction of two or more actual characters.
The second word of the node, which is called the *lig_char* word, contains *font* and *character* fields just as in a *CHAR_NODE*.
The characters that generated the ligature have not been forgotten, since they are needed for diagnostic messages and for hyphenation; the *lig_ptr* field points to a linked list of character nodes for all original characters that have been deleted.
(This list might be empty if the characters that generated the ligature were retained in other nodes.)

The *subtype* field is 0, plus 2 and/or 1 if the original source of the ligature included implicit left and/or right boundaries.

```c include/constants.h
#define LIGATURE_NODE 6 // |type| of a ligature node
```

```c include/datastructures.h
#define lig_char(X) ((X) + 1)           // the word where the ligature is to be found
#define lig_ptr(X)  link(lig_char((X))) // the list of characters
```
