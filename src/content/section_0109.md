# Section 109

When $\TeX$ "packages" a list into a box, it needs to calculate the proportionality ratio by which the glue inside the box should stretch or shrink.
This calculation does not affect $\TeX$'s decision making, so the precise details of rounding, etc., in the glue calculation are not of critical importance for the consistency of results on different computers.

We shall use the type *glue_ratio* for such proportionality ratios.
A glue ratio should take the same amount of memory as an *int* (usually 32 bits) if it is to blend smoothly with $\TeX$'s other data structures.
Thus *glue_ratio* should be equivalent to *short_real* in some implementations of Pascal.
Alternatively, it is possible to deal with glue ratios using nothing but fixed-point arithmetic; see *TUGboat* **3**,1 (March 1982), 10--27.
(But the routines cited there must be modified to allow negative glue ratios.)

> ![NOTE]
> *float* and *unfloat* are unused.
> *float_constant* is directly used by appending `.0` to a value.
> Finally, *glue_ration* is made into a *double*.

```c include/arithmetic.h
#define set_glue_ratio_zero(X) (X) = 0.0 // store the representation of zero ratio
#define set_glue_ratio_one(X)  (X) = 1.0 // store the representation of unit ratio
```

```c << Types in the outer block >>+=
typedef double glue_ratio; // one-word representation of a glue expansion factor
```
