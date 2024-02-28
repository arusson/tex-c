# Section 608

The *info* fields in the entries of the down stack or the right stack have six possible settings: *Y_HERE* or *Z_HERE* mean that the `DVI` command refers to *y* or *z*, respectively (or to *W* or *X*, in the case of horizontal motion); *YZ_OK* means that the `DVI` command is *DOWN* (or *RIGHT*) but can be changed to either *Y* or *Z* (or to either *W* or *X*); *Y_OK* means that it is *DOWN* and can be changed to *Y* but not *Z*; *Z_OK* is similar; and *D_FIXED* means it must stay *DOWN*.

The four settings *YZ_OK*, *Y_OK*, *Z_OK*, *D_FIXED* would not need to be distinguished from each other if we were simply solving the digit-subscripting problem mentioned above.
But in $\TeX$'s case there is a complication because of the nested structure of *PUSH* and *POP* commands.
Suppose we add parentheses to the digit-subscripting problem, redefining hits so that $\delta_y\ldots \delta_y$ is a hit if all $y$'s between the $\delta$'s are enclosed in properly nested parentheses, and if the parenthesis level of the right-hand $\delta_y$ is deeper than or equal to that of the left-hand one.
Thus, '(' and ')' correspond to *'PUSH'* and *'POP'*.
Now if we want to assign a subscript to the final 1 in the sequence

$$
2_y\,7_d\,1_d\,(\,8_z\,2_y\,8_z\,)\,1
$$

we cannot change the previous $1_d$ to $1_y$, since that would invalidate the $2_y\ldots2_y$ hit.
But we can change it to $1_z$, scoring a hit since the intervening $8_z$'s are enclosed in parentheses.

The program below removes movement nodes that are introduced after a *PUSH*, before it outputs the corresponding *POP*.

```c include/constants.h
#define Y_HERE  1 // |info| when the movement entry points to a |y| command
#define Z_HERE  2 // |info| when the movement entry points to a |z| command
#define YZ_OK   3 // |info| corresponding to an unconstrained |down| command
#define Y_OK    4 // |info| corresponding to a |down| that can't become a |z|
#define Z_OK    5 // |info| corresponding to a |down| that can't become a |y|
#define D_FIXED 6 // |info| corresponding to a |down| that can't change
```
