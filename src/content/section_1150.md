# Section 1150

Subformulas of math formulas cause a new level of math mode to be entered, on the semantic nest as well as the save stack.
These subformulas arise in several ways:
(1)&nbsp;A left brace by itself indicates the beginning of a subformula that will be put into a box, thereby freezing its glue and preventing line breaks.
(2)&nbsp;A subscript or superscript is treated as a subformula if it is not a single character; the same applies to the nucleus of things like `\underline`.
(3)&nbsp;The `\left` primitive initiates a subformula that will be terminated by a matching `\right`.
The group codes placed on *save_stack* in these three cases are *MATH_GROUP*, *MATH_GROUP*, and *MATH_LEFT_GROUP*, respectively.

Here is the code that handles case (1);
the other cases are not quite as trivial, so we shall consider them later.

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + LEFT_BRACE:
    tail_append(new_noad());
    back_input();
    scan_math(nucleus(tail));
    break;
```
