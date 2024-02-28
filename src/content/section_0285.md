# Section 285

When looking for possible pointers to a memory location, it is helpful to look for references from *eqtb* that might be waiting on the save stack.
Of course, we might find spurious pointers too; but this routine is merely an aid when debugging, and at such times we are grateful for any scraps of information, even if they prove to be irrelevant.

```c << Search |save_stack| for equivalents that point to |p| >>=
if (save_ptr > 0) {
    for(q = 0; q < save_ptr; q++) {
        if (equiv_field(save_stack[q]) == p) {
            print_nl("SAVE(");
            print_int(q);
            print_char(')');
        }
    }
}
```
