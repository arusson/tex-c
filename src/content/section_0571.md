# Section 571

A *fix_word* whose four bytes are $(a,b,c,d)$ from left to right represents the number

$$
x = \left\{
\begin{array}{ll}
b\cdot2^{-4} + c\cdot 2^{-12} + d\cdot 2^{-20}        & \text{if } a = 0; \\
-16 + b\cdot 2^{-4} + c\cdot 2^{-12} + d\cdot 2^{-20} & \text{if } a = 255.
\end{array}
\right.
$$

(No other choices of $a$ are allowed, since the magnitude of a number in design-size units must be less than 16.)
We want to multiply this quantity by the integer&nbsp;$z$, which is known to be less than $2^{27}$.
If $z < 2^{23}$, the individual multiplications $b\cdot z$, $c\cdot z$, $d\cdot z$ cannot overflow;
otherwise we will divide $z$ by 2, 4, 8, or 16, to obtain a multiplier less than $2^{23}$, and we can compensate for this later.
If $z$ has thereby been replaced by $z' = z/2^e$, let $\beta = 2^{4 - e}$; we shall compute

$$
\lfloor(b + c\cdot2^{-8} + d\cdot 2^{-16})\,z'/\beta\rfloor
$$

if $a = 0$, or the same quantity minus $\alpha = 2^{4 + e}z'$ if $a = 255$.
This calculation must be done exactly, in order to guarantee portability of $\TeX$ between computers.

```c include/font_metric.h
#define store_scaled(X)                                      \
    do {                                                     \
        fget(a);                                             \
        fget(b);                                             \
        fget(c);                                             \
        fget(d);                                             \
        sw = (((((d*z) / 256) + (c*z)) / 256) + (b*z))/beta; \
        if (a == 0) {                                        \
            (X) = sw;                                        \
        }                                                    \
        else if (a == 255) {                                 \
            (X) = sw - alpha;                                \
        }                                                    \
        else {                                               \
            abort;                                           \
        }                                                    \
    } while (0)
```

```c << Read box dimensions >>=
// << Replace |z| by |z'| and compute \alpha, \beta >>
for(k = width_base[f]; k <= lig_kern_base[f] - 1; k++) {
    store_scaled(font_info[k].sc);
}
if (font_info[width_base[f]].sc != 0) {
    abort; // width[0] must be zero
}
if (font_info[height_base[f]].sc != 0) {
    abort; // height[0] must be zero
}
if (font_info[depth_base[f]].sc != 0) {
    abort; // depth[0] must be zero
}
if (font_info[italic_base[f]].sc != 0) {
    abort; // italic[0] must be zero
}
```
