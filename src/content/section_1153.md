# Section 1153

The pointer *p* is placed on *save_stack* while a complex subformula is being scanned.

```c << Scan a subformula enclosed in braces and |return| >>=
back_input();
scan_left_brace();
saved(0) = p;
incr(save_ptr);
push_math(MATH_GROUP);
return;
```
 