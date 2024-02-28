# Section 544

The *tag* field in a *char_info_word* has four values that explain how to interpret the *remainder* field.

- *tag = 0* (*NO_TAG*) means that *remainder* is unused.
- *tag = 1* (*LIG_TAG*) means that this character has a ligature/kerning
  program starting at position *remainder* in the *lig_kern* array.
- *tag = 2* (*LIST_TAG*) means that this character is part of a chain of
  characters of ascending sizes, and not the largest in the chain.
  The *remainder* field gives the character code of the next larger character.\par
- *tag = 3* (*EXT_TAG*) means that this character code represents an
  extensible character, i.e., a character that is built up of smaller pieces
  so that it can be made arbitrarily large.
  The pieces are specified in *exten[remainder]*.

Characters with *tag = 2* and *tag = 3* are treated as characters with *tag = 0* unless they are used in special circumstances in math formulas.
For example, the `\sum` operation looks for a *LIST_TAG*, and the `\left` operation looks for both *LIST_TAG* and *EXT_TAG*.

```c include/constants.h
#define NO_TAG   0 // vanilla character
#define LIG_TAG  1 // character has a ligature/kerning program
#define LIST_TAG 2 // character has a successor in a charlist
#define EXT_TAG  3 // character is extensible
```
