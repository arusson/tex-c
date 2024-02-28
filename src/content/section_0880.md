# Section 880

The current line to be justified appears in a horizontal list starting at *link(TEMP_HEAD)* and ending at *cur_break(cur_p)*.
If *cur_break(cur_p)* is a glue node, we reset the glue to equal the *right_skip* glue; otherwise we append the *right_skip* glue at the right.
If *cur_break(cur_p)* is a discretionary node, we modify the list so that the discretionary break is compulsory, and we set *disc_break* to *true*.
We also append the *left_skip* glue at the left of the line, unless it is zero.

```c << Justify the line ending at breakpoint |cur_p|, and append it to the current vertical list, together with associated penalties and other insertions >>=
// << Modify the end of the line to reflect the nature of the break and to include \rightskip; also set the proper value of |disc_break| >>

// << Put the \leftskip glue at the left and detach this line >>

// << Call the packaging subroutine, setting |just_box| to the justified box >>

// << Append the new box to the current vertical list, followed by the list of special nodes taken out of the box by the packager >>

// << Append a penalty node, if a nonzero penalty is appropriate >>
```
