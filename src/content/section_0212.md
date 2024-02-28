# Section 212

The state of affairs at any semantic level can be represented by five values:

- *mode* is the number representing the semantic mode, as just explained.
- *head* is a *pointer* to a list head for the list being built;
  *link(head)* therefore points to the first element of the list, or to *null*
  if the list is empty.
- *tail* is a *pointer* to the final node of the list being built;
  thus, *tail = head* if and only if the list is empty.
- *prev_graf* is the number of lines of the current paragraph that have
  already been put into the present vertical list.
- *aux* is an auxiliary *memory_word* that gives further information
  that is needed to characterize the situation.

In vertical mode, *aux* is also known as *prev_depth*; it is the scaled value representing the depth of the previous box, for use in baseline calculations, or it is $\leq$ *−1000*pt if the next box on the vertical list is to be exempt from baseline calculations.
In horizontal mode, *aux* is also known as *space_factor* and *clang*;
it holds the current space factor used in spacing calculations, and the current language used for hyphenation.
(The value of *clang* is undefined in restricted horizontal mode.)
In math mode, *aux* is also known as *incompleat_noad*;
if not *null*, it points to a record that represents the numerator of a generalized fraction for which the denominator is currently being formed in the current list.

There is also a sixth quantity, *mode_line*, which correlates the semantic nest with the user's input; *mode_line* contains the source line number at which the current level of nesting was entered.
The negative of this line number is the *mode_line* at the level of the user's output routine.

In horizontal mode, the *prev_graf* field is used for initial language data.

The semantic nest is an array called *nest* that holds the *mode*, *head*, *tail*, *prev_graf*, *aux*, and *mode_line* values for all semantic levels below the currently active one. Information about the currently active level is kept in the global quantities *mode*, *head*, *tail*, *prev_graf*, *aux*, and *mode_line*, which live in a Pascal record that is ready to be pushed onto *nest* if necessary.

```c include/constants.h
#define IGNORE_DEPTH -65536000 // |prev_depth| value is ignored
```

```c << Types in the outer block >>+=
typedef struct {
    int mode_field;
    pointer head_field;
    pointer tail_field;
    int pg_field;
    int ml_field;
    memory_word aux_field;
} list_state_record;
```
