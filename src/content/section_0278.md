# Section 278

The counterpart of *eq_define* for the remaining (fullword) positions in
*eqtb* is called *eq_word_define*.
Since *xeq_level[p]* $\geq$ *LEVEL_ONE* for all *p*, a *'RESTORE_ZERO'* will never be used in this case.

```c datastructures/stack.c
void eq_word_define(pointer p, int w) {
    if (xeq_level[p] != cur_level) {
        eq_save(p, xeq_level[p]);
        xeq_level[p] = cur_level;
    }
    eqtb[p].integer = w;
}
```
