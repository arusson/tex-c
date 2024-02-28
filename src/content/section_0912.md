# Section 912

Okay, we're ready to insert the potential hyphenations that were found.
When the following program is executed, we want to append the word *hu[1 .. hn]* after node *ha*, and node *q* should be appended to the result.
During this process, the variable *i* will be a temporary index into *hu*; the variable *j* will be an index to our current position in *hu*; the variable *l* will be the counterpart of *j*, in a discretionary branch; the variable *r* will point to new nodes being created; and we need a few new local variables:

```c << Local variables for hyphenation >>+=
pointer major_tail, minor_tail; // the end of lists in the main and discretionary branches being reconstructed
ASCII_code c = 0;               // character temporarily replaced by a hyphen
int c_loc;                      // where that character came from
int r_count;                    // replacement count for discretionary
pointer hyf_node;               // the hyphen, if it exists
```
