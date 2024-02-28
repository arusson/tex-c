# Section 847

The length of lines depends on whether the user has specified `\parshape` or `\hangindent`.
If *par_shape_ptr* is not null, it points to a *(2n + 1)*-word record in *mem*, where the *info* in the first word contains the value of *n*, and the other *2n* words contain the left margins and line lengths for the first *n* lines of the paragraph; the specifications for line *n* apply to all subsequent lines.
If *par_shape_ptr = null*, the shape of the paragraph depends on the value of *n = hang_after*;
if *n* $\geq$ *0*, hanging indentation takes place on lines *n + 1*, *n + 2*, $\dots$, otherwise it takes place on lines 1, $\dots$, *|n|*.
When hanging indentation is active, the left margin is *hang_indent*, if *hang_indent* $\geq$ *0*, else it is 0;
the line length is *hsize* − <span style="white-space: nowrap;">*|hang_indent|*</span>.
The normal setting is *par_shape_ptr = null*, *hang_after = 1*, and *hang_indent = 0*.
Note that if *hang_indent = 0*, the value of *hang_after* is irrelevant.

```c << Global variables >>+=
halfword easy_line;         // line numbers |> easy_line| are equivalent in break nodes
halfword last_special_line; // line numbers |> last_special_line| all have the same width
scaled first_width;         // the width of all lines |<= last_special_line|, if no \parshape has been specified
scaled second_width;        // the width of all lines |> last_special_line|
scaled first_indent;        // left margin to go with |first_width|
scaled second_indent;       // left margin to go with |second_width|
```
