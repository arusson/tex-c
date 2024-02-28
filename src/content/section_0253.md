# Section 253

The last two regions of *eqtb* have fullword values instead of the three fields *eq_level*, *eq_type*, and *equiv*.
An *eq_type* is unnecessary, but $\TeX$ needs to store the *eq_level* information in another array called *xeq_level*.

> ![NOTE]
> Little bit of pointer arithmetic so arrays can be indexed by something other than zero.

```c << Global variables >>+=
memory_word eqtb0[EQTB_SIZE - ACTIVE_BASE + 1];
memory_word *eqtb = eqtb0 - ACTIVE_BASE;
quarterword xeq_level0[EQTB_SIZE - INT_BASE + 1];
quarterword *xeq_level = xeq_level0 - INT_BASE;
```
