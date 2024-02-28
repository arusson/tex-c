# Section 307

However, all this discussion about input state really applies only to the
case that we are inputting from a file.
There is another important case, namely when we are currently getting input from a token list.
In this case *state = TOKEN_LIST*, and the conventions about the other state variables
are different:

- *loc* is a pointer to the current node in the token list, i.e.,
  the node that will be read next. If *loc = null*, the token list has been fully read.

- *start* points to the first node of the token list; this node
  may or may not contain a reference count, depending on the type of token
  list involved.

- *token_type*, which takes the place of *index* in the
  discussion above, is a code number that explains what kind of token list
  is being scanned.

- *name* points to the *eqtb* address of the control sequence
  being expanded, if the current token list is a macro.

- *param_start*, which takes the place of *limit*, tells where
  the parameters of the current macro begin in the *param_stack*, if the
  current token list is a macro.

The *token_type* can take several values, depending on where the current token list came from:

- *PARAMETER*, if a parameter is being scanned;

- *U_TEMPLATE*, if the $\langle u_j\rangle$ part of an alignment
template is being scanned;

- *V_TEMPLATE*, if the $\langle v_j\rangle$ part of an alignment
template is being scanned;

- *BACKED_UP*, if the token list being scanned has been inserted as
  'to be read again';

- *INSERTED*, if the token list being scanned has been inserted as
  the text expansion of a `\count` or similar variable;

- *MACRO*, if a user-defined control sequence is being scanned;

- *OUTPUT_TEXT*, if an `\output` routine is being scanned;

- *EVERY_PAR_TEXT*, if the text of `\everypar` is being scanned;

- *EVERY_MATH_TEXT*, if the text of `\everymath` is being scanned;

- *EVERY_DISPLAY_TEXT*, if the text of `\everydisplay` is being scanned;

- *EVERY_HBOX_TEXT*, if the text of `\everyhbox` is being scanned;

- *EVERY_VBOX_TEXT*, if the text of `\everyvbox` is being scanned;

- *EVERY_JOB_TEXT*, if the text of `\everyjob` is being scanned;

- *EVERY_CR_TEXT*, if the text of `\everycr` is being scanned;

- *MARK_TEXT*, if the text of a `\mark` is being scanned;

- *WRITE_TEXT*, if the text of a `\write` is being scanned.

The codes for *OUTPUT_TEXT*, *EVERY_PAR_TEXT*, etc., are equal to a constant plus the corresponding codes for token list parameters *OUTPUT_ROUTINE_LOC*, *EVERY_PAR_LOC*, etc.
The token list begins with a reference count if and only if *token_type* $\geq$ *MACRO*.

```c include/datastructures.h
#define token_type  index // type of current token list
#define param_start limit // base of macro parameters in |param_stack|
```

```c include/constants.h
#define TOKEN_LIST         0  // |state| code when scanning a token list
#define PARAMETER          0  // |token_type| code for parameter
#define U_TEMPLATE         1  // |token_type| code for <u_j> template
#define V_TEMPLATE         2  // |token_type| code for <v_j> template
#define BACKED_UP          3  // |token_type| code for text to be reread
#define INSERTED           4  // |token_type| code for inserted texts
#define MACRO              5  // |token_type| code for defined control sequences
#define OUTPUT_TEXT        6  // |token_type| code for output routines
#define EVERY_PAR_TEXT     7  // |token_type| code for \everypar
#define EVERY_MATH_TEXT    8  // |token_type| code for \everymath
#define EVERY_DISPLAY_TEXT 9  // |token_type| code for \everydisplay
#define EVERY_HBOX_TEXT    10 // |token_type| code for \everyhbox
#define EVERY_VBOX_TEXT    11 // |token_type| code for \everyvbox
#define EVERY_JOB_TEXT     12 // |token_type| code for \everyjob
#define EVERY_CR_TEXT      13 // |token_type| code for \everycr
#define MARK_TEXT          14 // |token_type| code for \topmark, etc.
#define WRITE_TEXT         15 // |token_type| code for \write
```
