# Section 590

The last page in a `DVI` file is followed by *'POST'*;
this command introduces the postamble, which summarizes important facts that $\TeX$ has accumulated about the file, making it possible to print subsets of the data with reasonable efficiency.
The postamble has the form

<div align="center">
<div style="text-align: left; display: inline-block;">

*post p[4] num[4] den[4] mag[4] l[4] u[4] s[2] t[2]*<br>
⟨&nbsp;font definitions&nbsp;⟩<br>
*post_post q[4] i[1] 223's[$\geq$ 4]*
</div>
</div>

Here *p* is a pointer to the final *BOP* in the file.
The next three parameters, *num*, *den*, and *mag*, are duplicates of the quantities that appeared in the preamble.

Parameters *l* and *u* give respectively the height-plus-depth of the tallest page and the width of the widest page, in the same units as other dimensions of the file.
These numbers might be used by a `DVI`-reading program to position individual "pages" on large sheets of film or paper;
however, the standard convention for output on normal size paper is to position each page so that the upper left-hand corner is exactly one inch from the left and the top.
Experience has shown that it is unwise to design `DVI`-to-printer software that attempts cleverly to center the output; a fixed position of the upper left corner is easiest for users to understand and to work with.
Therefore *l* and&nbsp;*u* are often ignored.

Parameter *s* is the maximum stack depth (i.e., the largest excess of *PUSH* commands over *POP* commands) needed to process this file.
Then comes *t*, the total number of pages (*BOP* commands) present.

The postamble continues with font definitions, which are any number of *FNT_DEF* commands as described above, possibly interspersed with *NOP* commands.
Each font number that is used in the `DVI` file must be defined exactly twice:
Once before it is first selected by a *FNT* command, and once in the postamble.
