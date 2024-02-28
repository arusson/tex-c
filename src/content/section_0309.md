# Section 309

The input routines must also interact with the processing of `halign` and `\valign`, since the appearance of tab marks and `\cr` in certain places is supposed to trigger the beginning of special $\langle v_j\rangle$ template text in the scanner.
This magic is accomplished by an *align_state* variable that is increased by&nbsp;1 when a '`{`' is scanned and decreased by&nbsp;1 when a '`}`' is scanned.
The *align_state* is nonzero during the $\langle u_j\rangle$ template, after which it is set to zero; the $\langle v_j\rangle$ template begins when a tab mark or `\cr` occurs at a time that *align_state = 0*.

```c << Global variables >>+=
int align_state; // group level with respect to current alignment
```
