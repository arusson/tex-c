# Section 800

Finally, we will reach the end of the alignment, and we can breathe a sigh of relief that memory hasn't overflowed.
All the unset boxes will now be set so that the columns line up, taking due account of spanned columns.

```c alignment.c
void fin_align() {
    pointer p, q, r, s, u, v; // registers for the list operations
    scaled t, w;              // width of column
    scaled o;                 // shift offset for unset boxes
    halfword n;               // matching span amount
    scaled rule_save;         // temporary storage for |overfull_rule|
    memory_word aux_save;     // temporary storage for |aux|
    
    if (cur_group != ALIGN_GROUP) {
        confusion("align1");
    }
    unsave(); // that |ALIGN_GROUP| was for individual entries
    if (cur_group != ALIGN_GROUP) {
        confusion("align0");
    }
    unsave(); // that |ALIGN_GROUP| was for the whole alignment
    if (nest[nest_ptr - 1].mode_field == MMODE) {
        o = display_indent;
    }
    else {
        o = 0;
    }

    // << Go through the preamble list, determining the column widths and changing the alignrecords to dummy unset boxes >>

    // << Package the preamble list, to determine the actual tabskip glue amounts, and let |p| point to this prototype box >>

    // << Set the glue in all the unset boxes of the current list >>
    
    flush_node_list(p);
    pop_alignment();
    // << Insert the current list into its environment >>
}
```
