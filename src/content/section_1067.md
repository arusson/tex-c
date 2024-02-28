# Section 1067

The routine for a *RIGHT_BRACE* character branches into many subcases, since a variety of things may happen, depending on *cur_group*.
Some types of groups are not supposed to be ended by a right brace; error messages are given in hopes of pinpointing the problem.
Most branches of this routine will be filled in later, when we are ready to understand them; meanwhile, we must prepare ourselves to deal with such errors.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(RIGHT_BRACE):
    handle_right_brace();
    break;
```
