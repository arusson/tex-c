# Section 770

Alignments can occur within alignments, so a small stack is used to access the alignrecord information.
At each level we have a *preamble* pointer, indicating the beginning of the preamble list; a *cur_align* pointer, indicating the current position in the preamble list; a *cur_span* pointer, indicating the value of *cur_align* at the beginning of a sequence of spanned columns; a *cur_loop* pointer, indicating the tabskip glue before an alignrecord that should be copied next if the current list is extended;
and the *align_state* variable, which indicates the nesting of braces so that `\cr` and `\span` and tab marks are properly intercepted.
There also are pointers *cur_head* and *cur_tail* to the head and tail of a list of adjustments being moved out from horizontal mode to vertical&nbsp;mode.

The current values of these seven quantities appear in global variables;
when they have to be pushed down, they are stored in 5-word nodes, and *align_ptr* points to the topmost such node.

```c include/constants.h
#define ALIGN_STACK_NODE_SIZE 5 // number of |mem| words to save alignment states
```

```c include/alignment.h
#define preamble link(ALIGN_HEAD) // the current preamble list
```

```c << Global variables >>+=
pointer cur_align;          // current position in preamble list
pointer cur_span;           // start of currently spanned columns in preamble list
pointer cur_loop;           // place to copy when extending a periodic preamble
pointer align_ptr;          // most recently pushed-down alignment stack node
pointer cur_head, cur_tail; // adjustment list pointers
```
