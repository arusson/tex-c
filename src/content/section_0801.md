# Section 801

It's time now to dismantle the preamble list and to compute the column widths.
Let $w_{ij}$ be the maximum of the natural widths of all entries that span columns *i* through *j*, inclusive.
The alignrecord for column&nbsp;*i* contains $w_{ii}$ in its *width* field, and there is also a linked list of the nonzero $w_{ij}$ for increasing *j*, accessible via the *info* field;
these span nodes contain the value *j - i + MIN_QUARTERWORD* in their *link* fields.
The values of $w_{ii}$ were initialized to *NULL_FLAG*, which we regard as $-\infty$.

The final column widths are defined by the formula

$$
w_j = \max_{1 \leq i\leq j}\biggl( w_{ij} - \sum_{i\leq k<j}(t_k + w_k)\biggr),
$$

where $t_k$ is the natural width of the tabskip glue between columns *k* and&nbsp;*k + 1*.
However, if $w_{ij} = -\infty$ for all *i* in the range *1* $\leq$ *i* $\leq$ *j* (i.e., if every entry that involved column&nbsp;*j* also involved column&nbsp;*j + 1*), we let $w_j = 0$, and we zero out the tabskip glue after column&nbsp;*j*.

$\TeX$ computes these values by using the following scheme:
First $w_1 = w_{11}$.
Then replace $w_{2j}$ by $\max(w_{2j},w_{1j} - t_1 - w_1)$, for all *j* $>$ *1*.
Then $w_2 = w_{22}$.
Then replace $w_{3j}$ by $\max(w_{3j},w_{2j} - t_2 - w_2)$ for all *j* $>$ *2*; and so on.
If any $w_j$ turns out to be $-\infty$, its value is changed to zero and so is the next tabskip.

```c << Go through the preamble list, determining the column widths and changing the alignrecords to dummy unset boxes >>=
q = link(preamble);
do {
    flush_list(u_part(q));
    flush_list(v_part(q));
    p = link(link(q));
    if (width(q) == NULL_FLAG) {
        // << Nullify |width(q)| and the tabskip glue following this column >>
    }
    if (info(q) != END_SPAN) {
        // << Merge the widths in the span nodes of |q| with those of |p|, destroying the span nodes of |q| >>
    }
    type(q) = UNSET_NODE;
    span_count(q) = MIN_QUARTERWORD;
    height(q) = 0;
    depth(q) = 0;
    glue_order(q) = NORMAL;
    glue_sign(q) = NORMAL;
    glue_stretch(q) = 0;
    glue_shrink(q) = 0;
    q = p;
} while (q != null);
```
