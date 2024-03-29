# Section 768: Alignment

It's sort of a miracle whenever `\halign` and `\valign` work, because they cut across so many of the control structures of $\TeX$.

Therefore the present page is probably not the best place for a beginner to start reading this program; it is better to master everything else first.

Let us focus our thoughts on an example of what the input might be, in order to get some idea about how the alignment miracle happens.
The example doesn't do anything useful, but it is sufficiently general to indicate all of the special cases that must be dealt with; please do not be disturbed by its apparent complexity and meaninglessness.

```
\tabskip 2pt plus 3pt
\halign to 300pt{u1#v1&
        \tabskip 1pt plus 1fil u2#v2&
        u3#v3\cr
    a1&\omit a2&\vrule\cr
    \noalign{\vskip 3pt}
    b1\span b2\cr
    \omit&c2\span\omit\cr}
```

Here's what happens:

(0) When '`\halign to 300pt\{`' is scanned, the *scan_spec* routine places the 300pt dimension onto the *save_stack*, and an *ALIGN_GROUP* code is placed above it.
This will make it possible to complete the alignment when the matching '`}`' is found.

(1) The preamble is scanned next.
Macros in the preamble are not expanded, except as part of a tabskip specification.
For example, if `u2` had been a macro in the preamble above, it would have been expanded, since $\TeX$ must look for '`minus...`' as part of the tabskip glue.
A "preamble list" is constructed based on the user's preamble; in our case it contains the following seven items:

|                                 |                                       |
| ------------------------------  | ------------------------------------- |
| `\glue 2pt plus 3pt`            | (the tabskip preceding column 1)      |
| `\alignrecord, width` $-\infty$ | (preamble info for column 1)          |
| `\glue 2pt plus 3pt`            | (the tabskip between columns 1 and 2) |
| `\alignrecord, width` $-\infty$ | (preamble info for column 2)          |
| `\glue 1pt plus 1fil`           | (the tabskip between columns 2 and 3) |
| `\alignrecord, width` $-\infty$ | (preamble info for column 3)          |
| `\glue 1pt plus 1fil`           | (the tabskip following column 3)      |


These "alignrecord" entries have the same size as an *UNSET_NODE*, since they will later be converted into such nodes.
However, at the moment they have no *type* or *subtype* fields; they have *info* fields instead, and these *info* fields are initially set to the value *END_SPAN*, for reasons explained below.
Furthermore, the alignrecord nodes have no *height* or *depth* fields; these are renamed *u_part* and *v_part*, and they point to token lists for the templates of the alignment.
For example, the *u_part* field in the first alignrecord points to the token list '`u1`', i.e., the template preceding the '`#`' for column&nbsp;1.

(2) $\TeX$ now looks at what follows the `\cr` that ended the preamble.
It is not '`\noalign`' or '`\omit`', so this input is put back to be read again, and the template '`u1`' is fed to the scanner.
Just before reading '`u1`', $\TeX$ goes into restricted horizontal mode.
Just after reading '`u1`', $\TeX$ will see '`a1`', and then (when the `&` is sensed) $\TeX$ will see '`v1`'.
Then $\TeX$ scans an *ENDV* token, indicating the end of a column.
At this point an *UNSET_NODE* is created, containing the contents of the current hlist (i.e., '`u1a1v1`').
The natural width of this unset node replaces the *width* field of the alignrecord for column&nbsp;1; in general, the alignrecords will record the maximum natural width that has occurred so far in a given column.

(3) Since '`\omit`' follows the '`&`', the templates for column&nbsp;2 are now bypassed.
Again $\TeX$ goes into restricted horizontal mode and makes an *UNSET_NODE* from the resulting hlist; but this time the hlist contains simply '`a2`'.
The natural width of the new unset box is remembered in the *width* field of the alignrecord for column&nbsp;2.

(4) A third *UNSET_NODE* is created for column 3, using essentially the mechanism that worked for column&nbsp;1; this unset box contains '`u3\vrule v3`'.
The vertical rule in this case has running dimensions that will later extend to the height and depth of the whole first row, since each *UNSET_NODE* in a row will eventually inherit the height and depth of its enclosing box.

(5) The first row has now ended; it is made into a single unset box comprising the following seven items:

```
\glue 2pt plus 3pt
\unsetbox for 1 column: u1a1v1
\glue 2pt plus 3pt
\unsetbox for 1 column: a2
\glue 1pt plus 1fil
\unsetbox for 1 column: u3\vrule v3
\glue 1pt plus 1fil
```

The width of this unset row is unimportant, but it has the correct height and depth, so the correct baselineskip glue will be computed as the row is inserted into a vertical list.

(6) Since '`\noalign`' follows the current `\cr`, $\TeX$ appends additional material (in this case `\vskip 3pt`) to the vertical list.
While processing this material, $\TeX$ will be in internal vertical mode, and *NO_ALIGN_GROUP* will be on *save_stack*.

(7) The next row produces an unset box that looks like this:

```
\glue 2pt plus 3pt
\unsetbox for 2 columns: u1b1v1u2b2v2
\glue 1pt plus 1fil
\unsetbox for 1 column: (empty)
\glue 1pt plus 1fil
```
The natural width of the unset box that spans columns 1&nbsp;and&nbsp;2 is stored in a "span node," which we will explain later; the *info* field of the alignrecord for column&nbsp;1 now points to the new span node, and the *info* of the span node points to *END_SPAN*.

(8) The final row produces the unset box
```
\glue 2pt plus 3pt
\unsetbox for 1 column: (empty)
\glue 2pt plus 3pt
\unsetbox for 2 columns: u2c2v2
\glue 1pt plus 1fil
```

A new span node is attached to the alignrecord for column 2.

(9) The last step is to compute the true column widths and to change all the unset boxes to hboxes, appending the whole works to the vertical list that encloses the `\halign`.
The rules for deciding on the final widths of each unset column box will be explained below.

Note that as `\halign` is being processed, we fearlessly give up control to the rest of $\TeX$.
At critical junctures, an alignment routine is called upon to step in and do some little action, but most of the time these routines just lurk in the background.
It's something like post-hypnotic suggestion.
